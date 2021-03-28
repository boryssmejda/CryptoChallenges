# The code below is a partial modification of the code found here:
# https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake

find_program(GCOV_PATH gcov REQUIRED)
find_program(GCOVR_PATH gcovr REQUIRED)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "Code coverage works only for GCC! Aborting ...")
endif()

set(COVERAGE_COMPILER_FLAGS "-O0 -g -fprofile-arcs -ftest-coverage -fprofile-abs-path")

function(append_coverage_compiler_flags)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILER_FLAGS}" PARENT_SCOPE)
    message(STATUS "Appending code coverage compiler flags: ${COVERAGE_COMPILER_FLAGS}")
endfunction()

# Defines a target for running and collection code coverage information
# Builds dependencies, runs the given executable and outputs reports.
# NOTE! The executable should always have a ZERO as exit code otherwise
# the coverage generation will not complete.
#
# setup_target_for_coverage_gcovr_html(
#     NAME code_coverage                     # New target name
#     DEPENDENCIES executable_target         # Dependencies to build first
#     BASE_DIRECTORY "../"                   # Base directory for report
#     EXCLUDE "src/dir1/*" "src/dir2/*"      # Patterns to exclude
# )
function(setup_target_for_coverage)

    set(options NONE)
    set(oneValueArgs BASE_DIRECTORY NAME)
    set(multiValueArgs EXCLUDE DEPENDENCIES)
    cmake_parse_arguments(COVERAGE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Collect excludes
    set(GCOVR_EXCLUDES "")
    foreach(EXCLUDE ${COVERAGE_EXCLUDE})
        list(APPEND GCOVR_EXCLUDES "${EXCLUDE}")
    endforeach()
    list(REMOVE_DUPLICATES GCOVR_EXCLUDES)

    # Combine excludes to several -e arguments
    set(GCOVR_EXCLUDE_ARGS "")
    foreach(EXCLUDE ${GCOVR_EXCLUDES})
        list(APPEND GCOVR_EXCLUDE_ARGS "-e")
        list(APPEND GCOVR_EXCLUDE_ARGS "${EXCLUDE}")
    endforeach()

    # Create folder
    set(GCOVR_HTML_FOLDER_CMD
        ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/${COVERAGE_NAME}
    )
    # Running gcovr
    set(GCOVR_HTML_CMD
        ${GCOVR_PATH} --html --html-details -r ${COVERAGE_BASE_DIRECTORY}
        ${GCOVR_EXCLUDE_ARGS} --exclude-unreachable-branches
        --exclude-throw-branches
        --object-directory=${PROJECT_BINARY_DIR} 
        -o ${COVERAGE_NAME}/index.html
    )

    add_custom_target(${COVERAGE_NAME} ALL
        COMMAND ${GCOVR_HTML_FOLDER_CMD}
        COMMAND ${GCOVR_HTML_CMD}

        BYPRODUCTS ${PROJECT_BINARY_DIR}/${COVERAGE_NAME}/index.html  # report directory
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        DEPENDS ${COVERAGE_DEPENDENCIES}
        VERBATIM # Protect arguments to commands
        COMMENT "Running gcovr to produce HTML code coverage report."
    )
endfunction(setup_target_for_coverage)
