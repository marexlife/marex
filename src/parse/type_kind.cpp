#include "type_kind.h"

#include <source_location>
#include <stdexcept>

#include "nodes/exceptions/invalid_token_exception.h"
#include "token_kind.h"
#include "token_stream.h"

namespace marex {
[[nodiscard]] std::string_view parse::operator*(
    TypeKind token_kind) {
    switch (token_kind) {
        case TypeKind::EmptyType:
            return "void";
        case TypeKind::IntType:
            return "int32_t";
        case TypeKind::FloatType:
            return "float";
        case TypeKind::BoolType:
            return "bool";
        case marex::parse::TypeKind::StringType:
            return "str";
        case TypeKind::VoidType:
            return "void type";
        case TypeKind::None:
            break;
    }

    throw std::out_of_range("Not a valid TypeKind");
}

parse::TypeKind
parse::expression_kind_from_decl_or_throw(
    const parse::TokenStream& pack,
    std::source_location cpp_source_location) {
    switch (pack.get_kind()) {
        case marex::lex::TokenKind::IntDecl:
            return TypeKind::IntType;
        case marex::lex::TokenKind::BoolDecl:
            return TypeKind::BoolType;
        case marex::lex::TokenKind::FloatDecl:
            return TypeKind::FloatType;
        default:
            throw InvalidTokenException(
                pack.get_pos(), pack.get_kind(),
                "expected a type",
                cpp_source_location);
    }
}

parse::TypeKind
parse::expression_kind_from_literal_or_throw(
    const parse::TokenStream& pack,
    std::source_location cpp_source_location) {
    switch (pack.get_kind()) {
        case marex::lex::TokenKind::IntLiteral:
            return TypeKind::IntType;
        case marex::lex::TokenKind::BoolLiteral:
            return TypeKind::BoolType;
        case marex::lex::TokenKind::FloatLiteral:
            return TypeKind::FloatType;
        case marex::lex::TokenKind::StringLiteral:
            return TypeKind::StringType;
        default:
            throw InvalidTokenException(
                pack.get_pos(), pack.get_kind(),
                "expected a type",
                cpp_source_location);
    }
}
}  // namespace marex