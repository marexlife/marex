#include "Expr.h"

#include <utility>

#include "Token.h"

namespace marex::parse {
Expr::Expr(lex::Token&& token)
    : token(std::move(token)) {}
}  // namespace marex::parse