#ifndef MAREX_PARSE_LITERAL_H
#define MAREX_PARSE_LITERAL_H
#include "literal_kind.h"
#include "nodes/operand.h"
#include "token.h"

namespace marex::parse {
class Literal final : public Operand {
   public:
    explicit Literal(lex::Token&& token, LiteralKind literal_kind);

   private:
    LiteralKind literal_kind_{};
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_LITERAL_H