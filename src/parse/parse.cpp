#include "parse.h"

#include <expected>
#include <memory>
#include <utility>
#include <vector>

#include "error.h"
#include "token_stream.h"

namespace marex {
std::expected<parse::TranslationUnit,
              std::unique_ptr<core::Error>>
parse::parse(std::pmr::vector<lex::Token>&& tokens) {
    TranslationUnit translation_unit{};
    TokenStream token_stream{std::move(tokens)};
    auto result = translation_unit.parse(token_stream);

    if (!result) {
        return std::unexpected<
            std::unique_ptr<core::Error>>(
            std::move(result.error()));
    }
    
    return std::expected<parse::TranslationUnit,
                         std::unique_ptr<core::Error>>(
        std::move(translation_unit));
}
}  // namespace marex
