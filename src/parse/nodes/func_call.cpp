#include "func_call.h"

#include <format>
#include <string>
#include <utility>

#include "defer.h"
#include "expr_kind.h"
#include "token_kind.h"

namespace marex::parse {
std::string FuncCall::as_c() {
    std::string result;
    std::uintmax_t count{};

    for (auto& [name, expression_kind] : args_) {
        core::Defer increment_count = [&] { ++count; };
        result += name;

        if (count != args_.size() - 1) {
            result += ", ";
        }
    }

    return std::format("{}({});\n", func_name_,
                       result);
}

FuncCall FuncCall::parse(TokenStream& stream) {
    std::string func_name;
    std::vector<CallArg> args;

    func_name = stream.advance_if_matches_or_throw(
        lex::TokenKind::Identifier);

    stream.advance_if_matches_or_throw(
        lex::TokenKind::OpenBracket);

    if (stream.advance_if_matches(
            lex::TokenKind::CloseBracket)) {
        return FuncCall{stream.copy_out_token(),
                        std::move(func_name),
                        std::move(args)};
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

    return FuncCall{stream.copy_out_token(),
                    std::move(func_name),
                    std::move(args)};
}

FuncCall::FuncCall(lex::Token&& token,
                   std::string&& func_name,
                   std::vector<CallArg>&& args)
    : Expr(std::move(token)),
      func_name_(std::move(func_name)),
      args_(std::move(args)) {}
}  // namespace marex::parse
