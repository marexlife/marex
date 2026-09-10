#include "ExprBuilder.h"

#include <cstddef>
#include <limits>
#include <list>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "BindingRank.h"
#include "ExprFactory.h"
#include "Token.h"
#include "TokenKind.h"
#include "TokenStream.h"
#include "nodes/Expr.h"

namespace marex::parse {
void ExprBuilder::build(TokenStream& stream) {
    std::list<std::list<std::pair<
        lex::Token, TokenStream::ProgressType>>>
        binding_rankings;

    collect_rankings(stream, binding_rankings);

    std::list<std::list<
        std::pair<std::unique_ptr<Expr>,
                  TokenStream::ProgressType>>>
        expr_rows;

    for (auto& rank_row : binding_rankings) {
        std::list<std::pair<std::unique_ptr<Expr>,
                            TokenStream::ProgressType>>
            expressions_row;
        for (auto [token, progress] : rank_row) {
            auto expr = ExprFactory::new_expr(
                std::move(token));

            expressions_row.emplace_back(
                std::move(expr), progress);
        }

        expr_rows.emplace_back(
            std::move(expressions_row));
    }

    throw std::runtime_error(
        "expression parsing not implemented yet");

    for (auto& expr_row : expr_rows) {
        for ([[maybe_unused]] auto& [expr, progress] :
             expr_row) {
        }
    }
}

void ExprBuilder::collect_rankings(
    TokenStream& stream,
    std::list<std::list<std::pair<
        lex::Token, TokenStream::ProgressType>>>&
        binding_rankings) {
    for (std::uint8_t to_be_collected_rank = 0;
         to_be_collected_rank <
         std::numeric_limits<std::underlying_type_t<
             lex::BindingRank>>::max();
         ++to_be_collected_rank) {
        std::list<std::pair<lex::Token,
                            TokenStream::ProgressType>>
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
                    stream.borrow_token_at(token_id),
                    token_id);
            }

            binding_rankings.emplace_back(
                std::move(ranking_row));
        }
    }
}
}  // namespace marex::parse
