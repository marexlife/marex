#ifndef MAREX_LEX_TOKENFACTORY_H
#define MAREX_LEX_TOKENFACTORY_H
#include <charconv>
#include <optional>
#include <string_view>
#include <system_error>
#include <type_traits>
#include <unordered_map>

#include "Token.h"
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

    template <typename NumberType,
              TokenKind OutputValue>
        requires std::is_arithmetic_v<NumberType>
    [[nodiscard]] std::optional<TokenKind>
    try_convert_to_number(
        std::string_view source_word) {
        NumberType target{};

        if (std::from_chars(source_word.begin(),
                            source_word.end(), target)
                .ec == std::errc{}) {
            return std::optional<TokenKind>{
                OutputValue,
            };
        }

        return std::nullopt;
    }

    std::pmr::unordered_map<std::string_view,
                            TokenKind>
        mapping;
};
}  // namespace marex::lex
#endif  // MAREX_LEX_TOKENFACTORY_H
