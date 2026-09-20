#ifndef MAREX_LEX_TOKEN_H
#define MAREX_LEX_TOKEN_H
#include <optional>
#include <string>
#include <string_view>

#include "passkey.h"
#include "source_pos.h"
#include "token_kind.h"

namespace marex::lex {
enum struct BindingRank : std::uint8_t;

class [[nodiscard]] TokenFactory;
class [[nodiscard]] Token final {
   public:
    Token([[maybe_unused]] core::Passkey<
              TokenFactory>&& passkey,
          std::string&& lexeme, TokenKind token_kind,
          SourcePos source_pos);

    [[nodiscard]] std::string_view get_lexeme() const;

    [[nodiscard]] std::pmr::string move_out_lexeme();

    [[nodiscard]] TokenKind get_kind() const {
        return kind_;
    }

    auto operator==(const Token& other) const {
        return kind_ == other.kind_;
    }

    [[nodiscard]] BindingRank get_binding_rank() const;
    [[nodiscard]] SourcePos get_pos() const {
        return source_pos_;
    }

   private:
    std::optional<std::pmr::string> lexeme_ =
        std::nullopt;
    TokenKind kind_{};
    SourcePos source_pos_;
};
}  // namespace marex::lex
#endif  // MAREX_LEX_TOKEN_H
