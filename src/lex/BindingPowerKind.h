#ifndef MAREX_LEX_BINDINGPOWERKIND_H
#define MAREX_LEX_BINDINGPOWERKIND_H
#include <cstdint>

namespace marex::lex {
enum struct [[nodiscard]] BindingPowerKind : std::
    uint8_t {
        Invalid = 0,
        Var = 30,
    };
}
#endif  // MAREX_LEX_BINDINGPOWERKIND_H