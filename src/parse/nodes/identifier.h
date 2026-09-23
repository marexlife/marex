#ifndef MAREX_PARSE_IDENTIFIER_H
#define MAREX_PARSE_IDENTIFIER_H
#include "nodes/operand.h"
#include "token.h"

namespace marex::parse {
class Identifier final : public Operand {
   public:
    explicit Identifier(lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_IDENTIFIER_H