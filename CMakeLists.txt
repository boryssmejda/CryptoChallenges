cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")
set(CMAKE_POSITION_INDEPENDENT_CODE "ON")

project(CryptoChallenges CXX)

option(BUILD_TESTS "BUILD_TESTS" OFF)

    include(cmake/Git.cmake)
    git_init_submodules()

    # Link this 'library' to use the warnings specified in CompilerWarnings.cmake
    add_library(project_warnings INTERFACE)
    include(cmake/CompilerWarnings.cmake)
    set_project_warnings(project_warnings)

    if(ENABLE_COVERAGE)
        message(STATUS "Code coverage enabled!")

        include(cmake/coverage.cmake)
        # this functions must be called before creating any target with add_*
        # the function appends gcov flags to CXX_COMPILER_FLAGS,
        # so all sources are compiled with them.
        append_coverage_compiler_flags()

        setup_target_for_coverage(
            NAME ut_coverage
            DEPENDENCIES ut cryptoLib
            BASE_DIRECTORY "${CMAKE_SOURCE_DIR}/src"
            EXCLUDE "${CMAKE_SOURCE_DIR}/third_party"
        )
    endif()

    find_package(OpenSSL REQUIRED)

    add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/fmt)
    add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/spdlog)
    add_subdirectory(src)

    if(BUILD_TESTS)
        enable_testing()
        message(STATUS "Building the project with Unit Tests")
        add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest)
        add_subdirectory(test)
    endif()
