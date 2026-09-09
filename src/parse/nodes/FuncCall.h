#ifndef MAREX_PARSE_FUNCCALL_H
#define MAREX_PARSE_FUNCCALL_H
#include <string>
#include <vector>

#include "ExpressionKind.h"
#include "Token.h"
#include "nodes/Expr.h"

namespace marex::parse {
struct CallArg final {
    std::string name;
    ExpressionKind expression_kind{};
};

class FuncCall final : public Expr {
   public:
    explicit FuncCall(lex::Token&& token);

    [[nodiscard]] std::string as_c() override;

    void parse(TokenStream& stream) override;

   private:
    std::string func_name;
    std::vector<CallArg> args;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_FUNCCALL_H
