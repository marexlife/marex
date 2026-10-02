#ifndef MAREX_PARSE_RETRUNNODE_H
#define MAREX_PARSE_RETRUNNODE_H
#include <memory>
#include <optional>
#include <string>

#include "nodes/ast_node.h"
#include "nodes/expr.h"
#include "token.h"

namespace marex::parse {
class ReturnNode final : public AstNode {
   public:
    explicit ReturnNode(lex::Token&& token);

    [[nodiscard]] std::string as_c() override;

    void parse(TokenStream& stream) override;

   private:
    std::optional<std::unique_ptr<Expr>> value_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_RETRUNNODE_H