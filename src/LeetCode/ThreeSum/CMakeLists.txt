cmake_minimum_required(VERSION 3.18)

    set(MODULE_NAME ThreeSum)

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ThreeSum.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ThreeSum.hpp
    )

    add_library(${MODULE_NAME} ${SOURCES})
    add_library(leetCode::${MODULE_NAME} ALIAS ${MODULE_NAME})

    target_include_directories(${MODULE_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

    target_link_libraries(${MODULE_NAME} PUBLIC
        CONAN_PKG::spdlog
        project_warnings
    )
