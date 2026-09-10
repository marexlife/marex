#ifndef MAREX_PARSE_STATEMENTBUILDER_H
#define MAREX_PARSE_STATEMENTBUILDER_H
#include <list>

#include "TokenStream.h"

namespace marex::parse {
class ExprBuilder final {
   public:
    static void build(TokenStream& stream);

   private:
    static void collect_rankings(
        TokenStream& stream,
        std::list<std::list<std::pair<
            lex::Token, TokenStream::ProgressType>>>&
            binding_rankings);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_STATEMENTBUILDER_H
