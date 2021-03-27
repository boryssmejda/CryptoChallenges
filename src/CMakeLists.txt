cmake_minimum_required(VERSION 3.18)

    add_subdirectory(Numbers)

    add_library(cryptoLib STATIC)

    target_link_libraries(cryptoLib
        PRIVATE
        crypto::Numbers
        OpenSSL::SSL
        OpenSSL::Crypto
    )
