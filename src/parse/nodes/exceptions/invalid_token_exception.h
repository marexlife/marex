#ifndef MAREX_PARSE_EXCEPTIONS_INVALIDTOKENEXCEPTION_H
#define MAREX_PARSE_EXCEPTIONS_INVALIDTOKENEXCEPTION_H
#include <exception>
#include <source_location>
#include <string>

#include "source_pos.h"
#include "token_kind.h"

namespace marex::parse {
class InvalidTokenException final
    : public std::exception {
   public:
    InvalidTokenException(
        lex::SourcePos source_pos,
        lex::TokenKind expected_token_kind,
        lex::TokenKind got_token_kind,
        std::source_location cpp_source_location =
            std::source_location::current());

    InvalidTokenException(
        lex::SourcePos source_pos,
        lex::TokenKind unexpected_token_kind,
        std::source_location cpp_source_location =
            std::source_location::current());

    InvalidTokenException(
        lex::SourcePos source_pos,
        lex::TokenKind unexpected_token_kind,
        std::string&& message,
        std::source_location cpp_source_location =
            std::source_location::current());

    InvalidTokenException(
        lex::SourcePos source_pos,
        std::string&& full_message,
        std::source_location cpp_source_location =
            std::source_location::current());

    const char* what() const noexcept override;

   private:
    std::string full_message;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_EXCEPTIONS_INVALIDTOKENEXCEPTION_H
