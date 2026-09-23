#include "token.h"

#include <optional>
#include <utility>

#include "binding_power.h"
#include "logging.h"
#include "source_pos.h"
#include "token_kind.h"

namespace marex::lex {
Token::Token(
    [[maybe_unused]] core::Passkey<TokenFactory>&&
        passkey,
    std::string&& lexeme, TokenKind token_kind,
    SourcePos source_pos)
    : lexeme_(std::move(lexeme)),
      kind_(token_kind),
      source_pos_(source_pos) {}

std::optional<BindingPower> Token::get_binding_power()
    const {
    switch (kind_) {
        case lex::TokenKind::OpAdd:
            [[fallthrough]];
        case lex::TokenKind::OpSub:
            return std::optional<BindingPower>(
                BindingPower::AddSub);
        case lex::TokenKind::OpMul:
            [[fallthrough]];
        case lex::TokenKind::OpDiv:
            return std::optional<BindingPower>(
                BindingPower::MulDiv);
        case lex::TokenKind::Identifier:
            return BindingPower::Invalid;
        case TokenKind::None:
            core::log_fatal_error("TokenKind is none");
        default:
            return std::nullopt;
    }
}

[[nodiscard]] std::string_view Token::get_lexeme()
    const {
    if (!lexeme_) [[unlikely]] {
        core::log_fatal_internal_error(
            "trying to get lexeme when none is there");
    }

    return *lexeme_;
}

[[nodiscard]] std::pmr::string
Token::move_out_lexeme() {
    if (!lexeme_) [[unlikely]] {
        core::log_fatal_internal_error(
            "trying to move out a lexeme when none "
            "exists");
    }

    return *lexeme_;
}
}  // namespace marex::lex