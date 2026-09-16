#include "TokenKind.h"

#include <string_view>

#include "logging.h"

namespace marex {
[[nodiscard]] std::string_view lex::operator*(
    TokenKind token_kind) {
    switch (token_kind) {
        case TokenKind::Func:
            return "function keyword";
        case TokenKind::Colon:
            return ":";
        case TokenKind::Identifier:
            return "identifier";
        case TokenKind::IntDecl:
            return "Int Decl";
        case TokenKind::FloatDecl:
            return "Float Decl";
        case TokenKind::BoolDecl:
            return "Bool Decl";
        case TokenKind::IntLiteral:
            return "Int Literal";
        case TokenKind::FloatLiteral:
            return "Int Literal";
        case TokenKind::BoolLiteral:
            return "Bool Literal";
        case TokenKind::StringLiteral:
            return "String Literal";
        case TokenKind::Arrow:
            return "arrow";
        case TokenKind::Comma:
            return "comma";
        case TokenKind::Assignment:
            return "=";
        case TokenKind::StatementEnd:
            return ";";
        case TokenKind::Var:
            return "var";
        case TokenKind::OpenBrace:
            return "{";
        case TokenKind::CloseBrace:
            return "}";
        case TokenKind::OpenBracket:
            return "(";
        case TokenKind::CloseBracket:
            return ")";
        case TokenKind::Return:
            return "return";
        case TokenKind::None:
            goto end;
    }

end:
    core::log_fatal_internal_error(
        "Out of range TokenKind");
}
}  // namespace marex
