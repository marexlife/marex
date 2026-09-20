#ifndef MAREX_PARSE_STATEMENTBUILDER_H
#define MAREX_PARSE_STATEMENTBUILDER_H
#include <memory>
#include <utility>
#include <vector>

#include "nodes/expr.h"
#include "token_stream.h"

namespace marex::parse {
struct Ranking final {
    Ranking(std::unique_ptr<Expr> expr,
            TokenStream::ProgressType progress_type)
        : expr(std::move(expr)),
          progress_type(progress_type) {}

    std::unique_ptr<Expr> expr;
    TokenStream::ProgressType progress_type;
};

using RankingRow = std::vector<Ranking>;
using Rankings = std::vector<RankingRow>;

std::unique_ptr<Expr> build(TokenStream& stream);
}  // namespace marex::parse
#endif  // MAREX_PARSE_STATEMENTBUILDER_H
