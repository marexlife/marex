#include "func_call.h"

#include <format>
#include <string>
#include <utility>

#include "defer.h"
#include "expr_kind.h"
#include "token.h"
#include "token_kind.h"

namespace marex::parse {
FuncCall::FuncCall(lex::Token&& token) : Expr(std::move(token)) {}

std::string FuncCall::as_c() {
    std::string result;
    std::uintmax_t count{};

    for (auto& arg : args) {
        core::Defer increment_count = [&] { ++count; };
        result += arg.name;

        if (count != args.size() - 1) {
            result += ", ";
        }
    }

    return std::format("{}({});\n", func_name, result);
}

void FuncCall::parse(TokenStream& stream) {
    func_name = stream.value_advance_if_matches_or_throw(
        lex::TokenKind::Identifier);

    stream.advance_if_matches_or_throw(lex::TokenKind::OpenBracket);

    if (stream.advance_if_matches(lex::TokenKind::CloseBracket)) {
        return;
    }

    do {
        auto lexeme = stream.value_advance_if_matches_or_throw(
            lex::TokenKind::Identifier);

        args.emplace_back(CallArg{
            .name = std::string{lexeme},
        });
    } while (stream.advance_if_matches(lex::TokenKind::Comma));

    stream.advance_if_matches_or_throw(lex::TokenKind::CloseBracket);

    stream.advance_if_matches_or_throw(lex::TokenKind::StatementEnd);
}
}  // namespace marex::parse
