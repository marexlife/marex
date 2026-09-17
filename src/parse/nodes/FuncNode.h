#ifndef MAREX_PARSE_FUNCNODE_H
#define MAREX_PARSE_FUNCNODE_H
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "expr_kind.h"
#include "nodes/AstNode.h"
#include "nodes/Expr.h"
#include "nodes/ReturnNode.h"
#include "token.h"

namespace marex::parse {
struct FuncArg final {
    std::pmr::string arg_name;
    ExprKind arg_type{};
};

class FuncNode final : public Expr {
   public:
    explicit FuncNode(lex::Token&& token);

   protected:
    [[nodiscard]] std::string as_c() override;
    void parse(TokenStream& stream) override;

   private:
    void parse_func_signature(TokenStream& stream);
    void parse_func_body(TokenStream& stream);

    void parse_func_args(TokenStream& stream);

    std::string func_name;
    ExprKind return_type{};
    std::vector<std::unique_ptr<AstNode>> func_items;
    std::optional<std::unique_ptr<ReturnNode>>
        return_node = std::nullopt;
    std::vector<FuncArg> args;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_FUNCNODE_H