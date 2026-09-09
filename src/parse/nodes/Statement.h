#ifndef MAREX_PARSE_STATEMENT_H
#define MAREX_PARSE_STATEMENT_H
#include "Token.h"
#include "nodes/AstNode.h"

namespace marex::parse {
class Statement : public AstNode {
   public:
    explicit Statement(lex::Token&& token);

   private:
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_STATEMENT_H