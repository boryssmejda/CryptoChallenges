cmake_minimum_required(VERSION 3.18)

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/TestBinary.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TestDecimal.cpp
    )

    add_library(Numbers_test OBJECT
        ${SOURCES}
    )

    add_library(crypto::Numbers_test ALIAS Numbers_test)
    add_dependencies(Numbers_test Numbers)

    target_link_libraries(Numbers_test
        PUBLIC
            Numbers
            CONAN_PKG::spdlog
            CONAN_PKG::gtest
    )
