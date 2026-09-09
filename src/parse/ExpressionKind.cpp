#include "ExpressionKind.h"

#include <source_location>
#include <stdexcept>

#include "TokenStream.h"
#include "TokenKind.h"
#include "nodes/exceptions/InvalidTokenException.h"

namespace marex {
[[nodiscard]] std::string_view parse::operator*(
    ExpressionKind token_kind) {
    switch (token_kind) {
        case ExpressionKind::EmptyType:
            return "void";
        case ExpressionKind::IntType:
            return "int32_t";
        case ExpressionKind::FloatType:
            return "float";
        case ExpressionKind::BoolType:
            return "bool";
        case marex::parse::ExpressionKind::StringType:
            return "str";
        case ExpressionKind::Identifier:
            return "identifier";
        case ExpressionKind::None:
            goto end;
    }

end:
    throw std::out_of_range("Not a valid TypeKind");
}

parse::ExpressionKind
parse::expression_kind_from_decl_or_throw(
    const parse::TokenStream& pack,
    std::source_location cpp_source_location) {
    switch (pack.get_kind()) {
        case marex::lex::TokenKind::IntDecl:
            return ExpressionKind::IntType;
        case marex::lex::TokenKind::BoolDecl:
            return ExpressionKind::BoolType;
        case marex::lex::TokenKind::FloatDecl:
            return ExpressionKind::FloatType;
        default:
            throw InvalidTokenException(
                pack.get_pos(), pack.get_kind(),
                "expected a type",
                cpp_source_location);
    }
}

parse::ExpressionKind
parse::expression_kind_from_literal_or_throw(
    const parse::TokenStream& pack,
    std::source_location cpp_source_location) {
    switch (pack.get_kind()) {
        case marex::lex::TokenKind::IntLiteral:
            return ExpressionKind::IntType;
        case marex::lex::TokenKind::BoolLiteral:
            return ExpressionKind::BoolType;
        case marex::lex::TokenKind::FloatLiteral:
            return ExpressionKind::FloatType;
        case marex::lex::TokenKind::StringLiteral:
            return ExpressionKind::StringType;
        default:
            throw InvalidTokenException(
                pack.get_pos(), pack.get_kind(),
                "expected a type",
                cpp_source_location);
    }
}
}  // namespace marex