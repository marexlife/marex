#ifndef MAREX_PARSE_RETRUNNODE_H
#define MAREX_PARSE_RETRUNNODE_H
#include <optional>
#include <string>

#include "AstNode.h"
#include "Token.h"

namespace marex::parse {
enum struct ExpressionKind : std::uint8_t;

class ReturnNode final : public AstNode {
   public:
    explicit ReturnNode(lex::Token&& token);

    [[nodiscard]] std::string as_c() override;

    void parse(TokenStream& pack) override;

   private:
    ExpressionKind expression_kind{};
    std::optional<std::string> value;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_RETRUNNODE_H