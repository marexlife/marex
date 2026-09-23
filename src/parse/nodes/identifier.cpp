#include "identifier.h"

#include <utility>

#include "nodes/operand.h"
#include "token.h"

namespace marex::parse {
Identifier::Identifier(lex::Token&& token)
    : Operand(std::move(token)) {}
}  // namespace marex::parse