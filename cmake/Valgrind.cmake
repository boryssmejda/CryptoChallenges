function(run_ut_valgrind)
    set(options)
    set(oneValueArgs TARGET_NAME)
    set(multiValueArgs)

    cmake_parse_arguments(VALGRIND "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN})

    find_program(VALGRIND_PATH valgrind REQUIRED)

    set(VALGRIND_CMD
        ${VALGRIND_PATH} --tool=memcheck
        --leak-check=full
        --show-leak-kinds=all
        --track-origins=yes
    )

    add_custom_target(ut_valgrind ALL
        COMMAND ${VALGRIND_CMD} $<TARGET_FILE:${VALGRIND_TARGET_NAME}>
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        DEPENDS ${VALGRIND_TARGET_NAME}
        COMMENT "Running gcovr to produce HTML code coverage report."
    )
endfunction(run_ut_valgrind)
