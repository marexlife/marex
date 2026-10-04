#include "expr_build.h"

#include <concepts>
#include <cstddef>
#include <exception>
#include <format>
#include <iterator>
#include <list>
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>

#include "defer.h"
#include "logging.h"
#include "nodes/binary_op.h"
#include "nodes/expr.h"
#include "nodes/op_factory.h"
#include "nodes/op_node.h"
#include "nodes/operand.h"
#include "nodes/operator.h"
#include "token.h"
#include "token_kind.h"
#include "token_stream.h"

namespace marex {
namespace parse {
template <std::derived_from<OpNode> T>
struct PreviousOpNodeData final {
    PreviousOpNodeData(std::shared_ptr<T> op_node, std::size_t index)
        : op_node(std::move(op_node)), index(index) {}

    std::shared_ptr<T> op_node;
    std::size_t index{};
};

class OperationProcessor final {
   public:
    OperationProcessor() = default;

    [[nodiscard]] OperationProcessor& create_op_nodes(
        TokenStream& stream, lex::TokenKind until_token_kind);

    [[nodiscard]] std::shared_ptr<parse::Expr> process_op_nodes();

   private:
    [[nodiscard]] bool was_previous_more_powerful(
        const Operator& this_op_node) const;

    void op_node_iter(std::shared_ptr<OpNode>& op_node);

    void handle_start(std::shared_ptr<OpNode>& op_node);
    void handle_in_between_iter(std::shared_ptr<OpNode>& op_node);
    void handle_in_between_bin_op(
        std::shared_ptr<BinaryOp>&& op_node);
    void handle_end(std::shared_ptr<OpNode>& op_node);
    void swap_bin_op_to_complex_operator();

    [[nodiscard]] bool is_last_iter() const;

    [[nodiscard]] std::size_t list_size() const {
        return op_nodes_.size();
    }

    std::list<std::shared_ptr<OpNode>> op_nodes_;

    std::optional<PreviousOpNodeData<Operator>> previous_operator_ =
        std::nullopt;
    std::optional<PreviousOpNodeData<Operand>> previous_operand_ =
        std::nullopt;

    std::size_t walk_through_iter_{};
    std::size_t index_{};
};
}  // namespace parse

std::shared_ptr<parse::Expr> parse::build_expr(
    TokenStream& stream, lex::TokenKind until_token_kind) {
    return OperationProcessor{}
        .create_op_nodes(stream, until_token_kind)
        .process_op_nodes();
}

namespace parse {
OperationProcessor& OperationProcessor::create_op_nodes(
    TokenStream& stream, lex::TokenKind until_token_kind) {
    try {
        stream.run_until(
            until_token_kind, [&](const lex::Token& token) {
                op_nodes_.emplace_back(
                    OpFactory::create_op_node(lex::Token(token)));
            });
    } catch (std::out_of_range& out_of_range_exception) {
        throw std::runtime_error(
            std::format("Last was not {}", *until_token_kind));
    } catch (const std::exception& exception) {
        throw exception;
    } catch (...) {
        throw std::runtime_error("unkown error from create_op_nodes");
    }

    core::log_info("completed run_until");

    return *this;
}

std::shared_ptr<Expr> OperationProcessor::process_op_nodes() {
    walk_through_iter_ = {};

    for (; op_nodes_.size() > 1; ++walk_through_iter_) {
        core::Defer end_while_iter = [&] {
            previous_operator_ = std::nullopt;
        };

        core::log_info("start walk through with list size {}:",
                       op_nodes_.size());

        for (index_ = {}; auto& op_node : op_nodes_) {
            core::log_info(
                "expr build: index: {}, walk through iter: {}",
                index_, walk_through_iter_);

            core::Defer increment_index = [&] { ++index_; };

            op_node_iter(op_node);
        }

        core::log_info();
    }

    return op_nodes_.front();
}

[[nodiscard]] bool OperationProcessor::is_last_iter() const {
    if (op_nodes_.empty()) [[unlikely]] {
        return true;
    }

    return index_ == op_nodes_.size() - 1;
}

void OperationProcessor::op_node_iter(
    std::shared_ptr<OpNode>& op_node) {
    core::log_info("previous_operand: {}, previous_operator: {}",
                   previous_operand_.has_value(),
                   previous_operator_.has_value());

    if (!previous_operator_) {
        handle_start(op_node);
        return;
    }

    if (is_last_iter()) {
        handle_end(op_node);
        return;
    }

    handle_in_between_iter(op_node);
}

void OperationProcessor::handle_start(
    std::shared_ptr<OpNode>& op_node) {
    core::log_info("handle_start");

    switch (op_node->get_op_node_kind()) {
        case marex::parse::OpNodeKind::BinaryOp: {
            core::log_info("handle_start: BinaryOp");

            auto bin_operator = op_node->cast<BinaryOp>();
            core::Defer set_to_false = [&] {
                previous_operator_ = PreviousOpNodeData<Operator>(
                    bin_operator, index_);
            };

            bin_operator->set_lhs(previous_operand_.value().op_node);
        } break;
        case marex::parse::OpNodeKind::MonoOp:
            throw std::runtime_error(
                "mono ops are not implemented yet");
        case marex::parse::OpNodeKind::Operand:
            core::log_info("handle_start: Operand");

            previous_operand_ =
                PreviousOpNodeData(op_node->cast<Operand>(), index_);
            break;
        case marex::parse::OpNodeKind::None:
            [[fallthrough]];
        default:
            std::unreachable();
    }
}

bool OperationProcessor::was_previous_more_powerful(
    const Operator& this_op_node) const {
    auto previous_binding_power =
        previous_operator_.value().op_node->get_binding_power();
    auto this_binding_power = this_op_node.get_binding_power();

    return previous_binding_power > this_binding_power;
}

void OperationProcessor::handle_in_between_iter(
    std::shared_ptr<OpNode>& op_node) {
    core::log_info("handle_in_between_iter");

    switch (op_node->get_op_node_kind()) {
        case marex::parse::OpNodeKind::BinaryOp:
            handle_in_between_bin_op(op_node->cast<BinaryOp>());
            break;
        case marex::parse::OpNodeKind::MonoOp:
            throw std::runtime_error(
                "mono op is not implemented yet");
        case marex::parse::OpNodeKind::Operand:
            previous_operand_ =
                PreviousOpNodeData(op_node->cast<Operand>(), index_);
            break;
        case marex::parse::OpNodeKind::None:
            [[fallthrough]];
        default:
            std::unreachable();
    }
}

void OperationProcessor::handle_in_between_bin_op(
    std::shared_ptr<BinaryOp>&& op_node) {
    core::log_info("handle_in_between_bin_op");

    if (!was_previous_more_powerful(*op_node)) {
        op_node->set_lhs(previous_operand_.value().op_node);

        return;
    }

    auto& previous_operator_node = previous_operator_.value().op_node;

    switch (previous_operator_node->get_op_node_kind()) {
        case marex::parse::OpNodeKind::BinaryOp: {
            auto previous_bin_op =
                previous_operator_node->cast<BinaryOp>();

            previous_bin_op->set_rhs(
                previous_operand_.value().op_node);

            if (previous_bin_op->is_finished()) {
                swap_bin_op_to_complex_operator();
            }
        } break;
        case marex::parse::OpNodeKind::MonoOp:
            throw std::runtime_error("mono op not implemented yet");
        case marex::parse::OpNodeKind::Operand:
            [[fallthrough]];
        case marex::parse::OpNodeKind::None:
            [[fallthrough]];
        default:
            std::unreachable();
    }
}

void OperationProcessor::swap_bin_op_to_complex_operator() {
    if (index_ == 0) [[unlikely]] {
        throw std::runtime_error(
            "internal error: index is too low in erasing "
            "from the node list");
    }

    core::log_info("swap_to_complex_operator");

    auto previous_operator_node_index =
        previous_operator_.value().index;

    if (previous_operator_node_index < 1) [[unlikely]] {
        throw std::runtime_error(
            "swap to bin op: previous_operator_node_index is too "
            "low");
    }

    core::log_info("previous_operator_node_index: {}",
                   previous_operator_node_index);

    auto front_iter_index = previous_operator_node_index - 1;
    auto front_iter = op_nodes_.begin();

    auto middle_iter_index = previous_operator_node_index;
    auto middle_iter = op_nodes_.begin();

    auto end_iter_index = previous_operator_node_index + 1;
    auto end_iter = op_nodes_.begin();

    std::advance(front_iter, front_iter_index);
    std::advance(middle_iter, middle_iter_index);
    std::advance(end_iter, end_iter_index);

    core::log_info("erase nodes");
    op_nodes_.erase(front_iter);
    op_nodes_.erase(middle_iter);
    op_nodes_.erase(end_iter);

    auto complex_operand =
        previous_operator_->op_node->to_complex_operand();

    if (op_nodes_.empty()) {
        op_nodes_.emplace_back(complex_operand);

        return;
    }

    core::log_info("emplace complex operand at {}", front_iter_index);

    op_nodes_.emplace(front_iter, complex_operand);
}

void OperationProcessor::handle_end(
    std::shared_ptr<OpNode>& op_node) {
    core::log_info("handle_end");

    auto previous_operator_node = previous_operator_.value().op_node;

    switch (previous_operator_node->get_op_node_kind()) {
        case OpNodeKind::BinaryOp: {
            core::log_info("handle_end: BinaryOp");

            auto previous_bin_op =
                previous_operator_node->cast<BinaryOp>();

            previous_bin_op->set_rhs(op_node);

            swap_bin_op_to_complex_operator();
        } break;
        case OpNodeKind::MonoOp:
            throw std::runtime_error("mono ops not supported yet");
        case OpNodeKind::None:
            [[fallthrough]];
        default:
            std::unreachable();
    }
}
}  // namespace parse
}  // namespace marex
