#ifndef MAREX_PARSE_LITERALKIND_H
#define MAREX_PARSE_LITERALKIND_H
#include <cstdint>

namespace marex::parse {
enum struct [[nodiscard]] LiteralKind : std::uint8_t {
    None = 0,
    Float,
    Bool,
    Int,
    String,
};
}
#endif  // MAREX_PARSE_LITERALKIND_H