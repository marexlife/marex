#ifndef MAREX_PARSE_NUMBERNODE_H
#define MAREX_PARSE_NUMBERNODE_H
#include "nodes/operand.h"
#include "token.h"

namespace marex::parse {
class NumberNode final : public Operand {
   public:
    explicit NumberNode(lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_NUMBERNODE_H