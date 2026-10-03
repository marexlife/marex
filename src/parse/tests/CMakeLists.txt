cmake_minimum_required(VERSION 3.20)
project(parse_tests)

add_executable(${PROJECT_NAME}
    main.cpp
    expr_build_tester.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    parse
)

enable_testing()

add_test(${PROJECT_NAME} ${PROJECT_NAME})
