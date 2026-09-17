#ifndef MAREX_WALK_WRITE_H
#define MAREX_WALK_WRITE_H
#include "translation_unit.h"

namespace marex::write {
void write(parse::TranslationUnit&& translation_unit);
}  // namespace marex::write
#endif  // MAREX_WALK_WRITE_H