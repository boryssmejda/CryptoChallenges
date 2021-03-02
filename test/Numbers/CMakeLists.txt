cmake_minimum_required(VERSION 3.18)

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/TestBinary.cpp
    )

    add_library(Numbers_test OBJECT
        ${SOURCES}
    )

    add_library(crypto::Numbers_test ALIAS Numbers_test)

    target_link_libraries(Numbers_test PRIVATE Numbers)
    target_include_directories(Numbers_test
        PRIVATE
            ${SPDLOG_LOCATION}
            ${GTEST_LOCATION}
    )
