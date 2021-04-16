cmake_minimum_required(VERSION 3.18)

    add_subdirectory(Numbers)

    add_library(cryptoLib INTERFACE)

    target_link_libraries(cryptoLib
        INTERFACE
        crypto::Numbers
    )

