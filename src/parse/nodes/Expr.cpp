#include "Expr.h"

#include <utility>

#include "nodes/AstNode.h"

namespace marex::parse {
Expr::Expr(lex::Token&& token)
    : AstNode(std::move(token)) {}
}  // namespace marex::parse