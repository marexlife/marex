#ifndef MAREX_PARSE_IDENTIFIER_H
#define MAREX_PARSE_IDENTIFIER_H
#include "nodes/expr.h"
#include "token.h"

namespace marex::parse {
class Identifier final : public Expr {
   public:
    explicit Identifier(lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_IDENTIFIER_H