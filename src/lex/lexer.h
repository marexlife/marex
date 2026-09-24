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
   public:
    Lexer() = default;
    ~Lexer() = default;

    Lexer(Lexer&&) = delete;
    Lexer& operator=(Lexer&&) = delete;
    Lexer(const Lexer&) = delete;
    Lexer& operator=(const Lexer&) = delete;

    [[nodiscard]] std::vector<Token> run(
        std::string&& source_text,
        std::optional<std::string_view> filename = std::nullopt);

   private:
    void push_token(std::vector<Token>& result,
                    SourcePos& source_pos);
    void reset(SourcePos& source_pos);
    void push_current(std::vector<Token>& result, char current,
                      SourcePos& source_pos);
    void push_token_and_current(std::vector<Token>& result,
                                char current, SourcePos& source_pos);

    void flush_without_add(std::vector<Token>& result,
                           SourcePos& source_pos);

    [[nodiscard]] bool is_flushable() {
        return last_char_kind_ == LastCharKind::WasDefault;
    }

    constexpr static std::size_t expected_token_amount_ = 100;
    std::optional<char> last_char_optional_ = std::nullopt;
    LastCharKind last_char_kind_ = LastCharKind::None;
    TokenFactory token_factory_{};
    std::string last_word_;
};
}  // namespace marex::lex
#endif  // MAREX_LEXER_LEXER_H
