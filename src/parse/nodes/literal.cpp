#include "literal.h"

#include <utility>

#include "nodes/expr.h"
#include "token.h"

namespace marex::parse {
Literal::Literal(lex::Token&& token)
    : Expr(std::move(token)) {}
}  // namespace marex::parse