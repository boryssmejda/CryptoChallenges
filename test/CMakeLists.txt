cmake_minimum_required(VERSION 3.18)

    get_target_property(SPDLOG_LOCATION spdlog INCLUDE_DIRECTORIES)
    get_target_property(GTEST_LOCATION gtest INCLUDE_DIRECTORIES)

    add_subdirectory(Numbers)

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/mainTestStartingPoint.cpp
    )

    add_executable(ut ${SOURCES})
    add_dependencies(ut cryptoLib)

    target_link_libraries(ut
        PRIVATE
            $<TARGET_OBJECTS:crypto::Numbers_test>
            crypto::Numbers
            spdlog
            gtest
            gmock
            gtest_main
            project_warnings
    )

    add_test(NAME ut COMMAND ut)

    add_custom_command(TARGET ut
            POST_BUILD
            COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --progress --output-on-failure
            COMMENT "Running CTest after building tests!"
    )
