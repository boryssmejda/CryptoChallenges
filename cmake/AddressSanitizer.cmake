function(add_address_sanitizer target_name)

    set(ADDRESS_SANITIZER_FLAGS -fsanitize=address -g3 -fno-omit-frame-pointer)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -g3 -fno-omit-frame-pointer)

    target_compile_options(${target_name} INTERFACE ${ADDRESS_SANITIZER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS})
    target_link_options(${target_name} INTERFACE ${ADDRESS_SANITIZER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS})
endfunction()
