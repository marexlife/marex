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
        std::list<std::list<lex::Token>>&
            binding_rankings);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_STATEMENTBUILDER_H
