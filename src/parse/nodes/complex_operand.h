#ifndef MAREX_PARSE_COMPLEXOPERAND_H
#define MAREX_PARSE_COMPLEXOPERAND_H
#include <functional>
#include <memory>
#include <string>

#include "nodes/operand.h"

namespace marex::parse {
class Operator;

class ComplexOperand final : public Operand {
   public:
    explicit ComplexOperand(std::shared_ptr<Operator>&& operand);

    [[nodiscard]] std::reference_wrapper<const Operator>
    get_operator() const {
        return *operator_;
    }

    [[nodiscard]] std::string as_c() override;

   private:
    std::shared_ptr<Operator> operator_;
};
}  // namespace marex::parse
#endif  // MAREX_PARSE_COMPLEXOPERAND_H