#ifndef MAREX_CORE_PASSKEY_H
#define MAREX_CORE_PASSKEY_H
#include <type_traits>

namespace marex::core {
template <typename Factory>
    requires std::is_class_v<Factory>
class [[nodiscard]] Passkey final {
    friend Factory;

public:
    Passkey(Passkey&&) = default;

    Passkey& operator=(Passkey&&) = delete;
    Passkey(const Passkey&) = delete;
    Passkey& operator=(const Passkey&) = delete;
    ~Passkey() = default;

private:
    Passkey() = default;
};
} // namespace compiler::core
#endif // MAREX_CORE_PASSKEY_H
