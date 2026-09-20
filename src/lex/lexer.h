#ifndef MAREX_LEX_LEXER_H
#define MAREX_LEX_LEXER_H
#include <cstddef>
#include <optional>
#include <string>
#include <vector>

#include "source_pos.h"
#include "token_factory.h"

namespace marex::lex {
enum class [[nodiscard]] LastCharKind : std::uint8_t {
    None,
    WasDefault,
    WasNotDefault,
};

class [[nodiscard]] Lexer final {
    constexpr static std::size_t vector_default_size =
        100;

   public:
    Lexer() = default;
    Lexer(Lexer&&) = delete;
    Lexer& operator=(Lexer&&) = delete;
    Lexer(const Lexer&) = delete;
    Lexer& operator=(const Lexer&) = delete;
    ~Lexer() = default;

    [[nodiscard]] std::pmr::vector<Token> run(
        this Lexer& self,
        std::pmr::string&& source_text,
        std::optional<std::string_view> filename = std::nullopt);

   private:
    void push_token(this Lexer& self,
                    std::pmr::vector<Token>& result,
                    SourcePos& source_pos);
    void reset(this Lexer& self,
               SourcePos& source_pos);
    void push_current(this Lexer& self,
                      std::pmr::vector<Token>& result,
                      char current,
                      SourcePos& source_pos);
    void push_token_and_current(
        this Lexer& self,
        std::pmr::vector<Token>& result, char current,
        SourcePos& source_pos);

    [[nodiscard]] bool is_flushable(
        this const Lexer& self) {
        return self.last_char_kind ==
               LastCharKind::WasDefault;
    }

    std::optional<char> last_char_optional =
        std::nullopt;
    LastCharKind last_char_kind = LastCharKind::None;
    TokenFactory token_factory{};
    std::pmr::string last_word;
};
}  // namespace marex::lex
#endif  // MAREX_LEXER_LEXER_H
