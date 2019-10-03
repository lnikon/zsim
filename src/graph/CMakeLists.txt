cmake_minimum_required(VERSION 3.13)

project(graph CXX)

set(GRAPH_DIR "${CMAKE_SOURCE_DIR}/src/graph")
file(GLOB_RECURSE GRAPH_CPP "${GRAPH_DIR}/*.cpp")
file(GLOB_RECURSE GRAPH_HPP "${GRAPH_DIR}/*.hpp")

add_library(graph STATIC ${GRAPH_CPP} ${GRAPH_HPP})

target_include_directories(graph PUBLIC ${GRAPH_DIR})
target_link_libraries(graph PUBLIC core)
