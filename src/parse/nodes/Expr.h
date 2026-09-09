#ifndef MAREX_PARSE_EXPR_H
#define MAREX_PARSE_EXPR_H
#include "Token.h"

namespace marex::parse {
class Expr {
   public:
    explicit Expr(lex::Token&& token);

    Expr(Expr&&) = delete;
    Expr& operator=(Expr&&) = delete;
    Expr& operator=(const Expr&) = delete;
    Expr(const Expr&) = delete;
    virtual ~Expr() = default;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_EXPR_H
