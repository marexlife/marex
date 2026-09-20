#include "expr_build.h"

#include <cstddef>
#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#include "binding_rank.h"
#include "expr_factory.h"
#include "logging.h"
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

std::unique_ptr<parse::Expr> parse::build_expr(
    TokenStream& stream) {
    Rankings rankings;

    collect_rankings(stream, rankings);

    handle_rankings(std::move(rankings));

    throw std::runtime_error("not implemented yet");
}

void parse::collect_rankings(TokenStream& stream,
                             Rankings& rankings) {
    constexpr auto enum_max_rank =
        std::numeric_limits<std::underlying_type_t<
            lex::BindingRank>>::max();

    for (std::uint8_t i = 0; i < enum_max_rank; ++i) {
        RankingRow ranking_row;

        auto not_at_end = [&](std::size_t index) {
            return stream.token_kind_at(index) !=
                   lex::TokenKind::StatementEnd;
        };

        for (std::size_t j = 0;
             std::invoke(not_at_end, j); ++j) {
            auto rank_progress_matches_enum_one = [&] {
                return i ==
                       std::to_underlying(
                           stream.get_binding_rank_at(
                               j));
            };

            if (std::invoke(
                    rank_progress_matches_enum_one)) {
                ranking_row.emplace_back(Ranking(
                    ExprFactory::new_expr(
                        stream.copy_out_token()),
                    j));
            }

            rankings.emplace_back(
                std::move(ranking_row));
        }
    }
}

void parse::handle_rankings(Rankings&& rankings) {
    for (RankingRow& ranking_row : rankings) {
        for (auto [index, ranking] :
             ranking_row | std::views::enumerate) {
            auto& [expr, rank] = ranking;
            [[maybe_unused]] auto get_previous_row =
                [&] -> const Ranking& {
                if (index == 0) {
                    throw std::out_of_range(
                        "there is no previous");
                }

                return ranking_row.at(
                    static_cast<std::size_t>(index -
                                             1));
            };

            core::log_info("at index: {}, kind: {}",
                           index, *expr->get_kind());
        }
    }
}
}  // namespace marex
