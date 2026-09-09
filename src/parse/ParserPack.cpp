#include "ParserPack.h"

#include <exception>
#include <format>
#include <source_location>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>

#include "Logging.h"
#include "TokenKind.h"
#include "nodes/exceptions/InvalidTokenException.h"

namespace marex::parse {
TokenStream::TokenStream(std::vector<lex::Token>&& token_stream,
                       bool is_in_lint_mode)
    : token_stream(std::move(token_stream)),
      progress(),
      is_in_lint_mode(is_in_lint_mode) {}

lex::TokenKind TokenStream::get_next_kind(
    std::string_view error_message_on_failure) const {
    try {
        return token_stream.at(progress + 1)
            .get_kind();
    } catch (const std::exception& exception) {
        throw std::runtime_error(
            error_message_on_failure.data());
    } catch (...) {
        throw std::runtime_error(
            "unkown error when trying to reach for "
            "next token in ParserPack");
    }
}

std::string_view TokenStream::get_kind_string() const {
    return *get_kind();
}

[[nodiscard]] bool TokenStream::advance_if_matches(
    lex::TokenKind token_kind) {
    const auto does_match = matches(token_kind);

    if (does_match) {
        advance();
    }

    return does_match;
}

std::string TokenStream::advance_if_matches_or_throw(
    lex::TokenKind token_kind,
    std::source_location cpp_source_location) {
    auto pre_increment_token_borrow = get_token();
    const auto got_token_kind =
        pre_increment_token_borrow.get_kind();

    if (got_token_kind == token_kind) {
        advance();

        core::log_info(std::format(
            "TokenKind {} matched", *token_kind));

        return pre_increment_token_borrow
            .move_out_lexeme();
    }

    throw InvalidTokenException(get_pos(), token_kind,
                                got_token_kind,
                                cpp_source_location);
}

lex::Token TokenStream::copy_out_token_and_advance() {
    const auto token = copy_out_token();

    advance();

    return token;
}

std::string_view TokenStream::get_lexeme_and_advance() {
    const auto lexeme = get_lexeme();

    advance();

    return lexeme;
}

[[nodiscard]] lex::TokenKind
TokenStream::get_kind_and_advance() {
    const auto kind = get_kind();

    advance();

    return kind;
}

bool TokenStream::is_at_end() const {
    const auto is_finished =
        token_stream.size() <= progress;

    return is_finished;
}

[[nodiscard]] std::string
TokenStream::get_error_message() const {
    return std::format("invalid Token: '{}' at '{}'",
                       *get_kind(),
                       get_pos().as_string());
}
}  // namespace marex::parse
