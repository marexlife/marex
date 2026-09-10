#ifndef MAREX_PARSE_ASTNODE_H
#define MAREX_PARSE_ASTNODE_H
#include <stdexcept>
#include <string_view>

#include "Token.h"
#include "TokenKind.h"
#include "TokenStream.h"

namespace marex::parse {
class AstNode {
   public:
    explicit AstNode(lex::Token&& token);

    AstNode(AstNode&&) = default;
    AstNode& operator=(AstNode&&) = default;
    AstNode(const AstNode&) = delete;
    AstNode& operator=(const AstNode&) = delete;
    virtual ~AstNode() = default;

    virtual void parse(
        [[maybe_unused]] TokenStream& stream) {
        throw std::runtime_error(
            "this shouldn't have been called.");
    }

    // deliberately not = 0;
    [[nodiscard]] virtual std::string as_c() {
        throw std::runtime_error(
            "this shouldn't have been called.");
    }

    // deliberately not = 0;
    [[nodiscard]] const lex::Token& get_token() const {
        return token;
    }

    [[nodiscard]] lex::BindingRank get_binding_rank()
        const {
        return token.get_binding_rank();
    }

    [[nodiscard]] lex::TokenKind get_kind() const {
        return token.get_kind();
    }

    [[nodiscard]] std::string_view get_lexeme() const {
        return token.get_lexeme();
    }

   private:
    lex::Token token;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_ASTNODE_H
