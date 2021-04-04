if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -header-filter=.;
    -checks=*;)
endif()
