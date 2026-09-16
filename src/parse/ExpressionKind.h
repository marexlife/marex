#ifndef MAREX_PARSE_EXPRESSIONKIND_H
#define MAREX_PARSE_EXPRESSIONKIND_H
#include <cstdint>
#include <source_location>
#include <string_view>

namespace marex::parse {
class TokenStream;

enum class ExpressionKind : std::uint8_t {
    None = 0,
    Identifier,
    EmptyType,
    IntType,
    BoolType,
    FloatType,
    StringType,
};

[[nodiscard]] std::string_view operator*(
    ExpressionKind kind);

ExpressionKind expression_kind_from_decl_or_throw(
    const parse::TokenStream& pack,
    std::source_location cpp_source_location =
        std::source_location::current());

ExpressionKind expression_kind_from_literal_or_throw(
    const parse::TokenStream& pack,
    std::source_location cpp_source_location =
        std::source_location::current());
}  // namespace marex::parse
#endif  // MAREX_PARSE_EXPRESSIONKIND_H