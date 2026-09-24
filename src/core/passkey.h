#ifndef MAREX_CORE_PASSKEY_H
#define MAREX_CORE_PASSKEY_H
#include <type_traits>

namespace marex::core {
template <typename Friend>
    requires std::is_class_v<Friend>
class [[nodiscard]] Passkey final {
    friend Friend;

   public:
    Passkey(Passkey&&) = default;

    Passkey& operator=(Passkey&&) = delete;
    Passkey(const Passkey&) = delete;
    Passkey& operator=(const Passkey&) = delete;
    ~Passkey() = default;

   private:
    Passkey() = default;
};
}  // namespace marex::core
#endif  // MAREX_CORE_PASSKEY_H
