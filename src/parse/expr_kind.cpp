#include "expr_kind.h"

#include <source_location>
#include <stdexcept>

#include "nodes/exceptions/invalid_token_exception.h"
#include "token_kind.h"
#include "token_stream.h"

namespace marex {
[[nodiscard]] std::string_view parse::operator*(
    ExprKind token_kind) {
    switch (token_kind) {
        case ExprKind::EmptyType:
            return "void";
        case ExprKind::IntType:
            return "int32_t";
        case ExprKind::FloatType:
            return "float";
        case ExprKind::BoolType:
            return "bool";
        case marex::parse::ExprKind::StringType:
            return "str";
        case ExprKind::Identifier:
            return "identifier";
        case ExprKind::None:
            break;
    }

    throw std::out_of_range("Not a valid TypeKind");
}

parse::ExprKind
parse::expression_kind_from_decl_or_throw(
    const parse::TokenStream& pack,
    std::source_location cpp_source_location) {
    switch (pack.get_kind()) {
        case marex::lex::TokenKind::Int32Decl:
            return ExprKind::IntType;
        case marex::lex::TokenKind::BoolDecl:
            return ExprKind::BoolType;
        case marex::lex::TokenKind::FloatDecl:
            return ExprKind::FloatType;
        default:
            throw InvalidTokenException(
                pack.get_pos(), pack.get_kind(),
                "expected a type",
                cpp_source_location);
    }
}

parse::ExprKind
parse::expression_kind_from_literal_or_throw(
    const parse::TokenStream& pack,
    std::source_location cpp_source_location) {
    switch (pack.get_kind()) {
        case marex::lex::TokenKind::IntLiteral:
            return ExprKind::IntType;
        case marex::lex::TokenKind::BoolLiteral:
            return ExprKind::BoolType;
        case marex::lex::TokenKind::FloatLiteral:
            return ExprKind::FloatType;
        case marex::lex::TokenKind::StringLiteral:
            return ExprKind::StringType;
        default:
            throw InvalidTokenException(
                pack.get_pos(), pack.get_kind(),
                "expected a type",
                cpp_source_location);
    }
}
}  // namespace marex