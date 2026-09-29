#include "expr.h"

#include "nodes/ast_node.h"

namespace marex::parse {
Expr::Expr(std::reference_wrapper<lex::Token> token)
    : AstNode(token) {}
}  // namespace marex::parse