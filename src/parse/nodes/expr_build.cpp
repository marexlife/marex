#include "expr_build.h"

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
[[nodiscard]] static std::list<std::shared_ptr<parse::OpNode>>
create_op_nodes(TokenStream& stream);

class OperationProcessor final {
   public:
    OperationProcessor() = default;

    [[nodiscard]] std::unique_ptr<parse::Expr> process_operators(
        std::list<std::shared_ptr<parse::OpNode>>&& op_nodes);

   private:
    [[nodiscard]] bool was_previous_more_powerful(
        const Operator& this_op_node) const {
        auto previous_binding_power =
            previous_operator_.value()->get_binding_power();
        auto this_binding_power = this_op_node.get_binding_power();

        return previous_binding_power > this_binding_power;
    }

    void op_node_iter(std::shared_ptr<OpNode>& op_node);

    void handle_first_time_iter(std::shared_ptr<OpNode>& op_node);

    std::optional<std::shared_ptr<Operator>> previous_operator_ =
        std::nullopt;
    std::optional<std::shared_ptr<Operand>> previous_operand_ =
        std::nullopt;
};
}  // namespace parse

std::unique_ptr<parse::Expr> parse::build_expr(TokenStream& stream) {
    auto op_nodes = create_op_nodes(stream);

    return OperationProcessor{}.process_operators(
        std::move(op_nodes));
}

static std::list<std::shared_ptr<parse::OpNode>>
parse::create_op_nodes(TokenStream& stream) {
    std::list<std::shared_ptr<OpNode>> operators;

    stream.run_until_stmt_end([&](const lex::Token& token) {
        operators.emplace_back(
            OpFactory::create_op_node(lex::Token(token)));
    });

    return operators;
}

namespace parse {
std::unique_ptr<Expr> OperationProcessor::process_operators(
    std::list<std::shared_ptr<parse::OpNode>>&& op_nodes) {
    while (true) {
        core::Defer end_while_iter = [&] {
            previous_operator_ = std::nullopt;
        };

        for (auto& op_node : op_nodes) {
            op_node_iter(op_node);
        }
    }

    throw std::runtime_error("not implemented yet");
}

void OperationProcessor::op_node_iter(
    std::shared_ptr<OpNode>& op_node) {
    if (!previous_operand_) {
        handle_first_time_iter(op_node);
        return;
    }
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
}  // namespace parse
}  // namespace marex
