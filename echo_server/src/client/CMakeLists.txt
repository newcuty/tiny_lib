cmake_minimum_required(VERSION 3.10)
project(echo_client)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src/socket)


#message(STATUE "*****************include path is ${CMAKE_CURRENT_SOURCE_DIR}/../../*********************")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(client_compile_files client.cpp)

add_executable(echo_client ${client_compile_files})
target_link_libraries(echo_client tiny_socket pthread)