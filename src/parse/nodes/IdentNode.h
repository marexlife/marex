#ifndef MAREX_PARSE_IDENTNODE_H
#define MAREX_PARSE_IDENTNODE_H
#include <string>

#include "AstNode.h"
#include "TokenStream.h"

namespace marex::parse {
class IdentNode final : public AstNode {
   public:
    explicit IdentNode(lex::Token&& token);

    [[nodiscard]] std::string as_c() override;

    void parse(TokenStream& stream) override;

   private:
    std::string value;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_IDENTNODE_H
