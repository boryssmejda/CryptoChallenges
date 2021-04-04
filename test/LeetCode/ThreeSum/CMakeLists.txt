cmake_minimum_required(VERSION 3.18)

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Test_ThreeSum.cpp
    )

    add_library(ThreeSum_test OBJECT
        ${SOURCES}
    )

    add_library(leetCode::ThreeSum_test ALIAS ThreeSum_test)
    add_dependencies(ThreeSum_test leetCode::ThreeSum)

    target_link_libraries(ThreeSum_test
        PUBLIC
            leetCode::ThreeSum
            CONAN_PKG::spdlog
            CONAN_PKG::gtest
    )
