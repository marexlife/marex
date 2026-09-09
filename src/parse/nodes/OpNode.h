#ifndef MAREX_PARSE_OPNODE_H
#define MAREX_PARSE_OPNODE_H
#include "Expr.h"
#include "Token.h"

namespace marex::parse {
class OpNode : public Expr {
   public:
    explicit OpNode(lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_OPNODE_H
