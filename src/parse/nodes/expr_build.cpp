#include "expr_build.h"

#include <list>
#include <memory>
#include <stdexcept>
#include <utility>

#include "nodes/expr.h"
#include "nodes/op_node.h"
#include "nodes/op_node_factory.h"
#include "token.h"
#include "token_stream.h"

namespace marex {
std::unique_ptr<parse::Expr> parse::build_expr(TokenStream& stream) {
    std::list<std::unique_ptr<OpNode>> operators;

    stream.run_until_stmt_end([&](lex::Token token) {
        auto node = OpNodeFactory::create_node(std::move(token));

        operators.emplace_back(std::move(node));
    });

    throw std::runtime_error("not implemented yet");
}
}  // namespace marex
