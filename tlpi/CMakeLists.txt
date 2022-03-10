cmake_minimum_required(VERSION 3.22.0)
project(tlpi)

set(CMAKE_CXX_STANDARD          11    CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON    CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE            Debug CACHE INTERNAL "")

# 根据 Makefile.inc 设定的编译参数, 关闭 忽略 warning 提示的选项
#-D_XOPEN_SOURCE=600    (已定义)
#-D_DEFAULT_SOURCE      (已定义)
#-w                     (已定义)
#-Wall                  (已定义)
#-Wpedantic             (已定义)
#-std=c99               (cmake支持)
#-g                     (cmake支持)
# -I${TLPI_INCL_DIR}    (cmake支持)
#-Wmissing-prototypes   (C语言 特有)
#-Wno-sign-compare      (-Wall)
#-Wimplicit-fallthrough (-Wextra)
#-Wno-unused-parameter  (-Wextra)
set(MY_CMAKE_CXX_FLAGS "-g -D_XOPEN_SOURCE=600 -D_DEFAULT_SOURCE\
                        -w -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG ${MY_CMAKE_CXX_FLAGS} CACHE INTERNAL "")

add_subdirectory(lib)
#add_subdirectory(03_system_programming_concepts)
#add_subdirectory(04_the_universal_io_model)
add_subdirectory(05_io_further_details)