#ifndef MAREX_PARSE_PARSER_H
#define MAREX_PARSE_PARSER_H
#include <cstddef>
#include <vector>

#include "TokenStream.h"
#include "Token.h"
#include "TranslationUnit.h"

namespace marex::parse {
class Parser final {
    static const std::size_t nodes_default_reserve
        = 100;

public:
    Parser() = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(Parser&&) = delete;
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    ~Parser() = delete;

    [[nodiscard]] static TranslationUnit run(
        std::vector<lex::Token>&& tokens);

private:
    [[nodiscard]] static TranslationUnit parse(
        TokenStream&& stream);
};
} // namespace marex::parse
#endif // MAREX_PARSE_PARSER_H
