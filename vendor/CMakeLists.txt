cmake_minimum_required(VERSION 3.20)

include(FetchContent)

FetchContent_Declare(BOOST
    GIT_REPOSITORY https://github.com/boostorg/unordered.git
    GIT_TAG boost-1.92.0
)

FetchContent_MakeAvailable(
    ${BOOST}
)