cmake_minimum_required(VERSION 3.10)
project(echo_socket)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

#message(STATUE "*****************include path is ${CMAKE_CURRENT_SOURCE_DIR}/../../*********************")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(socket_compile_files socket.cpp)

add_library(tiny_socket SHARED ${socket_compile_files})
#target_link_libraries(tiny_socket pthread)