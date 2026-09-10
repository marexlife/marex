#ifndef MAREX_PARSE_RETRUNNODE_H
#define MAREX_PARSE_RETRUNNODE_H
#include <optional>
#include <string>

#include "Token.h"
#include "nodes/AstNode.h"
#include "nodes/Statement.h"

namespace marex::parse {
enum struct ExpressionKind : std::uint8_t;

class ReturnNode final : public AstNode,
                         public Statement {
   public:
    explicit ReturnNode(lex::Token&& token);

    [[nodiscard]] std::string as_c() override;

    void parse(TokenStream& stream) override;

   private:
    ExpressionKind expression_kind{};
    std::optional<std::string> value;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_RETRUNNODE_H