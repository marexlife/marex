#ifndef MAREX_PARSE_OPNODE_H
#define MAREX_PARSE_OPNODE_H
#include "expr.h"
#include "token.h"

namespace marex::parse {
class OpNode : public Expr {
   public:
    explicit OpNode(lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_OPNODE_H
