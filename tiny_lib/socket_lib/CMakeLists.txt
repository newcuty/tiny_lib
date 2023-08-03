
cmake_minimum_required (VERSION 3.8)

project ("socket lib")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD  17)
set(socket_lib_compile_file ${CMAKE_CURRENT_SOURCE_DIR}/src/socket.cpp)



add_library(tinynetwork STATIC ${socket_lib_compile_file})
SET_TARGET_PROPERTIES(tinynetwork PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(tinynetwork ws2_32)

