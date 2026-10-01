#include "expr_build.h"

#include <list>
#include <memory>
#include <stdexcept>
#include <utility>

#include "nodes/expr.h"
#include "nodes/op_factory.h"
#include "nodes/op_node.h"
#include "token.h"
#include "token_stream.h"

namespace marex {
namespace parse {
[[nodiscard]] static std::list<std::unique_ptr<parse::OpNode>>
create_op_nodes(TokenStream& stream);

class OperationProcessor final {
   public:
    OperationProcessor() = default;

    [[nodiscard]] std::unique_ptr<parse::Expr> process_operators(
        std::list<std::unique_ptr<parse::OpNode>>&& op_nodes);

   private:
    [[maybe_unused]] bool is_first_time_in_iter_{};
};
}  // namespace parse

std::unique_ptr<parse::Expr> parse::build_expr(TokenStream& stream) {
    auto op_nodes = create_op_nodes(stream);

    return OperationProcessor{}.process_operators(
        std::move(op_nodes));
}

static std::list<std::unique_ptr<parse::OpNode>>
parse::create_op_nodes(TokenStream& stream) {
    std::list<std::unique_ptr<OpNode>> operators;

    stream.run_until_stmt_end([&](const lex::Token& token) {
        operators.emplace_back(
            OpFactory::create_op_node(lex::Token(token)));
    });

    return operators;
}

namespace parse {
std::unique_ptr<Expr> OperationProcessor::process_operators(
    [[maybe_unused]] std::list<std::unique_ptr<parse::OpNode>>&&
        op_nodes) {
    while (true) {
        for ([[maybe_unused]] auto& op_node : op_nodes) {
        }
    }

    throw std::runtime_error("not implemented yet");
}
}  // namespace parse
}  // namespace marex
