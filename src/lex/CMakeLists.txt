cmake_minimum_required(VERSION 3.20)
project(lex)

include(${CMAKE_SOURCE_DIR}/cmake/flags.cmake)

set(CMAKE_BUILD_TYPE Release)

add_library(${PROJECT_NAME}
    Lexer.cpp
    TokenFactory.cpp
    LexerPrinter.cpp
    Token.cpp
    SourcePos.cpp
    TokenKind.cpp
    exceptions/SourceCodeEmptyException.cpp
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
