#ifndef MAREX_PARSE_EXPR_H
#define MAREX_PARSE_EXPR_H
#include "AstNode.h"
#include "Token.h"

namespace marex::parse {
class Expr : public AstNode {
   public:
    explicit Expr(lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_EXPR_H
