#ifndef MAREX_LEX_TOKENKIND_H
#define MAREX_LEX_TOKENKIND_H
#include <cstdint>
#include <string_view>

namespace marex::lex {
enum struct [[nodiscard]] TokenKind : std::uint8_t {
    None = 0,
    Identifier,
    Assignment,
    Var,
    Return,

    IntDecl,
    FloatDecl,
    BoolDecl,

    StringLiteral,
    IntLiteral,
    FloatLiteral,
    BoolLiteral,

    Func,
    StatementEnd,

    Arrow,

    Colon,
    Comma,

    OpenBrace,
    CloseBrace,

    OpenBracket,
    CloseBracket,
};

[[nodiscard]] std::string_view operator*(
    TokenKind token_kind);
}  // namespace marex::lex
#endif  // MAREX_LEX_TOKENKIND_H
