#ifndef MAREX_PARSE_ASTNODE_H
#define MAREX_PARSE_ASTNODE_H
#include <optional>
#include <stdexcept>
#include <string_view>

#include "token.h"
#include "token_kind.h"
#include "token_stream.h"

namespace marex::parse {
class AstNode {
   public:
    explicit AstNode(lex::Token&& token);

    AstNode(AstNode&&) = default;
    AstNode& operator=(AstNode&&) = default;
    AstNode(const AstNode&) = delete;
    AstNode& operator=(const AstNode&) = delete;
    virtual ~AstNode() = default;

    virtual void parse([[maybe_unused]] TokenStream& stream) {
        throw std::runtime_error("this shouldn't have been called.");
    }

    // deliberately not = 0;
    [[nodiscard]] virtual std::string as_c() {
        return std::string{token_.get_lexeme_or_throw()};
    }

    [[nodiscard]] const lex::Token& get_token() const {
        return token_;
    }

    [[nodiscard]] std::optional<lex::BindingPower> get_binding_power()
        const {
        return token_.get_binding_power();
    }

    [[nodiscard]] lex::TokenKind get_kind() const {
        return token_.get_kind();
    }

    [[nodiscard]] std::string_view get_lexeme() const {
        return token_.get_lexeme_or_throw();
    }

   private:
    lex::Token token_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_ASTNODE_H
