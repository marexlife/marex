#ifndef MAREX_CORE_ERROR_H
#define MAREX_CORE_ERROR_H
#include <exception>
#include <memory>
#include <string>
#include <string_view>

#include "passkey.h"

namespace marex::core {
class Error {
   public:
    [[nodiscard]] static std::unique_ptr<Error>
    from_message(std::string&& error_message);
    [[nodiscard]] static std::unique_ptr<Error>
    from_exception(const std::exception& exception);
    [[nodiscard]] static std::unique_ptr<Error>
    from_nothing();

    [[nodiscard]] std::string_view get_error_message()
        const {
        return error_message_;
    }

    explicit Error(
        [[maybe_unused]] core::Passkey<Error> passkey,
        std::string&& error_message);

    virtual ~Error() = default;

    Error(Error&&) = delete;
    Error& operator=(Error&&) = delete;
    Error(const Error&) = delete;
    Error& operator=(const Error&) = delete;

   private:
    std::string error_message_;
};
}  // namespace marex::core
#endif  // MAREX_CORE_ERROR_H