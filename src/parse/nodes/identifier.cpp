#include "identifier.h"

#include <utility>

#include "nodes/expr.h"
#include "token.h"

namespace marex::parse {
Identifier::Identifier(lex::Token&& token)
    : Expr(std::move(token)) {}
}  // namespace marex::parse