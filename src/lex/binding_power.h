#ifndef MAREX_LEX_BINDINGPOWER_H
#define MAREX_LEX_BINDINGPOWER_H
#include <cstdint>

namespace marex::lex {
enum struct BindingPower : std::uint8_t {
    Invalid = 0,
    AddSub = 1,
    MulDiv = 2,
};
}
#endif  // MAREX_LEX_BINDINGPOWER_H