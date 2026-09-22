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