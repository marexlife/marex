#ifndef MAREX_LEX_TOKENPOS_H
#define MAREX_LEX_TOKENPOS_H
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace marex::lex {
struct SourcePos final {
    explicit SourcePos(
        std::optional<std::string_view> filename);

    void advance_column();
    void advance_line();
    void reset();

    [[nodiscard]] std::string as_string() const;

   private:
    std::uintmax_t line = 1;
    std::uintmax_t column = 1;
    std::optional<std::string_view> filename;
};
}  // namespace marex::lex
#endif  // MAREX_LEX_TOKENPOS_H
