#ifndef MAREX_APP_HELPSCREEN_H
#define MAREX_APP_HELPSCREEN_H
#include <string_view>

namespace marex::app {
inline const std::string_view help_screen =
    R"(Help screen:
A. --help to get to here
B. 'clear;' to clear the screen in Shell mode
C. list files that should be compiled)";
}
#endif // MAREX_APP_HELPSCREEN_H