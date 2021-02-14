cmake_minimum_required(VERSION 3.18)

    add_library(hexAndBase64Converter_test OBJECT hexAndBase64Converter_test.cpp)
    add_library(crypto::hexAndBase64Converter_test ALIAS hexAndBase64Converter_test)
    add_dependencies(hexAndBase64Converter_test crypto::hexAndBase64Converter)

    target_link_libraries(hexAndBase64Converter_test
        PRIVATE
            gmock
            gtest
            gtest_main
            hexAndBase64Converter
    )
