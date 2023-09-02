cmake_minimum_required(VERSION 3.10)
project(echo_server)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src/socket)

#message(STATUE "*****************include path is ${CMAKE_CURRENT_SOURCE_DIR}/../../*********************")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(server_compile_files server.cpp)

add_executable(echo_server ${server_compile_files})
target_link_libraries(echo_server tiny_socket)