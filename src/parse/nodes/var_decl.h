#ifndef MAREX_PARSE_VAR_NODE_H
#define MAREX_PARSE_VAR_NODE_H
#include <string>

#include "expr_kind.h"
#include "nodes/ast_node.h"
#include "nodes/expr.h"
#include "token.h"
#include <memory>

namespace marex::parse {
class VarDecl final : public AstNode {
   public:
    explicit VarDecl(lex::Token&& token);

   protected:
    [[nodiscard]] std::string as_c() override;

    void parse(TokenStream& stream) override;

   private:
    std::string name_;
    TypeKind type_kind_{};
    std::shared_ptr<Expr> value_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_VAR_NODE_H
