#ifndef MAREX_PARSE_STATEMENTBUILDER_H
#define MAREX_PARSE_STATEMENTBUILDER_H
#include <list>

#include "ParserPack.h"

namespace marex::parse {
class StatementBuilder final {
   public:
    static void build(TokenStream& pack);

   private:
    static void collect_rankings(
        TokenStream& pack,
        std::list<std::list<
            std::reference_wrapper<const lex::Token>>>&
            binding_rankings);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_STATEMENTBUILDER_H