#ifndef MAREX_LEX_TOKEN_H
#define MAREX_LEX_TOKEN_H
#include <optional>
#include <string>
#include <string_view>

#include "passkey.h"
#include "source_pos.h"
#include "token_kind.h"

namespace marex::lex {
enum struct BindingPower : std::uint8_t;
class TokenFactory;

namespace tests {
class LexTester;
}

class [[nodiscard]] Token final {
   public:
    Token([[maybe_unused]] core::Passkey<TokenFactory>&& passkey,
          std::string&& lexeme, TokenKind kind, SourcePos source_pos);

    Token([[maybe_unused]] core::Passkey<tests::LexTester>&& passkey,
          std::string&& lexeme, TokenKind kind);

    Token([[maybe_unused]] core::Passkey<tests::LexTester>&& passkey,
          TokenKind kind);

    [[nodiscard]] std::string_view get_lexeme_or_throw() const;

    [[nodiscard]] std::string_view get_lexeme_or_empty_if_none()
        const;

    [[nodiscard]] std::pmr::string move_out_lexeme();

    [[nodiscard]] TokenKind get_kind() const { return kind_; }

    [[nodiscard]] bool operator==(const Token& other) const {
        return kind_ == other.kind_;
    }

    [[nodiscard]] bool operator!=(const Token& other) const {
        return kind_ != other.kind_;
    }

    [[nodiscard]] std::optional<BindingPower> get_binding_power()
        const;

    [[nodiscard]] SourcePos get_pos() const { return source_pos_; }

   private:
    std::optional<std::pmr::string> lexeme_ = std::nullopt;
    TokenKind kind_{};
    SourcePos source_pos_;
};
}  // namespace marex::lex
#endif  // MAREX_LEX_TOKEN_H
