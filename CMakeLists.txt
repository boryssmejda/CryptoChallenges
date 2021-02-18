cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")

project(CryptoChallenges CXX)

option(BUILD_TESTS "BUILD_TESTS" OFF)

    if(BUILD_TESTS)
        message(STATUS "Building the project with Unit Tests")
        add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest)
    endif()

    find_package(OpenSSL REQUIRED)

    add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/fmt)
    add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/spdlog)
    add_subdirectory(src)

    if(BUILD_TESTS)
        enable_testing()
        add_subdirectory(test)
    endif()
