#ifndef MAREX_PARSE_FUNCCALL_H
#define MAREX_PARSE_FUNCCALL_H
#include <string>
#include <vector>

#include "ExpressionKind.h"
#include "Token.h"
#include "nodes/Expression.h"

namespace marex::parse {
struct CallArg final {
    std::string name;
    ExpressionKind expression_kind{};
};

class FuncCall final : public Expression {
   public:
    explicit FuncCall(lex::Token&& token);

    [[nodiscard]] std::string as_c() override;

    void parse(ParserPack& pack) override;

   private:
    std::string func_name;
    std::vector<CallArg> args;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_FUNCCALL_H