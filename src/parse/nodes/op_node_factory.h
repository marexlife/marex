#ifndef MAREX_PARSE_OPFACTORY_H
#define MAREX_PARSE_OPFACTORY_H
#include <memory>

#include "binary_op_kind.h"
#include "token.h"
#include "token_kind.h"

namespace marex::parse {
class OpNode;

class OpNodeFactory final {
   public:
    [[nodiscard]] static std::unique_ptr<OpNode> create_node(
        lex::Token&& token);

   private:
    [[nodiscard]] static std::unique_ptr<OpNode> create_operator(
        lex::Token&& token, lex::TokenOpInfo token_op_info);

    [[nodiscard]] static std::unique_ptr<OpNode> create_operand(
        lex::Token&& token);

    [[nodiscard]] static BinaryOpKind to_binary_op_kind(
        lex::TokenKind token_kind);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_OPFACTORY_H