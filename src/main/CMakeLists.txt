cmake_minimum_required(VERSION 3.20)
project(main)

include(${CMAKE_SOURCE_DIR}/cmake/flags.cmake)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_compile_options(${PROJECT_NAME} PUBLIC
    ${MAREX_FLAGS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    app
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
)