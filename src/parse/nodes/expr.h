#ifndef MAREX_PARSE_EXPR_H
#define MAREX_PARSE_EXPR_H
#include <concepts>

#include "nodes/ast_node.h"
#include "token.h"

namespace marex::parse {
class Expr : public AstNode {
   public:
    explicit Expr(lex::Token&& token);
    virtual ~Expr() = default;

    template <std::derived_from<Expr> Target>
    [[nodiscard]] Target& cast() {
        return static_cast<Target&>(*this);
    }

    Expr(Expr&&) = delete;
    Expr& operator=(Expr&&) = delete;
    Expr& operator=(const Expr&) = delete;
    Expr(const Expr&) = delete;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_EXPR_H
