#ifndef MAREX_PARSE_OPERAND_H
#define MAREX_PARSE_OPERAND_H
#include "nodes/op_node.h"
#include "token.h"

namespace marex::parse {
class Operand : public OpNode {
   public:
    explicit Operand(lex::Token&& token);
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_OPERAND_H