cmake_minimum_required(VERSION 3.13)

project(id_generator CXX)

set(ID_GENERATOR_DIR "${CMAKE_SOURCE_DIR}/src/id_generator")
file(GLOB_RECURSE ID_GENERATOR_CPP "${ID_GENERATOR_DIR}/*.cpp")
file(GLOB_RECURSE ID_GENERATOR_HPP "${ID_GENERATOR_DIR}/*.hpp")

add_library(id_generator STATIC ${ID_GENERATOR_CPP} ${ID_GENERATOR_HPP})

target_include_directories(id_generator PUBLIC ${ID_GENERATOR_DIR})
