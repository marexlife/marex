#include "literal.h"

#include <utility>

#include "nodes/operand.h"
#include "token.h"

namespace marex::parse {
Literal::Literal(lex::Token&& token)
    : Operand(std::move(token)) {}
}  // namespace marex::parse