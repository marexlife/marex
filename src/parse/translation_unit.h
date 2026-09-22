#ifndef MAREX_PARSE_TRANSLATIONUNIT_H
#define MAREX_PARSE_TRANSLATIONUNIT_H
#include <memory>
#include <utility>
#include <vector>

#include "nodes/ast_node.h"
#include "token_stream.h"

namespace marex::parse {
class TranslationUnit final {
   public:
    [[nodiscard]] std::string as_c();
    [[nodiscard]] static TranslationUnit compile(
        std::vector<lex::Token>&& tokens);

   private:
    [[nodiscard]] static std::unique_ptr<AstNode>
    create_file_item(TokenStream& stream);

    explicit TranslationUnit(
        std::vector<std::unique_ptr<AstNode>>
            file_items)
        : file_items_(std::move(file_items)) {}

    std::vector<std::unique_ptr<AstNode>> file_items_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_TRANSLATIONUNIT_H
