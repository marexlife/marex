#ifndef MAREX_PARSE_RETRUNNODE_H
#define MAREX_PARSE_RETRUNNODE_H
#include <optional>
#include <string>

#include "nodes/ast_node.h"
#include "token.h"
namespace marex::parse {
enum struct ExprKind : std::uint8_t;

class ReturnNode final : public AstNode {
   public:
    explicit ReturnNode(lex::Token&& token);

    [[nodiscard]] std::string as_c() override;

    void parse(TokenStream& stream) override;

   private:
    ExprKind expression_kind_{};
    std::optional<std::string> value_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_RETRUNNODE_H