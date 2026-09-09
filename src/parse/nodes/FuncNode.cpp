#include "FuncNode.h"

#include <cstddef>
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include "Defer.h"
#include "Logging.h"
#include "TokenStream.h"
#include "TokenKind.h"
#include "VarDecl.h"
#include "exceptions/InvalidTokenException.h"
#include "nodes/FuncCall.h"
#include "nodes/ReturnNode.h"

namespace marex::parse {
FuncNode::FuncNode(lex::Token&& token)
    : AstNode(std::move(token)) {}

[[nodiscard]] std::string FuncNode::as_c() {
    auto get_func_args = [&] -> std::string {
        std::string func_args_string;

        std::size_t count{};

        for (auto& [arg_name, arg_type] : args) {
            core::Defer iter_end = [&] { ++count; };

            func_args_string += *arg_type;
            func_args_string += ' ';
            func_args_string += arg_name;

            if (count != args.size() - 1) {
                func_args_string += ", ";
            }
        }

        if (func_args_string.empty()) {
            func_args_string = "void";
        }

        return func_args_string;
    };

    auto get_func_code = [&] -> std::string {
        std::string func_content_string;

        for (auto& func_item : func_items) {
            func_content_string += std::format(
                "    {}", func_item->as_c());
        }

        return func_content_string;
    };

    return std::format(
        "{} {}({}) {{\n{}{}}}\n\n", *return_type,
        func_name, std::invoke(get_func_args),
        std::invoke(get_func_code),
        std::invoke([&] -> std::string {
            if (return_node) {
                return std::format(
                    "\n    {}",
                    return_node.value()->as_c());
            }

            return "";
        }));
}

void FuncNode::parse_func_body(TokenStream& stream) {
    while (true) {
        if (stream.matches(lex::TokenKind::Return)) {
            this->return_node = std::invoke([&] {
                auto return_node =
                    std::make_unique<ReturnNode>(
                        stream.copy_out_token());

                return_node->parse(stream);

                return return_node;
            });

            if (this->return_node) {
                core::log_info(
                    "succeeded to set return node");
            } else {
                core::log_fatal_error(
                    "failed to set return node");
            }
        }

        if (stream.advance_if_matches(
                lex::TokenKind::CloseBrace)) {
            break;
        }

        auto node = std::invoke([&] -> std::unique_ptr<
                                        AstNode> {
            switch (stream.get_kind()) {
                case lex::TokenKind::Var:
                    return std::make_unique<VarDecl>(
                        stream.copy_out_token());
                case lex::TokenKind::Identifier: {
                    if (stream.get_next_kind() ==
                        lex::TokenKind::OpenBracket) {
                        core::log_info(
                            "function call");

                        return std::make_unique<
                            FuncCall>(
                            stream.copy_out_token());
                    }

                    throw std::runtime_error(
                        "identifiers in functions, "
                        "that are not function calls "
                        "are not supported yet");
                } break;
                default:
                    goto end;
            }

        end:
            throw InvalidTokenException(
                stream.get_pos(), stream.get_kind());
        });

        node->parse(stream);

        func_items.emplace_back(std::move(node));
    }
}

void FuncNode::parse(TokenStream& stream) {
    parse_func_signature(stream);
    parse_func_body(stream);
}

void FuncNode::parse_func_signature(TokenStream& stream) {
    stream.advance_if_matches_or_throw(
        lex::TokenKind::Func);

    func_name = stream.advance_if_matches_or_throw(
        lex::TokenKind::Identifier);

    parse_func_args(stream);

    if (stream.advance_if_matches(
            lex::TokenKind::OpenBrace)) {
        return_type = ExpressionKind::EmptyType;
        return;
    }

    stream.advance_if_matches_or_throw(
        lex::TokenKind::Arrow);

    return_type =
        expression_kind_from_decl_or_throw(stream);

    stream.advance();

    stream.advance_if_matches_or_throw(
        lex::TokenKind::OpenBrace);
}

void FuncNode::parse_func_args(TokenStream& stream) {
    stream.advance_if_matches_or_throw(
        lex::TokenKind::OpenBracket);

    core::log_info("pre: parsed func args");
    std::uintmax_t arg_count = 1;

    if (stream.advance_if_matches(
            lex::TokenKind::CloseBracket)) {
        return;
    }

    do {
        core::Defer defer_arg_increment = [&] {
            ++arg_count;
        };

        core::log_info(
            std::format("arg count: {}", arg_count));

        auto func_arg = std::invoke([&] -> FuncArg {
            auto name =
                stream.advance_if_matches_or_throw(
                    lex::TokenKind::Identifier);
            stream.advance_if_matches_or_throw(
                lex::TokenKind::Colon);
            auto type =
                expression_kind_from_decl_or_throw(
                    stream);
            stream.advance();

            return FuncArg{
                .arg_name = name,
                .arg_type = type,
            };
        });

        args.emplace_back(std::move(func_arg));
    } while (stream.advance_if_matches(
        lex::TokenKind::Comma));

    stream.advance_if_matches_or_throw(
        lex::TokenKind::CloseBracket);

    core::log_info("post: parsed func args");
}
}  // namespace marex::parse
