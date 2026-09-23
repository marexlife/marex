#ifndef MAREX_PARSE_LITERAL_H
#define MAREX_PARSE_LITERAL_H
#include "nodes/operand.h"
#include "token.h"

namespace marex::parse {
class Literal final : public Operand {
   public:
    explicit Literal(lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_LITERAL_H