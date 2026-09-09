#ifndef MAREX_PARSE_PARSERPACK_H
#define MAREX_PARSE_PARSERPACK_H
#include <cstddef>
#include <source_location>
#include <string>
#include <string_view>
#include <vector>

#include "BindingRank.h"
#include "SourcePos.h"
#include "Token.h"
#include "TokenKind.h"

namespace marex::parse {
class TokenStream final {
   public:
    TokenStream(std::vector<lex::Token>&& token_stream,
               bool is_in_lint_mode = false);

    void advance() { ++progress; }

    [[nodiscard]] lex::TokenKind get_next_kind(
        std::string_view error_message_on_failure =
            "trying to access next token, when there "
            "is none") const;

    [[nodiscard]] bool is_at_end() const;

    [[nodiscard]] lex::TokenKind token_kind_at(
        std::size_t index) const {
        return borrow_token_at(index).get_kind();
    }

    [[nodiscard]] const lex::Token& borrow_token_at(
        std::size_t index) const {
        return token_stream.at(index);
    }

    [[nodiscard]] lex::BindingRank get_binding_rank_at(
        std::size_t index) const {
        return borrow_token_at(index)
            .get_binding_rank();
    }

    [[nodiscard]] std::size_t get_progress() const {
        return progress;
    }

    [[nodiscard]] std::string_view get_kind_string()
        const;

    [[nodiscard]] bool advance_if_matches(
        lex::TokenKind token_kind);

    [[nodiscard]] bool matches(
        lex::TokenKind token_kind) const {
        return get_kind() == token_kind;
    }

    [[nodiscard]] lex::Token
    copy_out_previous_token() {
        return token_stream.at(progress - 1);
    }

    /* NOT [[nodiscard]] */ std::string
    advance_if_matches_or_throw(
        lex::TokenKind token_kind,
        std::source_location cpp_source_location =
            std::source_location::current());

    [[nodiscard]] lex::TokenKind get_kind() const {
        return get_token().get_kind();
    }

    [[nodiscard]] lex::Token
    copy_out_token_and_advance();

    [[nodiscard]] std::string_view
    get_lexeme_and_advance();

    [[nodiscard]] lex::TokenKind
    get_kind_and_advance();

    [[nodiscard]] lex::SourcePos get_pos() const {
        return get_token().get_pos();
    }

    [[nodiscard]] std::string_view get_lexeme() const {
        return get_token().get_lexeme();
    }

    [[nodiscard]] const lex::Token& get_token() const {
        return token_stream.at(progress);
    }

    [[nodiscard]] lex::Token copy_out_token() const {
        return lex::Token(token_stream.at(progress));
    }

    [[nodiscard]] bool get_is_in_lint_mode() const {
        return is_in_lint_mode;
    }

    [[nodiscard]] std::string get_error_message()
        const;

   private:
    std::vector<lex::Token> token_stream;
    std::size_t progress{};
    bool is_in_lint_mode{};
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_PARSERPACK_H
