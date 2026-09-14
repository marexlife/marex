#include "TokenFactory.h"

#include <string_view>

#include "Passkey.h"
#include "SourcePos.h"
#include "Token.h"
#include "TokenKind.h"

namespace marex::lex {
TokenFactory::TokenFactory()
    : mapping{
          {
              {"var", TokenKind::Var},
              {"float", TokenKind::FloatDecl},
              {"int", TokenKind::IntDecl},
              {"bool", TokenKind::BoolDecl},
              {"fun", TokenKind::Func},
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

Token TokenFactory::create_token(
    std::string&& source_word, SourcePos source_pos) {
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

    if (source_word.at(0) == '"' &&
        source_word.ends_with('"')) {
        return TokenKind::StringLiteral;
    }

    if (auto result =
            try_convert_to_number(source_word)) {
        return result.value();
    }

    return TokenKind::Identifier;
}
}  // namespace marex::lex
