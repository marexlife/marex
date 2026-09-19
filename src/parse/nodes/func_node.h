#ifndef MAREX_PARSE_FUNCNODE_H
#define MAREX_PARSE_FUNCNODE_H
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "expr_kind.h"
#include "nodes/ast_node.h"
#include "nodes/expr.h"
#include "return_node.h"
#include "token.h"

namespace marex::parse {
class ReturnNode;

struct FuncArg final {
    std::pmr::string arg_name;
    ExprKind arg_type{};
};

class FuncNode final : public Expr {
   public:
    explicit FuncNode(lex::Token&& token);

   protected:
    [[nodiscard]] std::string as_c() override;
    std::expected<void, std::unique_ptr<core::Error>>
    parse(TokenStream& stream) override;

   private:
    std::expected<void, std::unique_ptr<core::Error>>
    parse_func_signature(TokenStream& stream);
    std::expected<void, std::unique_ptr<core::Error>>
    parse_func_body(TokenStream& stream);

    std::expected<void, std::unique_ptr<core::Error>>
    parse_func_args(TokenStream& stream);

    std::string func_name_;
    ExprKind return_type_{};
    std::vector<std::unique_ptr<AstNode>> func_items_;
    std::optional<std::unique_ptr<ReturnNode>>
        return_node_;
    std::vector<FuncArg> args_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_FUNCNODE_H