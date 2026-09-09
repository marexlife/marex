#include "StatementBuilder.h"

#include <cstddef>
#include <limits>
#include <list>
#include <memory>
#include <stdexcept>
#include <utility>

#include "ExprFactory.h"
#include "Token.h"
#include "TokenKind.h"
#include "nodes/Assignment.h"
#include "nodes/Expr.h"

namespace marex::parse {
void StatementBuilder::build(TokenStream& stream) {
    std::list<std::list<lex::Token>> binding_rankings;

    collect_rankings(stream, binding_rankings);

    std::list<std::list<std::unique_ptr<Expr>>>
        expr_rows;

    for (auto& rank_row : binding_rankings) {
        std::list<std::unique_ptr<Expr>>
            expressions_row;
        for (auto token : rank_row) {
            auto expr = ExprFactory::new_expr(
                std::move(token));

            expressions_row.emplace_back(
                std::move(expr));
        }

        expr_rows.emplace_back(
            std::move(expressions_row));
    }

    // TODO! get the meta-data for Token where it is
    // in the TokenStream for plugging it into an Ast here after

    throw std::runtime_error(
        "expression parsing not implemented yet");

    for (auto& expr_row : expr_rows) {
        for (auto& expr : expr_row) {
            if ([[maybe_unused]] Assignment* const
                    assignment =
                        dynamic_cast<Assignment*>(
                            expr.get())) {
                // assignment->set_lhs(std::move());
                // assignment->set_rhs(
                //    std::move(Tp && t));
            }
        }
    }
}

void StatementBuilder::collect_rankings(
    TokenStream& stream,
    std::list<std::list<lex::Token>>&
        binding_rankings) {
    for (std::uint8_t to_be_collected_rank = 0;
         to_be_collected_rank <
         std::numeric_limits<std::uint8_t>::max();
         ++to_be_collected_rank) {
        std::list<lex::Token> ranking_row;

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
