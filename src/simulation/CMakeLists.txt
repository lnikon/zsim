cmake_minimum_required(VERSION 3.13)

project(simulation CXX)

set(SIMULATION_DIR "${CMAKE_SOURCE_DIR}/src/simulation")
file(GLOB_RECURSE SIMULATION_CPP "${SIMULATION_DIR}/*.cpp")
file(GLOB_RECURSE SIMULATION_HPP "${SIMULATION_DIR}/*.hpp")

add_library(simulation STATIC ${SIMULATION_CPP} ${SIMULATION_HPP})

target_include_directories(simulation PUBLIC ${SIMULATION_DIR})

target_link_libraries(simulation PUBLIC core)