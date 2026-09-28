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

enum struct [[nodiscard]] TokenOpKind : std::uint8_t {
    None = 0,
    MonoOp,
    BinOp,
};

struct TokenOpInfo final {
    TokenOpInfo(BindingPower binding_power, TokenOpKind token_op_kind)
        : binding_power(binding_power),
          token_op_kind(token_op_kind) {}

    BindingPower binding_power{};
    TokenOpKind token_op_kind{};
};

class [[nodiscard]] Token final {
   public:
    Token([[maybe_unused]] core::Passkey<TokenFactory>&& passkey,
          std::string&& lexeme, TokenKind kind, SourcePos source_pos);

    // HAS TO BE IN HEADER
#ifdef TESTING
    Token(std::string&& lexeme, TokenKind kind)
        : lexeme_(std::move(lexeme)), kind_(kind) {}

    Token(TokenKind kind) : kind_(kind) {}
#endif

    Token(Token&&) = default;
    Token& operator=(Token&&) = delete;
    Token(const Token&) = delete;
    Token& operator=(const Token&) = delete;
    ~Token() = default;

    [[nodiscard]] std::string_view get_lexeme_or_throw() const;

    [[nodiscard]] std::string_view get_lexeme_or_empty_if_none()
        const;

    [[nodiscard]] std::string move_out_lexeme_or_throw();

    [[nodiscard]] std::optional<std::string>
    move_out_lexeme_or_none();

    [[nodiscard]] TokenKind get_kind() const { return kind_; }

    [[nodiscard]] bool operator==(const Token& other) const {
        return kind_ == other.kind_;
    }

    [[nodiscard]] bool operator!=(const Token& other) const {
        return kind_ != other.kind_;
    }

    [[nodiscard]] std::optional<TokenOpInfo> get_token_info_optional()
        const;

    [[nodiscard]] SourcePos get_pos() const { return source_pos_; }

   private:
    std::optional<std::string> lexeme_ = std::nullopt;
    TokenKind kind_{};
    SourcePos source_pos_;
};
}  // namespace marex::lex
#endif  // MAREX_LEX_TOKEN_H
