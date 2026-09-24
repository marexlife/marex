cmake_minimum_required(VERSION 3.20)
project(lex)

add_subdirectory(tests)

include(${CMAKE_SOURCE_DIR}/cmake/flags.cmake)

add_library(${PROJECT_NAME}
    lexer.cpp
    lex_print.cpp
    token.cpp
    source_pos.cpp
    token_factory.cpp
    token_kind.cpp
)

target_compile_options(${PROJECT_NAME} PUBLIC
    ${MAREX_FLAGS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    core
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
