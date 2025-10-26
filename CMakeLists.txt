cmake_minimum_required(VERSION 3.15)

project(SrsTestProject LANGUAGES CXX)

set(SRC_ROOT          "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR       "${SRC_ROOT}/include")
set(LIB_SRC_DIR       "${SRC_ROOT}/lib")
set(EXEC_DIR          "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_library(srs_test STATIC
    "${LIB_SRC_DIR}/srs_test.cpp"
)

target_include_directories(srs_test PUBLIC
    "${INCLUDE_DIR}"          # expose the header location to users of the lib
)

macro(add_fuzz_exe exe_name source_file)
    add_executable(${exe_name}
        "${SRC_ROOT}/${source_file}"
    )
    target_include_directories(${exe_name} PRIVATE "${INCLUDE_DIR}")
    target_link_libraries(${exe_name} PRIVATE srs_test)

    set_target_properties(${exe_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${EXEC_DIR}
    )
endmacro()


add_fuzz_exe(fuzz_tester           "fuzz_tester.cpp")
add_fuzz_exe(metamorph_tester     "metamorph_tester.cpp")



