cmake_minimum_required(VERSION 3.18)

    get_target_property(SPDLOG_LOCATION spdlog INCLUDE_DIRECTORIES)
    get_target_property(GTEST_LOCATION gtest INCLUDE_DIRECTORIES)

    add_subdirectory(Numbers)

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/mainTestStartingPoint.cpp
    )

    add_executable(cryptoTests ${SOURCES})
    add_dependencies(cryptoTests crypto::Numbers_test)

    target_link_libraries(cryptoTests
        PRIVATE
            $<TARGET_OBJECTS:crypto::Numbers_test>
            crypto::Numbers
            spdlog
            gtest
            gmock
            gtest_main
    )

    add_test(NAME cryptoTests COMMAND cryptoTests)
