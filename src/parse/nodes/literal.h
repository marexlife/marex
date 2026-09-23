#ifndef MAREX_PARSE_LITERAL_H
#define MAREX_PARSE_LITERAL_H
#include "nodes/expr.h"
#include "token.h"

namespace marex::parse {
class Literal final : public Expr {
   public:
    explicit Literal(lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_LITERAL_H