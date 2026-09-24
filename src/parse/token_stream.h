#ifndef MAREX_PARSE_PARSERPACK_H
#define MAREX_PARSE_PARSERPACK_H
#include <cstddef>
#include <functional>
#include <source_location>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "binding_power.h"
#include "source_pos.h"
#include "token.h"
#include "token_kind.h"

namespace marex::parse {
class TokenStream final {
   public:
    TokenStream(std::vector<lex::Token>&& token_stream = {},
                bool is_in_lint_mode = false);

    using ProgressType = std::size_t;

    void advance() { ++progress_; }

    [[nodiscard]] bool previous_was(lex::TokenKind token_kind) const;
    [[nodiscard]] bool next_is(lex::TokenKind token_kind) const;

    [[nodiscard]] lex::TokenKind get_next_kind(
        std::string_view error_message_on_failure =
            "trying to access next token, when there "
            "is none") const;

    struct RunUntilStmtEndPack final {
        RunUntilStmtEndPack(
            std::size_t index,
            std::reference_wrapper<const lex::Token> token)
            : index(index), token(token) {}

        std::size_t index{};
        std::reference_wrapper<const lex::Token> token;
    };

    template <typename F>
        requires std::is_invocable_v<F, RunUntilStmtEndPack>
    void run_until_stmt_end(F iter) const {
        for (std::size_t i = 0;
             token_kind_at(i) != lex::TokenKind::StatementEnd; ++i) {
            std::invoke(iter,
                        RunUntilStmtEndPack(i, borrow_token_at(i)));
        }
    }

    [[nodiscard]] bool is_at_end() const;

    [[nodiscard]] lex::TokenKind token_kind_at(
        std::size_t index) const {
        return borrow_token_at(index).get_kind();
    }

    [[nodiscard]] bool mismatches_at(
        ProgressType progress, lex::TokenKind token_kind) const {
        return !matches_at(progress, token_kind);
    }

    [[nodiscard]] bool matches_at(ProgressType progress,
                                  lex::TokenKind token_kind) const {
        return token_kind_at(progress) == token_kind;
    }

    [[nodiscard]] const lex::Token& borrow_token_at(
        std::size_t index) const {
        return tokens_.at(index);
    }

    [[nodiscard]] std::optional<lex::BindingPower>
    get_binding_power_at(std::size_t index) const {
        return borrow_token_at(index).get_binding_power();
    }

    [[nodiscard]] std::size_t get_progress() const {
        return progress_;
    }

    [[nodiscard]] std::string_view get_kind_string() const;

    [[nodiscard]] bool advance_if_matches(lex::TokenKind token_kind);

    [[nodiscard]] bool matches(lex::TokenKind token_kind) const {
        return get_kind() == token_kind;
    }

    [[nodiscard]] const lex::Token& borrow_previous() const {
        return tokens_.at(progress_ - 1);
    }

    [[nodiscard]] const lex::Token& borrow_next() const {
        return tokens_.at(progress_ + 1);
    }

    [[nodiscard]] lex::Token copy_out_previous_token() {
        return tokens_.at(progress_ - 1);
    }

    /* NOT [[nodiscard]] */ std::pmr::string
    advance_if_matches_or_throw(
        lex::TokenKind token_kind,
        std::source_location cpp_source_location =
            std::source_location::current());

    [[nodiscard]] lex::TokenKind get_kind() const {
        return borrow_token().get_kind();
    }

    [[nodiscard]] lex::Token copy_out_token_and_advance();

    [[nodiscard]] std::string_view get_lexeme_and_advance();

    [[nodiscard]] lex::TokenKind get_kind_and_advance();

    [[nodiscard]] lex::SourcePos get_pos() const {
        return borrow_token().get_pos();
    }

    [[nodiscard]] std::string_view get_lexeme() const {
        return borrow_token().get_lexeme_or_throw();
    }

    [[nodiscard]] const lex::Token& borrow_token() const {
        return tokens_.at(progress_);
    }

    [[nodiscard]] lex::Token copy_out_token() const {
        return lex::Token(tokens_.at(progress_));
    }

    [[nodiscard]] bool get_is_in_lint_mode() const {
        return is_in_lint_mode_;
    }

    [[nodiscard]] std::string get_error_message() const;

   private:
    std::vector<lex::Token> tokens_;
    ProgressType progress_{};
    bool is_in_lint_mode_{};
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_PARSERPACK_H
