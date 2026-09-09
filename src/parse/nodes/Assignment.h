#ifndef MAREX_PARSE_ASSIGNMENT_H
#define MAREX_PARSE_ASSIGNMENT_H
#include <memory>
#include <optional>

#include "TokenStream.h"
#include "Token.h"
#include "nodes/Expr.h"

namespace marex::parse {
class Assignment final : public Expr {
   public:
    explicit Assignment(lex::Token&& token);

    [[nodiscard]] std::string as_c() override;

    void parse(TokenStream& stream) override;

   private:
    void parse_lhs(TokenStream& stream);
    void parse_rhs(TokenStream& stream);

    std::optional<std::unique_ptr<Expr>> lhs =
        std::nullopt;
    std::optional<std::unique_ptr<Expr>> rhs =
        std::nullopt;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_ASSIGNMENT_H