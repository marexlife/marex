#include "Token.h"

#include <optional>
#include <utility>

#include "Logging.h"
#include "SourcePos.h"
#include "TokenKind.h"

namespace marex::lex {
Token::Token(
    [[maybe_unused]] core::Passkey<TokenFactory>&&
        passkey,
    std::string&& lexeme, TokenKind token_kind,
    SourcePos source_pos)
    : lexeme(std::move(lexeme)),
      kind(token_kind),
      source_pos(source_pos) {}

[[nodiscard]] std::optional<std::uint8_t> Token::get_binding_power()
    const {
    switch (kind) {
        case lex::TokenKind::Var: {
            return 30;
        } break;
        case lex::TokenKind::Identifier: {
            static const std::uint8_t binding_power =
                10;

            return binding_power;
        } break;
        case TokenKind::None:
            core::log_fatal_error("TokenKind is none");
        default:
            core::log_fatal_error(
                "TokenKind is Invalid");
    }
}

[[nodiscard]] std::string_view Token::get_lexeme()
    const {
    if (!lexeme) [[unlikely]] {
        core::log_fatal_internal_error(
            "trying to get lexeme when none is there");
    }

    return *lexeme;
}

[[nodiscard]] std::string Token::move_out_lexeme() {
    if (!lexeme) [[unlikely]] {
        core::log_fatal_internal_error(
            "trying to move out a lexeme when none "
            "exists");
    }

    return *lexeme;
}
}  // namespace marex::lex