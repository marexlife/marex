#ifndef MAREX_PARSE_ASSIGNMENT_H
#define MAREX_PARSE_ASSIGNMENT_H
#include <memory>
#include <optional>

#include "ParserPack.h"
#include "Token.h"
#include "nodes/Expr.h"

namespace marex::parse {
class Assignment final : public Expr {
   public:
    explicit Assignment(lex::Token&& token);

    [[nodiscard]] std::string as_c() override;

    void parse(ParserPack& pack) override;

   private:
    void parse_lhs(ParserPack& pack);
    void parse_rhs(ParserPack& pack);

    std::optional<std::unique_ptr<Expr>> lhs =
        std::nullopt;
    std::optional<std::unique_ptr<Expr>> rhs =
        std::nullopt;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_ASSIGNMENT_H