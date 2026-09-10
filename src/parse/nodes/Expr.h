#ifndef MAREX_PARSE_EXPR_H
#define MAREX_PARSE_EXPR_H
#include <cstdint>

#include "Token.h"

namespace marex::parse {
enum struct [[nodiscard]] ExprKind : std::uint8_t {
    Assignment,
    FuncCall,
    Var,
};

class Expr {
   public:
    explicit Expr(lex::Token&& token);

    const lex::Token& borrow_token() const {
        return token;
    }

    Expr(Expr&&) = delete;
    Expr& operator=(Expr&&) = delete;
    Expr& operator=(const Expr&) = delete;
    Expr(const Expr&) = delete;
    virtual ~Expr() = default;

   private:
    lex::Token token;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_EXPR_H
