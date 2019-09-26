cmake_minimum_required(VERSION 3.13)

add_executable(main_zsim main.cpp)

target_link_libraries(main_zsim PUBLIC libblifparse)
target_link_libraries(main_zsim PUBLIC core)
target_link_libraries(main_zsim PUBLIC graph)
target_link_libraries(main_zsim PUBLIC id_generator)
