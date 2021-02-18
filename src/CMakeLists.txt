cmake_minimum_required(VERSION 3.18)

    set(MODULE_NAME hexAndBase64Converter)

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/HexAndBase64Converter/hexAndBase64Converter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/HexAndBase64Converter/hexAndBase64Converter.hpp
    )

    add_library(${MODULE_NAME} STATIC ${SOURCES})
    add_library(crypto::${MODULE_NAME} ALIAS ${MODULE_NAME})
    target_include_directories(${MODULE_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    )

    target_link_libraries(${MODULE_NAME} PRIVATE 
        fmt
        spdlog
        OpenSSL::SSL
        OpenSSL::Crypto
    )
