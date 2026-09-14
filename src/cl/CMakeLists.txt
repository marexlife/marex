cmake_minimum_required(VERSION 3.20)
project(cl)

include(${CMAKE_SOURCE_DIR}/cmake/flags.cmake)

set(CMAKE_BUILD_TYPE Release)

add_library(${PROJECT_NAME}
    Cli.cpp
)

target_compile_options(${PROJECT_NAME} PUBLIC
    ${MAREX_FLAGS}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
