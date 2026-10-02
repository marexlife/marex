#include "expr_build.h"

#include <cstddef>
#include <iterator>
#include <list>
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>

#include "defer.h"
#include "nodes/binary_op.h"
#include "nodes/expr.h"
#include "nodes/op_factory.h"
#include "nodes/op_node.h"
#include "nodes/operand.h"
#include "nodes/operator.h"
#include "token.h"
#include "token_stream.h"

namespace marex {
namespace parse {
class OperationProcessor final {
   public:
    OperationProcessor() = default;

    [[nodiscard]] OperationProcessor& create_op_nodes(
        TokenStream& stream);

    [[nodiscard]] std::unique_ptr<parse::Expr> process_op_nodes();

   private:
    [[nodiscard]] bool get_was_previous_more_powerful(
        const Operator& this_op_node) const {
        auto previous_binding_power =
            previous_operator_.value()->get_binding_power();
        auto this_binding_power = this_op_node.get_binding_power();

        return previous_binding_power > this_binding_power;
    }

    void op_node_iter(std::shared_ptr<OpNode>& op_node);

    void handle_first_time_iter(std::shared_ptr<OpNode>& op_node);
    void handle_in_between_iter(std::shared_ptr<OpNode>& op_node);
    void handle_in_between_bin_op(
        std::shared_ptr<BinaryOp>&& op_node);
    void handle_last_bin_op(std::shared_ptr<OpNode>& op_node);

    std::list<std::shared_ptr<OpNode>> op_nodes_;
    std::optional<std::shared_ptr<Operator>> previous_operator_ =
        std::nullopt;
    std::optional<std::shared_ptr<Operand>> previous_operand_ =
        std::nullopt;
    std::size_t index_{};
    bool is_last_iter_{};
};
}  // namespace parse

std::unique_ptr<parse::Expr> parse::build_expr(TokenStream& stream) {
    return OperationProcessor{}
        .create_op_nodes(stream)
        .process_op_nodes();
}

namespace parse {
OperationProcessor& OperationProcessor::create_op_nodes(
    TokenStream& stream) {
    stream.run_until_stmt_end([&](const lex::Token& token) {
        op_nodes_.emplace_back(
            OpFactory::create_op_node(lex::Token(token)));
    });

    return *this;
}

std::unique_ptr<Expr> OperationProcessor::process_op_nodes() {
    while (op_nodes_.size() > 1) {
        core::Defer end_while_iter = [&] {
            previous_operator_ = std::nullopt;
        };

        for (index_ = {}; auto& op_node : op_nodes_) {
            is_last_iter_ = index_ == op_nodes_.size() - 1;

            core::Defer increment_index = [&] { ++index_; };

            op_node_iter(op_node);
        }
    }

    throw std::runtime_error("not implemented yet");
}

void OperationProcessor::op_node_iter(
    std::shared_ptr<OpNode>& op_node) {
    if (!previous_operator_ || !previous_operand_) {
        handle_first_time_iter(op_node);
        return;
    }

    if (is_last_iter_) {
        handle_last_bin_op(op_node);
        return;
    }

    handle_in_between_iter(op_node);
}

void OperationProcessor::handle_first_time_iter(
    std::shared_ptr<OpNode>& op_node) {
    switch (op_node->get_op_node_kind()) {
        case marex::parse::OpNodeKind::BinaryOp: {
            auto bin_operator = op_node->cast<BinaryOp>();
            core::Defer set_to_false = [&] {
                previous_operator_ = bin_operator;
            };

            bin_operator->set_lhs(previous_operand_.value());
        } break;
        case marex::parse::OpNodeKind::MonoOp:
            throw std::runtime_error(
                "mono ops are not implemented yet");
        case marex::parse::OpNodeKind::Operand:
            previous_operand_ = op_node->cast<Operand>();
            break;
        case marex::parse::OpNodeKind::None:
            [[fallthrough]];
        default:
            std::unreachable();
    }
}

void OperationProcessor::handle_in_between_iter(
    std::shared_ptr<OpNode>& op_node) {
    switch (op_node->get_op_node_kind()) {
        case marex::parse::OpNodeKind::BinaryOp:
            handle_in_between_bin_op(op_node->cast<BinaryOp>());
            break;
        case marex::parse::OpNodeKind::MonoOp:
            throw std::runtime_error(
                "mono op is not implemented yet");

        case marex::parse::OpNodeKind::Operand:
            previous_operand_ = op_node->cast<Operand>();
            break;
        case marex::parse::OpNodeKind::None:
            [[fallthrough]];
        default:
            std::unreachable();
    }
}

void OperationProcessor::handle_in_between_bin_op(
    std::shared_ptr<BinaryOp>&& op_node) {
    if (!get_was_previous_more_powerful(*op_node)) {
        op_node->set_lhs(previous_operand_.value());

        return;
    }

    auto& previous_operator_value = previous_operator_.value();

    switch (previous_operator_value->get_op_node_kind()) {
        case marex::parse::OpNodeKind::BinaryOp: {
            auto previous_bin_op =
                previous_operator_value->cast<BinaryOp>();

            previous_bin_op->set_rhs(previous_operand_.value());

            if (previous_bin_op->is_finished()) {
                auto op_nodes_erase_begin_iter = op_nodes_.begin();
                auto op_nodes_erase_end_iter = op_nodes_.begin();
                auto new_complex_operand_insert_iter =
                    op_nodes_.begin();

                if (index_ == 0) [[unlikely]] {
                    throw std::runtime_error(
                        "internal error: index is too low in erasing "
                        "from the node list");
                }

                std::advance(op_nodes_erase_begin_iter, index_ - 1);
                std::advance(op_nodes_erase_end_iter, index_ + 1);
                std::advance(new_complex_operand_insert_iter, index_);

                op_nodes_.erase(op_nodes_erase_begin_iter,
                                op_nodes_erase_end_iter);

                auto complex_operand =
                    previous_bin_op->to_complex_operand();

                op_nodes_.insert(new_complex_operand_insert_iter,
                                 complex_operand);
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

void OperationProcessor::handle_last_bin_op(
    [[maybe_unused]] std::shared_ptr<OpNode>& op_node) {}
}  // namespace parse
}  // namespace marex
