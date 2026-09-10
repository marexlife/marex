#ifndef MAREX_PARSE_STATEMENTBUILDER_H
#define MAREX_PARSE_STATEMENTBUILDER_H
#include <memory>
#include <vector>

#include "TokenStream.h"
#include "nodes/Expr.h"

namespace marex::parse {
class ExprBuilder final {
   public:
    static std::unique_ptr<Expr> build(
        TokenStream& stream);

   private:
    static void collect_rankings(
        TokenStream& stream,
        std::vector<std::vector<std::pair<
            lex::Token, TokenStream::ProgressType>>>&
            binding_rankings);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_STATEMENTBUILDER_H
