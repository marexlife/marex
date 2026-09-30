#include "expr_build.h"

#include <memory>
#include <stdexcept>
#include <vector>

#include "nodes/expr.h"
#include "nodes/op_factory.h"
#include "nodes/op_node.h"
#include "token.h"
#include "token_stream.h"

namespace marex {
namespace parse {
[[nodiscard]] static std::vector<std::unique_ptr<OpNode>>
create_operators(TokenStream& stream);
}  // namespace parse

std::unique_ptr<parse::Expr> parse::build_expr(TokenStream& stream) {
    auto operators = create_operators(stream);

    throw std::runtime_error("not implemented yet");
}

static std::vector<std::unique_ptr<parse::OpNode>>
parse::create_operators(TokenStream& stream) {
    std::vector<std::unique_ptr<OpNode>> operators;

    stream.run_until_stmt_end([&](const lex::Token& token) {
        operators.emplace_back(
            OpFactory::create_op_node(lex::Token(token)));
    });

    return operators;
}
}  // namespace marex
