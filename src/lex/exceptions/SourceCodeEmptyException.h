#ifndef MAREX_LEX_SOURCECODEMPTYEXCEPTION_H
#define MAREX_LEX_SOURCECODEMPTYEXCEPTION_H
#include <exception>

namespace marex::lex {
class SourceCodeEmptyException final
    : public std::exception {
   public:
    explicit SourceCodeEmptyException() = default;

    const char* what() const noexcept override;
};
}  // namespace marex::lex
#endif  // MAREX_LEX_SOURCECODEMPTYEXCEPTION_H