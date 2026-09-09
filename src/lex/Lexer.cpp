#include "Lexer.h"

#include <optional>
#include <string>

#include "Defer.h"
#include "LastCharKind.h"
#include "Logging.h"
#include "SourcePos.h"
#include "Token.h"
#include "exceptions/SourceCodeEmptyException.h"

namespace marex::lex {
std::vector<Token> Lexer::run(
    std::string&& source_text,
    std::optional<std::string> filename) {
    std::vector<Token> result;

    SourcePos source_pos{filename};

    result.reserve(vector_default_size);

    core::Defer defer_reset = [&]() {
        if (is_flushable()) {
            Lexer::push_token(result, source_pos);
        }

        reset(source_pos);
    };

    for (const auto source_text_char : source_text) {
        LastCharKind this_char_kind =
            LastCharKind::WasNotDefault;

        core::Defer defer_iter_end = [&]() {
            last_char_optional = source_text_char;
            last_char_kind = this_char_kind;
        };

        source_pos.advance_column();

        switch (source_text_char) {
            case ' ':
                if (is_flushable()) {
                    Lexer::push_token(result,
                                      source_pos);
                }
                break;
            case '\n':
                if (is_flushable()) {
                    Lexer::push_token(result,
                                      source_pos);
                }
                source_pos.advance_line();
                break;
            case '\0':
                /* ignore */
                break;
            case '{':
                [[fallthrough]];
            case '}':
                [[fallthrough]];
            case '(':
                [[fallthrough]];
            case ')':
                [[fallthrough]];
            case '=':
                [[fallthrough]];
            case ':':
                [[fallthrough]];
            case ',':
                [[fallthrough]];
            case ';':
                if (is_flushable()) {
                    Lexer::push_token_and_current(
                        result, source_text_char,
                        source_pos);
                } else {
                    Lexer::push_current(
                        result, source_text_char,
                        source_pos);
                }
                break;
            default:
                this_char_kind =
                    LastCharKind::WasDefault;
                last_word.push_back(source_text_char);
                break;
        }
    }

    if (!last_char_optional.has_value()) [[unlikely]] {
        throw SourceCodeEmptyException();
    }

    return result;
}

void Lexer::reset(SourcePos& source_pos) {
    last_char_optional = std::nullopt;
    last_char_kind = LastCharKind::None;
    source_pos.reset();
    last_word.clear();
}

void Lexer::push_token(std::vector<Token>& result,
                       SourcePos& source_pos) {
    core::log_info("Lexer: push_token");

    result.emplace_back(token_factory.create_token(
        std::string{last_word}, source_pos));

    last_word.clear();
}

void Lexer::push_current(std::vector<Token>& result,
                         char current,
                         SourcePos& source_pos) {
    core::log_info("Lexer: push_current");

    result.emplace_back(token_factory.create_token(
        std::string{current}, source_pos));
}

void Lexer::push_token_and_current(
    std::vector<Token>& result, char current,
    SourcePos& source_pos) {
    core::log_info("Lexer: push_token_and_current");

    push_token(result, source_pos);
    push_current(result, current, source_pos);
}
}  // namespace marex::lex
