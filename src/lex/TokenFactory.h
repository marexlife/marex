#ifndef MAREX_LEX_TOKENFACTORY_H
#define MAREX_LEX_TOKENFACTORY_H
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "token.h"
#include "TokenKind.h"

namespace marex::lex {
class TokenFactory final {
   public:
    TokenFactory();

    TokenFactory(TokenFactory&&) = delete;
    TokenFactory& operator=(TokenFactory&&) = delete;
    TokenFactory(const TokenFactory&) = delete;
    TokenFactory& operator=(const TokenFactory&) =
        delete;
    ~TokenFactory() = default;

    [[nodiscard]] Token create_token(
        std::string&& source_word,
        SourcePos source_pos);

   private:
    [[nodiscard]] TokenKind map(
        std::string_view source_word);

    [[nodiscard]] static std::optional<TokenKind>
    try_convert_to_number(
        std::string_view source_word) {
        try {
            [[maybe_unused]] auto ignored =
                std::stoi(source_word.data());

            return std::optional<TokenKind>{
                TokenKind::IntLiteral,
            };
        } catch (...) {
            return std::nullopt;
        }
    }

    std::pmr::unordered_map<std::string_view,
                            TokenKind>
        mapping;
};
}  // namespace marex::lex
#endif  // MAREX_LEX_TOKENFACTORY_H
