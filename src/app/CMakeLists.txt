cmake_minimum_required(VERSION 3.20)
project(app)

include(${CMAKE_SOURCE_DIR}/cmake/flags.cmake)

set(CMAKE_BUILD_TYPE Release)

add_library(${PROJECT_NAME}
    app.cpp
)

target_compile_options(${PROJECT_NAME} PUBLIC
    ${MAREX_FLAGS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    lex
    parse
    fetch
    write
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
