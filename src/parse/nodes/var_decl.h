#ifndef MAREX_PARSE_VAR_NODE_H
#define MAREX_PARSE_VAR_NODE_H
#include <string>

#include "nodes/ast_node.h"
#include "token.h"
#include "type_kind.h"

namespace marex::parse {
class VarDecl final : public AstNode {
   public:
    explicit VarDecl(lex::Token&& token);

   protected:
    [[nodiscard]] std::string as_c() override;

    [[nodiscard]] static VarDecl parse(
        TokenStream& stream);

   private:
    VarDecl(lex::Token&& token, std::string&& name,
            std::string&& value, TypeKind type_kind);

    std::string name_;
    std::string value_;
    TypeKind type_kind_{};
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_VAR_NODE_H
