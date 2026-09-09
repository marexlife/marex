#include "FuncCall.h"

#include <format>
#include <string>
#include <utility>

#include "Defer.h"
#include "ExpressionKind.h"
#include "Token.h"
#include "TokenKind.h"

namespace marex::parse {
FuncCall::FuncCall(lex::Token&& token)
    : Expr(std::move(token)) {}

std::string FuncCall::as_c() {
    std::string result;
    std::uintmax_t count{};

    for (auto& [name, expression_kind] : args) {
        core::Defer increment_count = [&] { ++count; };
        result += name;

        if (count != args.size() - 1) {
            result += ", ";
        }
    }

    return std::format("{}({});\n", func_name, result);
}

void FuncCall::parse(TokenStream& stream) {
    func_name = stream.advance_if_matches_or_throw(
        lex::TokenKind::Identifier);

    stream.advance_if_matches_or_throw(
        lex::TokenKind::OpenBracket);

    if (stream.advance_if_matches(
            lex::TokenKind::CloseBracket)) {
        return;
    }

    do {
        auto lexeme = stream.get_lexeme();
        auto expression_kind =
            expression_kind_from_literal_or_throw(
                stream);

        stream.advance();

        args.emplace_back(CallArg{
            .name = std::string{lexeme},
            .expression_kind = expression_kind,
        });
    } while (stream.advance_if_matches(
        lex::TokenKind::Comma));

    stream.advance_if_matches_or_throw(
        lex::TokenKind::CloseBracket);
}
}  // namespace marex::parse
