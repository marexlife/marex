#ifndef MAREX_PARSE_FUNCCALL_H
#define MAREX_PARSE_FUNCCALL_H
#include <string>
#include <utility>
#include <vector>

#include "expr_kind.h"
#include "nodes/expr.h"
#include "token.h"

namespace marex::parse {
struct CallArg final {
    std::string name;
    TypeKind expression_kind{};
};

class FuncCall final : public Expr {
   public:
    static FuncCall parse(TokenStream& stream);

   protected:
    [[nodiscard]] std::string as_c() override;

   private:
    FuncCall(lex::Token&& token,
             std::string&& func_name,
             std::vector<CallArg>&& args);

    std::string func_name_;
    std::vector<CallArg> args_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_FUNCCALL_H
