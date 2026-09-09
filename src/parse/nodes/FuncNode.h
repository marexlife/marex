#ifndef MAREX_PARSE_FUNCNODE_H
#define MAREX_PARSE_FUNCNODE_H
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "ExpressionKind.h"
#include "ParserPack.h"
#include "Token.h"
#include "nodes/ReturnNode.h"

namespace marex::parse {
struct FuncArg final {
    std::string arg_name;
    ExpressionKind arg_type{};
};

class FuncNode final : public AstNode {
   public:
    explicit FuncNode(lex::Token&& token);

   protected:
    [[nodiscard]] std::string as_c() override;
    void parse(TokenStream& pack) override;

   private:
    void parse_func_signature(TokenStream& pack);
    void parse_func_body(TokenStream& pack);

    void parse_func_args(TokenStream& pack);

    std::string func_name;
    ExpressionKind return_type{};
    std::vector<std::unique_ptr<AstNode>> func_items;
    std::optional<std::unique_ptr<ReturnNode>>
        return_node = std::nullopt;
    std::vector<FuncArg> args;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_FUNCNODE_H