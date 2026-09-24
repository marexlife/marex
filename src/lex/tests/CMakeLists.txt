cmake_minimum_required(VERSION 3.20)
project(lex_tests)

add_executable(${PROJECT_NAME}
    test_lex.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    core
    lex
)

enable_testing()

add_test(${PROJECT_NAME} ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ctest $<TARGET_FILE:${PROJECT_NAME}> --output-on-failure
)