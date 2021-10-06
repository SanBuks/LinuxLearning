cmake_minimum_required(VERSION 3.1.7)
project(01_progconc)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

add_executable(get_libc_version get_libc_version.cpp)
#target_link_libraries(copy PRIVATE tlpi_header)
#target_include_directories(copy PRIVATE ${lib_SOURCE_DIR})