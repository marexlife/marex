cmake_minimum_required(VERSION 3.20)
project(parse_tests)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    parse
)

enable_testing()

add_test(${PROJECT_NAME} ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ctest $<TARGET_FILE:${PROJECT_NAME}> --output-on-failure
)