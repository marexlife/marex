#include "expr_build.h"

#include <cstddef>
#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#include "binding_rank.h"
#include "expr_factory.h"
#include "nodes/expr.h"
#include "token.h"
#include "token_kind.h"
#include "token_stream.h"

namespace marex {
namespace parse {
using Ranking = std::pair<std::unique_ptr<Expr>,
                          TokenStream::ProgressType>;
using RankingRow = std::vector<Ranking>;
using Rankings = std::vector<RankingRow>;

static void collect_rankings(TokenStream& stream,
                             Rankings& rankings);

static void handle_rankings(Rankings&& rankings);
}  // namespace parse

std::unique_ptr<parse::Expr> parse::build(
    TokenStream& stream) {
    Rankings rankings;

    collect_rankings(stream, rankings);

    handle_rankings(std::move(rankings));

    throw std::runtime_error("not implemented yet");
}

void parse::collect_rankings(TokenStream& stream,
                             Rankings& rankings) {
    for (std::uint8_t to_be_collected_rank = 0;
         to_be_collected_rank <
         std::numeric_limits<std::underlying_type_t<
             lex::BindingRank>>::max();
         ++to_be_collected_rank) {
        RankingRow ranking_row;

        for (std::size_t token_id = 0;
             stream.token_kind_at(token_id) !=
             lex::TokenKind::StatementEnd;
             ++token_id) {
            if (to_be_collected_rank ==
                std::to_underlying(
                    stream.get_binding_rank_at(
                        token_id))) {
                ranking_row.emplace_back(Ranking(
                    ExprFactory::new_expr(
                        stream.copy_out_token()),
                    token_id));
            }

            rankings.emplace_back(
                std::move(ranking_row));
        }
    }
}

void parse::handle_rankings(Rankings&& rankings) {
    for (auto& ranking_row : rankings) {
        for (auto& [expr, progress] : ranking_row) {
            switch (expr->get_kind()) {
                case marex::lex::TokenKind::Assignment:

                    break;
                default:
                    throw std::runtime_error(
                        "not implemented yet");
            }
        }
    }
}
}  // namespace marex
