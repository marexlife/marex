cmake_minimum_required(VERSION 3.20)

if(MSVC)
set(MAREX_FLAGS)
else()
set(MAREX_FLAGS
    -Wall
    -Wextra
    -Wconversion
    -Werror
)
endif()

