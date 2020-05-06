cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

set(CORE_INC_DIR "${CMAKE_SOURCE_DIR}/src/core")
file(GLOB_RECURSE CORE_CPP "${CORE_INC_DIR}/*.cpp")
file(GLOB_RECURSE CORE_HPP "${CORE_INC_DIR}/*.hpp")

set(LIBBLIFPARSER_INC_DIR "${CMAKE_SOURCE_SIR}/libs/libblifparser/src")

add_library(core STATIC
        ${CORE_CPP}
        ${CORE_HPP})

target_include_directories(core PUBLIC ${CORE_INC_DIR} ${LIBBLIFPARSER_INC_DIR})
target_link_libraries(core PUBLIC id_generator)
target_link_libraries(core PUBLIC graph)
target_link_libraries(core PUBLIC zsim_algorithm)
