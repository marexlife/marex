#ifndef MAREX_PARSE_FUNCCALL_H
#define MAREX_PARSE_FUNCCALL_H
#include <expected>
#include <memory>
#include <string>
#include <vector>

#include "error.h"
#include "expr_kind.h"
#include "nodes/expr.h"
#include "token.h"

namespace marex::parse {
struct CallArg final {
    std::string name;
    ExprKind expression_kind{};
};

class FuncCall final : public Expr {
   public:
    explicit FuncCall(lex::Token&& token);

    [[nodiscard]] std::string as_c() override;

    std::expected<void, std::unique_ptr<core::Error>>
    parse(TokenStream& stream) override;

   private:
    std::string func_name;
    std::vector<CallArg> args;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_FUNCCALL_H
