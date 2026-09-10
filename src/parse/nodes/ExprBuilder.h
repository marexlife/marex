#ifndef MAREX_PARSE_STATEMENTBUILDER_H
#define MAREX_PARSE_STATEMENTBUILDER_H
#include <list>
#include <memory>

#include "TokenStream.h"
#include "nodes/Expr.h"

namespace marex::parse {
class ExprBuilder final {
   public:
    static std::unique_ptr<Expr> build(TokenStream& stream);

   private:
    static void collect_rankings(
        TokenStream& stream,
        std::list<std::list<std::pair<
            lex::Token, TokenStream::ProgressType>>>&
            binding_rankings);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_STATEMENTBUILDER_H
