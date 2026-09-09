#include "StatementBuilder.h"

#include <cstddef>
#include <functional>
#include <limits>
#include <utility>
#include <vector>

#include "ParserPack.h"
#include "Token.h"
#include "TokenKind.h"

namespace marex::parse {
void StatementBuilder::build(
    [[maybe_unused]] ParserPack& pack) {
    std::vector<std::vector<
        std::reference_wrapper<const lex::Token>>>
        binding_rankings;

    collect_rankings(pack, binding_rankings);
}

void StatementBuilder::collect_rankings(
    ParserPack& pack,
    std::vector<std::vector<
        std::reference_wrapper<const lex::Token>>>&
        binding_rankings) {
    for (std::uint8_t to_be_collected_rank = 0;
         to_be_collected_rank <
         std::numeric_limits<std::uint8_t>::max();
         ++to_be_collected_rank) {
        for (std::size_t token_id = 0;
             pack.token_kind_at(token_id) !=
             lex::TokenKind::StatementEnd;
             ++token_id) {
            if (to_be_collected_rank ==
                std::to_underlying(
                    pack.get_binding_rank_at(
                        token_id))) {
                binding_rankings
                    .at(to_be_collected_rank)
                    .emplace_back(pack.borrow_token_at(
                        token_id));
            }
        }
    }
}
}  // namespace marex::parse