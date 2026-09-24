cmake_minimum_required(VERSION 3.20)

include(FetchContent)

FetchContent_Declare(BOOST
    GIT_REPOSITORY https://github.com/boostorg/unordered.git
    GIT_TAG boost-1.92.0
)

FetchContent_Declare(CATCH2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.16.0
)

FetchContent_MakeAvailable(
    BOOST CATCH2
)