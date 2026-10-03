#ifndef MAREX_PARSE_BINARYOPKIND_H
#define MAREX_PARSE_BINARYOPKIND_H
#include <cstdint>
#include <string_view>
#include <utility>

namespace marex::parse {
enum struct [[nodiscard]] BinaryOpKind : std::uint8_t {
    None = 0,
    Add,
    Sub,
    Mul,
    Div,
};

inline std::string_view to_c(BinaryOpKind binary_op_kind) {
    switch (binary_op_kind) {
        case marex::parse::BinaryOpKind::Add:
            return "+";
        case marex::parse::BinaryOpKind::Sub:
            return "-";
        case marex::parse::BinaryOpKind::Mul:
            return "*";
        case marex::parse::BinaryOpKind::Div:
            return "/";
        case marex::parse::BinaryOpKind::None:
            [[fallthrough]];
        default:
            std::unreachable();
    }
}
}  // namespace marex::parse
#endif  // MAREX_PARSE_BINARYOPKIND_H