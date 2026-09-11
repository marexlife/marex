#ifndef MAREX_LEX_TOKEN_H
#define MAREX_LEX_TOKEN_H
#include <optional>
#include <string>
#include <string_view>

#include "Passkey.h"
#include "SourcePos.h"
#include "TokenKind.h"

namespace marex::lex
{
enum struct [[nodiscard]] BindingRank : std::uint8_t;

class [[nodiscard]] TokenFactory;
class [[nodiscard]] Token final
{
  public:
    Token([[maybe_unused]] core::Passkey<TokenFactory>
              &&passkey,
          std::string &&lexeme, TokenKind token_kind,
          SourcePos source_pos);

    [[nodiscard]] std::string_view get_lexeme() const;

    [[nodiscard]] std::string move_out_lexeme();

    [[nodiscard]] TokenKind GetKind() const
    {
        return kind;
    }

    [[nodiscard]] BindingRank get_binding_rank() const;
    [[nodiscard]] SourcePos get_pos() const
    {
        return source_pos;
    }

  private:
    std::optional<std::string> lexeme = std::nullopt;
    TokenKind kind{};
    SourcePos source_pos;
};
} // namespace marex::lex
#endif // MAREX_LEX_TOKEN_H
