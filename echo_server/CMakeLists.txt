cmake_minimum_required(VERSION 3.10)
project(echo_server)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/socket)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/server)