cmake_minimum_required(VERSION 3.13)

set(ZSIM_ALGORITHM_INC_DIR "${CMAKE_SOURCE_DIR}/src/zsim_algorithm")
file(GLOB_RECURSE ZSIM_ALGORITHM_CPP "${ZSIM_ALGORITHM_INC_DIR}/*.cpp")
file(GLOB_RECURSE ZSIM_ALGORITHM_HPP "${ZSIM_ALGORITHM_INC_DIR}/*.hpp")

set(LIBBLIFPARSER_INC_DIR "${CMAKE_SOURCE_SIR}/libs/libblifparser/src")

add_library(zsim_algorithm STATIC
		${ZSIM_ALGORITHM_CPP}
		${ZSIM_ALGORITHM_HPP})

target_include_directories(zsim_algorithm PUBLIC ${ZSIM_ALGORITHM_INC_DIR} ${LIBBLIFPARSER_INC_DIR})
