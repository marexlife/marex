#include "expr_build.h"

#include <list>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include "nodes/expr.h"
#include "nodes/op_factory.h"
#include "nodes/op_node.h"
#include "token.h"
#include "token_stream.h"

namespace marex {
namespace parse {
[[nodiscard]] static std::list<std::unique_ptr<parse::OpNode>>
create_operators(TokenStream& stream);

[[nodiscard]] static std::unique_ptr<parse::Expr> process_operators(
    std::list<std::unique_ptr<parse::OpNode>>&& operators);
}  // namespace parse

std::unique_ptr<parse::Expr> parse::build_expr(TokenStream& stream) {
    auto operators = create_operators(stream);

    return process_operators(std::move(operators));
}

static std::list<std::unique_ptr<parse::OpNode>>
parse::create_operators(TokenStream& stream) {
    std::list<std::unique_ptr<OpNode>> operators;

    stream.run_until_stmt_end([&](const lex::Token& token) {
        operators.emplace_back(
            OpFactory::create_op_node(lex::Token(token)));
    });

    return operators;
}

static std::unique_ptr<parse::Expr> parse::process_operators(
    [[maybe_unused]] std::list<std::unique_ptr<parse::OpNode>>&&
        operators) {
    throw std::runtime_error("not implemented yet");
}
}  // namespace marex
