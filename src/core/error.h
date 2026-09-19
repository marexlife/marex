#ifndef MAREX_CORE_ERROR_H
#define MAREX_CORE_ERROR_H
#include <string>

namespace marex::core {
class Error {
   public:
    explicit Error(std::string&& error_message);
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