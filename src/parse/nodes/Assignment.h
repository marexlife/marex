#ifndef MAREX_PARSE_ASSIGNMENT_H
#define MAREX_PARSE_ASSIGNMENT_H
#include <memory>
#include <optional>

#include "Token.h"
#include "nodes/Expr.h"

namespace marex::parse {
class Assignment final : public Expr {
   public:
    explicit Assignment(lex::Token&& token);

    void set_lhs(std::unique_ptr<Expr> lhs);
    void set_rhs(std::unique_ptr<Expr> rhs);

   private:
    std::optional<std::unique_ptr<Expr>> lhs =
        std::nullopt;
    std::optional<std::unique_ptr<Expr>> rhs =
        std::nullopt;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_ASSIGNMENT_H