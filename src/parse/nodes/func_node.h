#ifndef MAREX_PARSE_FUNCNODE_H
#define MAREX_PARSE_FUNCNODE_H
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "type_kind.h"
#include "nodes/ast_node.h"
#include "nodes/expr.h"
#include "return_node.h"
#include "token.h"

namespace marex::parse {
struct FuncArg final {
    std::string arg_name;
    TypeKind arg_type{};
};

class FuncNode final : public Expr {
   public:
    [[nodiscard]] static FuncNode parse(
        TokenStream& stream);

   protected:
    [[nodiscard]] std::string as_c() override;

   private:
    void parse_func_signature(TokenStream& stream);
    void parse_func_body(TokenStream& stream);

    void parse_func_args(TokenStream& stream);

    std::string func_name_;
    TypeKind return_type_{};
    std::vector<std::unique_ptr<AstNode>> func_items_;
    ReturnNode return_node_;
    std::vector<FuncArg> args_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_FUNCNODE_H