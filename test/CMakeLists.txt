cmake_minimum_required(VERSION 3.18)

    add_subdirectory(HexAndBase64Converter)

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/mainTestStartingPoint.cpp
    )

    add_executable(cryptoTests ${SOURCES})
    add_dependencies(cryptoTests crypto::hexAndBase64Converter_test)

    target_link_libraries(cryptoTests
        PRIVATE
            crypto::hexAndBase64Converter_test
            gtest
            gmock
            gtest_main
    )

    add_test(NAME cryptoTests COMMAND cryptoTests)
