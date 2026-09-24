cmake_minimum_required(VERSION 3.20)
project(lex_tests)


add_executable(${PROJECT_NAME}
    test_lex.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    core
    lex
    Catch2
)

add_test(NAME ${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
)