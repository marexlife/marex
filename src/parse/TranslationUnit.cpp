#include "TranslationUnit.h"

#include <memory>
#include <string>
#include <utility>

#include "TokenKind.h"
#include "nodes/FuncNode.h"
#include "nodes/exceptions/InvalidTokenException.h"

namespace marex::parse {
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

    for (auto& file_item : file_items) {
        result += file_item->as_c();
    }

    return result;
}

void TranslationUnit::parse(TokenStream& pack) {
    while (!pack.is_at_end()) {
        std::unique_ptr<AstNode> file_item =
            create_file_item(pack);

        file_item->parse(pack);

        file_items.emplace_back(std::move(file_item));
    }
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
