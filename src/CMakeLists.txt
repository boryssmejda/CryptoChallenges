cmake_minimum_required(VERSION 3.18)

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/HexAndBase64Converter/hexAndBase64Converter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/HexAndBase64Converter/hexAndBase64Converter.hpp
    )

    add_library(hexAndBase64Converter STATIC ${SOURCES})
    add_library(crypto::hexAndBase64Converter ALIAS hexAndBase64Converter)
    target_include_directories(hexAndBase64Converter INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    )

    target_link_libraries(hexAndBase64Converter PRIVATE 
        fmt
        spdlog
        OpenSSL::SSL
        OpenSSL::Crypto
    )
