cmake_minimum_required(VERSION 3.20)
project(lex_tests)

add_executable(${PROJECT_NAME}
    main.cpp
    lexer_tester.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    core
    lex
)

enable_testing()

add_compile_definitions(${PROJECT_NAME}
    TESTING
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
