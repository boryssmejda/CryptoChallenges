cmake_minimum_required(VERSION 3.18)
    add_subdirectory(Numbers)

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/mainTestStartingPoint.cpp
    )

    add_executable(ut ${SOURCES})

    target_link_libraries(ut
        PRIVATE
            project_warnings
            cryptoLib
            CONAN_PKG::gtest
            $<TARGET_OBJECTS:crypto::Numbers_test>
    )

    add_test(NAME ut COMMAND ut)

    add_custom_command(TARGET ut
            POST_BUILD
            COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --progress --output-on-failure
            COMMENT "Running CTest after building tests!"
    )

