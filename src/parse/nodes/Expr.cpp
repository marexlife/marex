#include "Expr.h"

#include <utility>

#include "nodes/ast_node.h"

namespace marex::parse {
Expr::Expr(lex::Token&& token)
    : AstNode(std::move(token)) {}
}  // namespace marex::parse