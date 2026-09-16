#ifndef MAREX_LEX_BINDINGRANK_H
#define MAREX_LEX_BINDINGRANK_H
#include <cstdint>

namespace marex::lex {
enum struct BindingRank : std::uint8_t {
    Div = 0,
    Mul = 0,
    Add = 1,
    Sub = 1,
    Var = 30,
    Invalid = 0,
};
}
#endif  // MAREX_LEX_BINDINGRANK_H