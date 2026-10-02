#include "invalid_token_exception.h"

#include <format>
#include <utility>

#include "error_format.h"
#include "token_kind.h"

namespace marex::parse {
InvalidTokenException::InvalidTokenException(
    lex::SourcePos source_pos, lex::TokenKind expected_token_kind,
    lex::TokenKind got_token_kind,
    std::source_location cpp_source_location)
    : full_message(std::format(
          "Invalid token: At {}\nexpected: {}, got "
          "{}, from {}",
          source_pos.as_string(), *expected_token_kind,
          *got_token_kind,
          core::source_location_to_string(cpp_source_location))) {}

InvalidTokenException::InvalidTokenException(
    lex::SourcePos source_pos, lex::TokenKind unexpected_token_kind,
    std::string&& message, std::string_view unexpected_token_lexeme,
    std::source_location cpp_source_location)
    : full_message(std::format(
          "At: {},\nunexpected token kind: {}, '{}'. {}\n\n"
          "from:{}",
          source_pos.as_string(), *unexpected_token_kind,
          unexpected_token_lexeme, message,
          core::source_location_to_string(cpp_source_location))) {}

InvalidTokenException::InvalidTokenException(
    lex::SourcePos source_pos, lex::TokenKind unexpected_token_kind,
    std::string&& message, std::source_location cpp_source_location)
    : marex::parse::InvalidTokenException(
          source_pos, unexpected_token_kind, std::move(message), "",
          cpp_source_location) {}

InvalidTokenException::InvalidTokenException(
    lex::SourcePos source_pos, lex::TokenKind unexpected_token_kind,
    std::source_location cpp_source_location)
    : full_message(std::format(
          "At: {},\nunexpected token kind: {}, from {}",
          source_pos.as_string(), *unexpected_token_kind,
          core::source_location_to_string(cpp_source_location))) {}

InvalidTokenException::InvalidTokenException(
    lex::SourcePos source_pos, std::string&& full_message,
    std::source_location cpp_source_location)
    : full_message(std::format(
          "At {}\nInvalid token: {}, from {}", source_pos.as_string(),
          std::move(full_message),
          core::source_location_to_string(cpp_source_location))) {}

const char* InvalidTokenException::what() const noexcept {
    return full_message.data();
}
}  // namespace marex::parse
