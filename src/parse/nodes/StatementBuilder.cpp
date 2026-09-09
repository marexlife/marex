#include "StatementBuilder.h"

#include <cstddef>
#include <functional>
#include <limits>
#include <list>
#include <utility>

#include "Token.h"
#include "TokenKind.h"
#include "nodes/Expr.h"

namespace marex::parse {
void StatementBuilder::build(
    [[maybe_unused]] TokenStream& pack) {
    std::list<std::list<
        std::reference_wrapper<const lex::Token>>>
        binding_rankings;

    collect_rankings(pack, binding_rankings);

    std::list<Expr> expressions_row;

    for (auto& rank_row : binding_rankings) {
        for ([[maybe_unused]] auto token : rank_row) {
        }
    }
}

void StatementBuilder::collect_rankings(
    TokenStream& stream,
    std::list<std::list<
        std::reference_wrapper<const lex::Token>>>&
        binding_rankings) {
    for (std::uint8_t to_be_collected_rank = 0;
         to_be_collected_rank <
         std::numeric_limits<std::uint8_t>::max();
         ++to_be_collected_rank) {
        std::list<
            std::reference_wrapper<const lex::Token>>
            ranking_row;

        for (std::size_t token_id = 0;
             stream.token_kind_at(token_id) !=
             lex::TokenKind::StatementEnd;
             ++token_id) {
            if (to_be_collected_rank ==
                std::to_underlying(
                    stream.get_binding_rank_at(
                        token_id))) {
                ranking_row.emplace_back(
                    stream.borrow_token_at(token_id));
            }

            binding_rankings.emplace_back(
                std::move(ranking_row));
        }
    }
}
}  // namespace marex::parse
