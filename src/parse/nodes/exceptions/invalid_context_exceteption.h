#ifndef MAREX_PARSE_INVALIDCONTEXTEXCEPTION_H
#define MAREX_PARSE_INVALIDCONTEXTEXCEPTION_H
#include <string>

namespace marex::parse {
class InvalidContextException final {
   public:
    explicit InvalidContextException(
        std::string&& message);

   private:
    std::string message_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_INVALIDCONTEXTEXCEPTION_H