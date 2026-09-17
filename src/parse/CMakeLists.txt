cmake_minimum_required(VERSION 3.20)
project(parse)

include(${CMAKE_SOURCE_DIR}/cmake/flags.cmake)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_CLANG_TIDY ON)

add_library(${PROJECT_NAME}
    parse.cpp
    token_stream.cpp
    translation_unit.cpp
    expr_kind.cpp
    expr_factory.cpp

    nodes/ast_node.cpp
    nodes/op_node.cpp
    nodes/binary_op.cpp
    nodes/VarDecl.cpp
    nodes/return_node.cpp
    nodes/func_node.cpp
    nodes/func_call.cpp
    nodes/expr.cpp
    nodes/expr_builder.cpp

    nodes/exceptions/invalid_token_exception.cpp
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
