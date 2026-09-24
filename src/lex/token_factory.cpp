#include "token_factory.h"

#include <string_view>

#include "passkey.h"
#include "source_pos.h"
#include "token.h"
#include "token_kind.h"

namespace marex::lex {
TokenFactory::TokenFactory()
    : mapping{
          {
              {"var", TokenKind::Var},
              {"val", TokenKind::Var},

              {"float", TokenKind::FloatDecl},
              {"double", TokenKind::DoubleDecl},
              {"int8", TokenKind::Int8Decl},
              {"int16", TokenKind::Int16Decl},
              {"int32", TokenKind::Int32Decl},
              {"int", TokenKind::Int32Decl},
              {"int64", TokenKind::Int64Decl},
              {"bool", TokenKind::BoolDecl},

              {"+", TokenKind::OpAdd},
              {"-", TokenKind::OpSub},
              {"*", TokenKind::OpMul},
              {"/", TokenKind::OpDiv},

              {"+=", TokenKind::OpAddAssign},
              {"-=", TokenKind::OpSubAssign},
              {"*=", TokenKind::OpMulAssign},
              {"/=", TokenKind::OpDivAssign},

              {":", TokenKind::Colon},
              {"=", TokenKind::Assignment},
              {";", TokenKind::StatementEnd},
              {"\n", TokenKind::StatementEnd},
              {"{", TokenKind::OpenBrace},
              {"}", TokenKind::CloseBrace},
              {"(", TokenKind::OpenBracket},
              {")", TokenKind::CloseBracket},
              {"true", TokenKind::BoolLiteral},
              {"false", TokenKind::BoolLiteral},
              {"return", TokenKind::Return},
              {"->", TokenKind::Arrow},
              {",", TokenKind::Comma},
          },
      } {}

Token TokenFactory::create_token(std::string&& source_word,
                                 SourcePos source_pos) {
    return Token{
        core::Passkey<TokenFactory>{},
        std::move(source_word),
        map(source_word),
        source_pos,
    };
}

[[nodiscard]] TokenKind TokenFactory::map(
    std::string_view source_word) {
    if (mapping.contains(source_word)) {
        return mapping.at(source_word);
    }

    if (source_word.at(0) == '"' && source_word.ends_with('"')) {
        return TokenKind::StringLiteral;
    }

    if (auto result = try_convert_to_number(source_word)) {
        return result.value();
    }

    return TokenKind::Identifier;
}
}  // namespace marex::lex
