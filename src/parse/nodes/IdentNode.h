#ifndef MAREX_PARSE_IDENTNODE_H
#define MAREX_PARSE_IDENTNODE_H
#include <string>

#include "AstNode.h"
#include "ParserPack.h"

namespace marex::parse {
class IdentNode final : public AstNode {
   public:
    explicit IdentNode(lex::Token&& token);

    [[nodiscard]] std::string as_c() override;

    void parse(TokenStream& pack) override;

   private:
    std::string value;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_IDENTNODE_H