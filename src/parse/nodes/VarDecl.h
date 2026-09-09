#ifndef MAREX_PARSE_VAR_NODE_H
#define MAREX_PARSE_VAR_NODE_H
#include <string>

#include "ExpressionKind.h"
#include "Token.h"
#include "TokenStream.h"
#include "nodes/Statement.h"

namespace marex::parse {
class VarDecl final : public Statement {
   public:
    explicit VarDecl(lex::Token&& token);

   protected:
    [[nodiscard]] std::string as_c() override;

    void parse(TokenStream& stream) override;

   private:
    std::string name;
    ExpressionKind type_kind{};
    std::string value;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_VAR_NODE_H
