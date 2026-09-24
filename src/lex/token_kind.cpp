#include "token_kind.h"

#include <string_view>

#include "logging.h"

namespace marex {
[[nodiscard]] std::string_view lex::operator*(TokenKind token_kind) {
    switch (token_kind) {
        case TokenKind::Colon:
            return ":";

        case TokenKind::OpAdd:
            return "OpAdd";
        case TokenKind::OpSub:
            return "OpSub";
        case TokenKind::OpMul:
            return "OpMul";
        case TokenKind::OpDiv:
            return "OpDiv";

        case TokenKind::OpAddAssign:
            return "OpAddAssign";
        case TokenKind::OpSubAssign:
            return "OpSubAssign";
        case TokenKind::OpMulAssign:
            return "OpMulAssign";
        case TokenKind::OpDivAssign:
            return "OpDivAssign";

        case TokenKind::Identifier:
            return "Identifier";
        case TokenKind::Int8Decl:
            return "Int8Decl";
        case TokenKind::Int16Decl:
            return "Int16Decl";
        case TokenKind::Int32Decl:
            return "Int32Decl";
        case TokenKind::Int64Decl:
            return "Int64Decl";
        case TokenKind::FloatDecl:
            return "FloatDecl";
        case TokenKind::DoubleDecl:
            return "DoubleDecl";
        case TokenKind::BoolDecl:
            return "BoolDecl";
        case TokenKind::IntLiteral:
            return "IntLiteral";
        case TokenKind::FloatLiteral:
            return "IntLiteral";
        case TokenKind::BoolLiteral:
            return "BoolLiteral";
        case TokenKind::StringLiteral:
            return "StringLiteral";
        case TokenKind::Arrow:
            return "Arrow";
        case TokenKind::Comma:
            return "Comma";
        case TokenKind::Assignment:
            return "Assignment";
        case TokenKind::StatementEnd:
            return "StatementEnd";
        case TokenKind::Var:
            return "Var";
        case TokenKind::Val:
            return "Val";
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
            break;
    }

    core::log_fatal_internal_error("Out of range TokenKind");
}
}  // namespace marex
