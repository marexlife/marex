#include "literal.h"

#include <utility>

#include "nodes/operand.h"
#include "token.h"

namespace marex::parse {
Literal::Literal(lex::Token&& token, LiteralKind literal_kind)
    : Operand(std::move(token)), literal_kind_(literal_kind) {}
}  // namespace marex::parse