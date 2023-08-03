cmake_minimum_required (VERSION 3.8)

project ("socket lib")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../socket_lib/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../socket_lib/lib)

set(CMAKE_CXX_STANDARD  17)
set(demo_compile_files ${CMAKE_CURRENT_SOURCE_DIR}/web_demo.cpp)
add_executable(web_demo ${demo_compile_files})

target_link_libraries(web_demo tinynetwork)