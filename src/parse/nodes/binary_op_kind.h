#ifndef MAREX_PARSE_BINARYOPKIND_H
#define MAREX_PARSE_BINARYOPKIND_H
#include <cstdint>

namespace marex::parse {
enum struct [[nodiscard]] BinaryOpKind : std::uint8_t {
    None = 0,
    Add,
    Sub,
    Mul,
    Div,
};
}
#endif  // MAREX_PARSE_BINARYOPKIND_H