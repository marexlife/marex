#ifndef MAREX_PARSE_EXPR_H
#define MAREX_PARSE_EXPR_H
#include <cstdint>

#include "Token.h"
#include "nodes/AstNode.h"

namespace marex::parse {
enum struct [[nodiscard]] ExprKind : std::uint8_t {
    Assignment,
    FuncCall,
    Var,
};

class Expr : public AstNode {
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
