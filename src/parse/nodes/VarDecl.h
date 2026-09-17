#ifndef MAREX_PARSE_VAR_NODE_H
#define MAREX_PARSE_VAR_NODE_H
#include <string>

#include "expr_kind.h"
#include "nodes/ast_node.h"
#include "token.h"

namespace marex::parse {
class VarDecl final : public AstNode {
   public:
    explicit VarDecl(lex::Token&& token);

   protected:
    [[nodiscard]] std::string as_c() override;

    void parse(TokenStream& stream) override;

   private:
    std::string name_;
    ExprKind type_kind_{};
    std::string value_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_VAR_NODE_H
