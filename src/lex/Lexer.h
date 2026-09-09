#ifndef MAREX_LEX_LEXER_H
#define MAREX_LEX_LEXER_H
#include <cstddef>
#include <string>
#include <vector>

#include "LastCharKind.h"
#include "SourcePos.h"
#include "TokenFactory.h"

namespace marex::lex {
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

    [[nodiscard]] std::vector<Token> run(
        std::string&& source_text,
        std::optional<std::string> filename);

   private:
    void push_token(std::vector<Token>& result,
                    SourcePos& source_pos);
    void reset(SourcePos& source_pos);
    void push_current(std::vector<Token>& result,
                      char current,
                      SourcePos& source_pos);
    void push_token_and_current(std::vector<Token>& result,
                                char current,
                                SourcePos& source_pos);

    [[nodiscard]] bool is_flushable() const {
        return last_char_kind ==
               LastCharKind::WasDefault;
    }

    std::optional<char> last_char_optional =
        std::nullopt;
    LastCharKind last_char_kind = LastCharKind::None;
    TokenFactory token_factory{};
    std::string last_word;
};
}  // namespace marex::lex
#endif  // MAREX_LEXER_LEXER_H
