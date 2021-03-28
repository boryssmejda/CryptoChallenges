cmake_minimum_required(VERSION 3.18)

    set(MODULE_NAME Numbers)
    set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/inc/BaseNumber.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/inc/Binary.hpp
    )

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Binary.cpp
    )

    add_library(${MODULE_NAME} OBJECT ${SOURCES} ${HEADERS})
    add_library(crypto::${MODULE_NAME} ALIAS ${MODULE_NAME})

    target_include_directories(${MODULE_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    )

    target_link_libraries(${MODULE_NAME} PUBLIC
        CONAN_PKG::spdlog
        project_warnings
    )
