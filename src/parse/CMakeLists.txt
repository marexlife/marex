cmake_minimum_required(VERSION 3.20)
project(parse)

include(${CMAKE_SOURCE_DIR}/cmake/flags.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_CLANG_TIDY ON)

add_library(${PROJECT_NAME}
    Parser.cpp
    ParserPack.cpp
    TranslationUnit.cpp
    ExpressionKind.cpp

    nodes/AstNode.cpp
    nodes/OpNode.cpp
    nodes/VarDecl.cpp
    nodes/IdentNode.cpp
    nodes/FuncNode.cpp
    nodes/FuncCall.cpp
    nodes/ReturnNode.cpp
    nodes/Expr.cpp
    nodes/StatementBuilder.cpp
    nodes/Statement.cpp
    nodes/exceptions/InvalidTokenException.cpp
    ExprFactory.cpp

    linter/CaseCheck.cpp
    linter/exceptions/WrongCaseException.cpp
)

target_compile_options(${PROJECT_NAME} PUBLIC
    ${MAREX_FLAGS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    lex
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
