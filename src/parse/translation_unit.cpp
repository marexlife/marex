#include "translation_unit.h"

#include <memory>
#include <string>
#include <utility>

#include "nodes/exceptions/invalid_token_exception.h"
#include "nodes/func_node.h"
#include "token_kind.h"

namespace marex::parse {
TranslationUnit TranslationUnit::compile(
    std::vector<lex::Token>&& tokens) {
    TokenStream stream{std::move(tokens)};
    std::vector<std::unique_ptr<AstNode>> file_items;

    while (!stream.is_at_end()) {
        std::unique_ptr<AstNode> file_item =
            create_file_item(stream);

        file_item->parse(stream);

        file_items.emplace_back(std::move(file_item));
    }

    return TranslationUnit{std::move(file_items)};
}

std::string TranslationUnit::as_c() {
    std::string result = R"(#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

void run(void);

int main(void) {
    run();

    return 0;
}

)";

    for (auto& file_item : file_items_) {
        result += file_item->as_c();
    }

    return result;
}

std::unique_ptr<AstNode>
TranslationUnit::create_file_item(TokenStream& pack) {
    switch (pack.get_kind()) {
        case lex::TokenKind::Func:
            return std::make_unique<FuncNode>(
                pack.copy_out_token());
        case lex::TokenKind::Var:
            throw InvalidTokenException(
                pack.get_pos(),
                "no global variables allowed");
        default:
            throw InvalidTokenException(
                pack.get_pos(), pack.get_kind());
    }
}
}  // namespace marex::parse
