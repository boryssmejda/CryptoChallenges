cmake_minimum_required(VERSION 3.18)

    get_target_property(SPDLOG_LOCATION spdlog INCLUDE_DIRECTORIES)
    get_target_property(GTEST_LOCATION gtest INCLUDE_DIRECTORIES)

    add_subdirectory(HexAndBase64Converter)

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/mainTestStartingPoint.cpp
    )

    add_executable(cryptoTests ${SOURCES})
    add_dependencies(cryptoTests crypto::hexAndBase64Converter_test)

    target_link_libraries(cryptoTests
        PRIVATE
            $<TARGET_OBJECTS:crypto::hexAndBase64Converter_test>
            crypto::hexAndBase64Converter
            spdlog
            gtest
            gmock
            gtest_main
    )

    add_test(NAME cryptoTests COMMAND cryptoTests)
