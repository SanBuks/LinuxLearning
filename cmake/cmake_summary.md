### 设置顶层 cmake
```cmake
# 设置 是否链接动态库 (作为项目信息, 一定在 configure_file() 前设置)
option(USE_MYMATH "Use tutorial implementation" ON)

#... 

# 根据选项收集 动态库名称, 路径
if (USE_MYMATH)
    # 增加 子文件中的库
    add_subdirectory(MathFunctions)
    list(APPEND EXTRA_LIBS MathFunctions)
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif()

# ...

# 增加 动态库链接
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})
# 增加 include 目录
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           ${EXTRA_INCLUDES})
```

## 1.3 设置依赖条件
### 减少顶层 cmake 条件
```cmake
if (USE_MYMATH)
    add_subdirectory(MathFunctions)
    list(APPEND EXTRA_LIBS MathFunctions)
#   list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif()

target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}")
#                          ${EXTRA_INCLUDES})
```


### 增加 ctest 设置
```cmake
# 开启测试
enable_testing()
# 增加 名为 Runs  命令为 Tutorial 25 的测试用例
add_test(NAME Runs COMMAND Tutorial 25)

# 增加 名为 Runs  命令为 Tutorial 的测试用例
# 期待的输出符合正则表达式 Usage:.*number
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage
        PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# 命名 do_test 函数
#     target : 测试用例程序名称
#     arg : 测试用例程序参数
#     result : 测试用例程序输出结果
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
          PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction(do_test)

do_test(Tutorial 4 "4 Is 2")
do_test(Tutorial 9 "9 Is 3")
do_test(Tutorial 5 "5 Is 2.236")
do_test(Tutorial 7 "7 Is 2.645")
do_test(Tutorial 25 "25 Is 5")
do_test(Tutorial -25 "-25 Is [nan|nan|0]")
do_test(Tutorial 0.0001 "0.0001 Is 0.01")
```

### ctest 命令
> ctest [ -N | -VV | -C \<cfg>] 
> 在 build_dir 下开启测试

- `-N` : 显示测试用例信息, 不测试
- `-VV` : 显示详细信息
- `-C <cfg>` : 设置测试的运行配置为Debug


# 1. cmake 基础
```bash
# [modern-cmake] 项目基本结构
- project
  - .gitignore
  - README.md
  - LICENCE.md
  - CMakeLists.txt
  - cmake
    - FindSomeLib.cmake
    - something_else.cmake
  - include  # 头文件目录中没有 CmakeLists 
    - project  # 内置 project 目录 防止 install headers 产生冲突
      - lib.hpp
  - src
    - CMakeLists.txt
    - lib.cpp
  - apps
    - CMakeLists.txt
    - app.cpp
  - tests
    - CMakeLists.txt
    - testlib.cpp
  - docs
    - CMakeLists.txt
  - extern
    - googletest
  - scripts
    - helper.py
```

## 1.1 hello-cmake & hello-headers
### 基础 CmakeLists
```cmake
# 1. 设置 构建工具 cmake 最小版本号
cmake_minimum_required(VERSION 3.20)
# 2. 设置 项目名称 和 项目版本号 (优先设置)
project(Tutorial VERSION 1.0)
# 3. 增加 可执行目标 手动命名/用预设变量
add_executable(Tutorial tutorial.cpp)
#add_executable(${PROJECT_NAME} tutorial.cpp)
```
### 构建相关命令
- Out-of-Source Build : 在其他目录下构建项目
- In-Place Build : 在源文件目录下构建项目
```bash
# 1. 构建命令 (MinGW 64 环境下)
# project/build/ : out-of-source build
cmake -G"MinGW Makefiles" 
      -DCMAKE_C_COMPILER=gcc 
      -DCMAKE_CXX_COMPILER=g++ 
      -DCMAKE_MAKE_PROGRAM=make 
      ..
# 2. 生成目标文件
# cmake 生成目标文件
cmake --build .
# make 生成目标文件 (输出额外信息)
make VERBOSE=1
# 3. 清理生成的二进制文件
make clean
```

### 预设变量
```bash
# 顶层 cmake 的 信息
CMAKE_PROJECT_NAME
CMAKE_SOURCE_DIR
CMAKE_BINARY_DIR

# 当前 cmake 信息
CMAKE_CURRENT_SOURCE_DIR 
CMAKE_CURRENT_BINARY_DIR 

# 与当前作用域或上层目录中最接近的 project 信息
PROJECT_NAME 
PROJECT_SOURCE_DIR
PROJECT_BINARY_DIR

# 子目录 信息
subdirectory_SOURCE_DIR
subdirectory_BINARY_DIR
```

### 定义变量
```cmake
# [modern-cmake]
# 建议在 add_xxx() 中直接声明多个文件因为 xxx 本身可以复用
# 而且可以清晰看到文件的变动

# 1. 通过 set 定义变量
set(SOURCES src/sss src/xxx)
add_executable(TARGET ${SOURCES})
# 2. 通过 file 定义通配的变量 
file(GLOB SOURCES "src/*.cpp")
file(GLOB SOURCES2 RELATIVE "D:/Project/cmake-examples/01-basic/B-hello-headers/build"
     "src/*.cpp") # 以 relative目录为基础的相对路径
add_executable(TARGET ${SOURCES})
# 3. 变量的类型
# cmake 中 有两种类型变量 : normal, cache
set (MY_TEST "333")  # normal
set (MY_TEST "111" CACHE STRING "test")  # cache
set (MY_TEST "222" CACHE STRING "test" FORCE)  # unset "333"
set (MY_TEST "333")  # 显示 333
# 如果 cache 被增加或修改, 会移除作用域内的同名 normal 变量
# (1) 在 函数作用域内 寻找变量, 否在在 目录作用域中 寻找变量
# (2) 如果找到 normal 变量则绑定
# (3) 如果没找到则绑定 cache 变量
# (4) FORCE 定义 cache 变量会 unset 统一作用域内的同名 normal 变量
```

### 增加头文件目录
```cmake
# 增加 目标的 include 目录 (等效于 -Idir)
target_include_direcotries(Tutorial
                           SYSTEM   # 视为系统头文件
                           AFTER    # 追加在包含头文件路径之前, (BEFORE)
                           PRIVATE  # 定义作用域
                           "${PROJECT_SOURCE_DIR}/include")
```

### 可复用目标的可见性
- 任何可被复用的目标(目录, 库等等)存在两个变量
    - INCLUDE_XXXX : 构建自己本身需要的目标
    - INTERFACE_INCLUDE_XXXX : 构建依赖于自己本身的目标所需要的目标
- 作用域区别:  
    - PRIVATE: INCLUDE_XXXX 
    - INTERFACE: INTERFACE_INCLUDE_XXXX
    - PUBLIC: INCLUDE_XXXX 和 INTERFACE_INCLUDE_XXXX

## 2.2 static library & shared library
### 增加静态库
```cmake
# 1. 增加 静态库 (hello_library.a)
add_library(hello_library STATIC 
    src/Hello.cpp
)
# 2. 给静态库增加头文件目录
# 在 include 内设本项目文件夹和多个子项目文件夹有助于避免头文件冲突
# 如 #include "project/sub1/static/yyy.h"
target_include_directories(hello_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)
# 3. 给 目标 增加静态库 (-rdynamic libhello_library.a)
target_link_libraries(hello_binary
    PRIVATE 
        hello_library
)
```

### 增加动态库
```cmake
# 1. 增加 动态库 (hello_library.so)
add_library(hello_library SHARED 
    src/Hello.cpp
)
# 2. 给动态库增加头文件目录
target_include_directories(hello_library 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
# 3. 给动态库起别名 hello::library
add_library(hello::library ALIAS hello_library)

# 3. 给 目标 增加动态库 (-rdynamic libhello_library.so)
target_link_libraries(hello_binary
    PRIVATE
        hello::library
)
```

## 2.3 installing & build_type
### install 命令
```bash
# 1. 构建前 install 配置
cmake .. -DCMAKE_INSTALL_PREFIX=D:/Project/cmake-examples/01-basic/E-installing/install  
# 2. 构建后 install
cmake --install . --prefix "D:/Project/cmake-examples/01-basic/E-installing/install"
# 3. 使用 make install 其中 DESTDIR 可以配置 ${CMAKE_INSTALL}前缀 
#    用于暂存和测试
make install DESTDIR=/d/temp_install
```

### install 配置
```cmake
# 0. 设置 install 默认目录
message(STATUS "Set CMAKE_INSTALL_PREFIX to ${CMAKE_SOURCE_DIR}/install")
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE STRING
    "default install path" FORCE)

# 1. install 可执行目标 到 ${CMAKE_INSTALL_PREFIX}/bin 下
install(TARGETS cmake_examples_inst_bin
    DESTINATION bin)

# 2. install 库文件 到 ${CMAKE_INSTALL_PREFIX}/lib 下 (windows : /bin)
# linux
#install(TARGETS cmake_examples_inst
#    LIBRARY DESTINATION lib)
# windows 
install(TARGETS cmake_examples_inst
    LIBRARY DESTINATION lib  # .a/.so 库文件
    RUNTIME DESTINATION bin)  # .dll 库文件

# 3. install include 目录下的文件 到 ${CMAKE_INSTALL_PREFIX}/include 下
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/  # 最后的 / 不能丢
    DESTINATION include)

# 4. install 配置文件 到 ${CMAKE_INSTALL_PREFIX}/etc 下
install (FILES cmake-examples.conf
    DESTINATION etc)
```

### uninstall 配置
- 首先, 在 ${PROJECT_SOURCE_DIR} 下创建 cmake_uninstall.cmake.in 文件
```cmake
if(NOT EXISTS "@CMAKE_BINARY_DIR@/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: @CMAKE_BINARY_DIR@/install_manifest.txt")
endif()

file(READ "@CMAKE_BINARY_DIR@/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling $ENV{DESTDIR}${file}")
  if(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    exec_program(
      "@CMAKE_COMMAND@" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing $ENV{DESTDIR}${file}")
    endif()
  else(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    message(STATUS "File $ENV{DESTDIR}${file} does not exist.")
  endif()
endforeach()
```

- 最后, 在 CMakeLists 中增加逻辑
```cmake
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
```

> 对于 UNIX 系统 可以 使用 xargs rm < install_manifest.txt 直接删除 install 文件
 
 
### 构建类型
```cmake
# 1. 内置构建类型
#    Release        : -O3 -DNDEBUG 
#    Debug          : -g 
#    MinSizeRel     : -Os -DNDEBUG
#    RelWithDebInfo : -O2 -g -DNDEBUG

# 2. 提供构建类型
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
  # 给 gui 提供可选择的值
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS 
               "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# 3. 通过命令 设置 cmake .. -DCMAKE_BUILD_TYPE=Release
```

## 2.4 compile options & import library
### 设置编译选项与预定义
```cmake
# 1. 设置全局的编译选项 CMAKE_CXX_FLAGS/CMAKE_C_FLAGS
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING 
     "Set C++ Compiler Flags" FORCE)
# 2. 增加 per target 预定义
target_compile_definitions(cmake_examples_compile_flags 
                           PRIVATE EX3)
# 3. 增加 per target 编译选项
target_compile_options(cmake_examples_compile_flags
                       PRIVATE -std=c++11
                       PRIVATE -pedantic)
# 4 命令行设定编译选项和预定义 
#   cmake .. -DCMAKE_CXX_FLAGS="-DEX3"
```

### 第三方库
1. 安装 boost 库
```bash
$ ./bootstrap.sh --prefix=D:\DevelopTool\git\usr\local
$ ./b2 install
```

2. 找包
```cmake
# 查找包的两种模式: config 模式 或 module 模式
# 1. 指定 XXXConfig.cmake 路径变量 BOOSTROOT 
set(BOOST_ROOT "D:/DevelopTool/git/usr/local/lib/cmake/Boost-1.77.0")
# 2. 指定 ${CMAKE_MODULE_PATH} 为查找路径
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};D:/DevelopTool/git/usr/local/lib/cmake/Boost-1.77.0")

# 3. find_package 命令
# Boost      : 库名, 需要寻找 FindXXXX.cmake / XXXXConfig.cmake
# 1.46.1     : 库版本号
# REQUIRED   : 必须包含, 否则停止构建
# COMPONENTS : 子库
find_package(Boost 1.77.0 REQUIRED COMPONENTS filesystem system)

# 4. 找包后有些变量作为结果会被设置如
# Boost_INCLUDE_DIRS, Boost_FOUND 等
if (Boost_FOUND)
    message ("boost found")
else ()
    message (FATAL_ERROR "Cannot find Boost")
endif ()

# 5. 从 cmake 3.5 开始支持 库的别名 链接
target_link_libraries(third_party_include
                      PRIVATE
                      Boost::filesystem)
# 等价于 Boost_XXXX_LIBRARY
target_link_libraries(third_party_include
                      PRIVATE
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_FILESYSTEM_LIBRARY})
# 头文件 
target_include_directories(third_party_include PRIVATE ${Boost_INCLUDE_DIRS})
```

### 编译器, make, linker
```bash
$ cmake .. -DCMAKE_C_COMPILER=clang-3.6 
           -DCMAKE_CXX_COMPILER=clang++-3.6
           -DCMAKE_MAKE_PROGRAM=make4.2.1
           -DCMAKE_LINKER=ld2.30
```

### 生成器
```bash
# cmake 是元构建器, 可以生成不同构建工具脚本
# 可显示所有类型编译脚本
$ cmake --help 
# 生成 MinGW 环境下的 makefile 文件
$ cmake .. -G"MinGW Makefiles"
```

### 设置标准
```cmake
# 1. [2.8] 版本 手动判断编译器是否支持 相关标准
# 判断编译器是否支持标准
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
# 查看结果然后设置标准
if(COMPILER_SUPPORTS_CXX11)#
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)#
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# 2. [3.1] 版本 会对编译器支持标准的版本做一个最接近处理
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 3. [3.1] 版本 会对编译器支持的标准特性选择支持的标准 
#    根据 feature 设置最合适的 标准 (存在传播类型)
target_compile_features(hello_cpp11 PUBLIC cxx_auto_type)
#    打印编译器支持的所有 feature
message("List of compile features: ${CMAKE_CXX_COMPILE_FEATURES}")
```

## 2.5 sub-project
- 顶层目录:
```cmake
# 1. 增加子目录
add_subdirectory(sublibrary1)
add_subdirectory(sublibrary2)
add_subdirectory(subbinary)

# 2. 在每个子目录下 显示信息
function(print name)
  message("**********${name}**********")
  message("[PROJECT_NAME] IS : ${PROJECT_NAME}")
  message("[CMAKE_PROJECT_NAME] IS : ${CMAKE_PROJECT_NAME}")

  message("[PROJECT_SOURCE_DIR] IS : ${PROJECT_SOURCE_DIR}")
  message("[CMAKE_SOURCE_DIR] IS : ${CMAKE_SOURCE_DIR}")
  message("[CMAKE_CURRENT_SOURCE_DIR] IS : ${CMAKE_CURRENT_SOURCE_DIR}")

  message("[PROJECT_BINARY_DIR] IS : ${PROJECT_BINARY_DIR}")
  message("[CMAKE_BINARY_DIR] IS : ${CMAKE_BINARY_DIR}")
  message("[CMAKE_CURRENT_BINARY_DIR] IS : ${CMAKE_CURRENT_BINARY_DIR}")

  message("[subbinary_SOURCE_DIR] IS : ${subbinary_SOURCE_DIR}")
  message("[subbinary_BINARY_DIR] IS : ${subbinary_BINARY_DIR}")
endfunction()

# install 子文件夹
install (TARGETS sublibrary1
         DESTINATION bin)
install (DIRECTORY ${sublibrary2_SOURCE_DIR}/include/
         DESTINATION include)
install (TARGETS subbinary
         DESTINATION bin)
```

- 子目录:
```cmake
# 1. sublibrary1 
project (sublibrary1)
add_library(${PROJECT_NAME} src/sublib1.cpp)
add_library(sub::lib1 ALIAS ${PROJECT_NAME})
target_include_directories( ${PROJECT_NAME}
                            PUBLIC ${PROJECT_SOURCE_DIR}/include)

# 2. sublibrary2
project (sublibrary2)
add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::lib2 ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE
                           ${PROJECT_SOURCE_DIR}/include)
# 3. subbinary
project(subbinary)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} sub::lib1 sub::lib2 )
```

## 2.6 configure files & protobuf
### 配置文件
```cmake
# 1. 设置 project 版本号
project(cf_example VERSION 0.21.1)
#    等价于
#set (cf_example_VERSION_MAJOR 0)
#set (cf_example_VERSION_MINOR 2)
#set (cf_example_VERSION_PATCH 1)
#set(cf_example_VERSION "${cf_example_VERSION_MAJOR}.${cf_example_VERSION_MINOR}.${cf_example_VERSION_PATCH}")

# 2. 配置 设置文件
configure_file(ver.h.in ${PROJECT_BINARY_DIR}/ver.h)
configure_file(path.h.in ${PROJECT_BINARY_DIR}/path.h @ONLY)  # 仅仅替换 @ 型变量
# ver.h.in : const char* ver = "${cf_example_VERSION}";
# path.h.in : const char* path = "@CMAKE_SOURCE_DIR@";
```

### protobuf 生成
- 安装 msys2 :
```bash
# 1. 安装后, 从服务器下载新的软件包数据库, 升级所有已安装的软件包
$ pacman -Syu
$ pacman -Su
# 2. 安装指定的开发包, 不重新安装已是最新的软件包
$ pacman -S --needed base-devel mingw-w64-x86_64-toolchain
# 3. 安装 protobuf
$ pacman -S mingw-w64-x86_64-protobuf 
# 4. 安装 cmake
pacman -S mingw-w64-x86_64-cmake
```

- 配置 clion :
```bash
# 1. ToolChain 设置 cmake, make, gcc, g++, gdb 
#    出现 Test cmake run finished error 可以忽略
# 2. Terminal 设置 /path/msys2/usr/bin/bash.exe --login -i
#    environment variable 增加 MSYSTEM=MINGW64
```

- 配置 protobuf :
```cmake
# 1. 找包
find_package(Protobuf REQUIRED)
if (PROTOBUF_FOUND)
  message("protobuf found")
else ()
  message(FATAL_ERROR "Cannot find Protobuf")
endif ()
# 2. 生成代码
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS
                      DESCRIPTORS PROTO_DESC
                      AddressBook.proto)
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS
#                      EXPORT_MACRO DLL_EXPORT
#                      foo.proto)
message("PROTO_SRCS = ${PROTO_SRCS}")
message("PROTO_HDRS = ${PROTO_HDRS}")
message("PROTO_DESC = ${PROTO_DESC}")
# 3. 生成目标
add_executable(protobuf_example main.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(protobuf_example PUBLIC
                           ${PROTOBUF_INCLUDE_DIRS}
                           ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS ${PROTOBUF_LIBRARIES})
target_link_libraries(protobuf_example PUBLIC
                      ${PROTOBUF_LIBRARIES}
                      protobuf::libprotobuf
                      protobuf::libprotobuf-lite
                      protobuf::libprotoc)
```

- 构建命令 :
```bash
cmake .. -G"MinGW Makefiles"
         -DCMAKE_C_COMPILER=gcc
         -DCMAKE_CXX_COMPILER=g++
         -DCMAKE_MAKE_PROGRAM=make 
         -DProtobuf_PROTOC_EXECUTABLE=/mingw64/bin/protoc
         -DCMAKE_BUILD_TYPE=Release
```

- 额外的变量
```cmake
set(Protobuf_SRC_ROOT_FOLDER "")
set(Protobuf_IMPORT_DIRS "${Protobuf_IMPORT_DIRS};")
set(Protobuf_DEBUG ON CACHE BOOL "" FORCE)
set(Protobuf_USE_STATIC_LIBS ON CACHE BOOL "" FORCE)

function(print)
  message(STATUS "Protobuf_FOUND is ${Protobuf_FOUND}")
  message(STATUS "Protobuf_VERSION is ${Protobuf_VERSION}")
  message(STATUS "Protobuf_INCLUDE_DIRS is ${Protobuf_INCLUDE_DIRS}")
  message(STATUS "Protobuf_LIBRARIES is ${Protobuf_LIBRARIES}")
  message(STATUS "Protobuf_PROTOC_LIBRARIES is ${Protobuf_PROTOC_LIBRARIES}")
  message(STATUS "Protobuf_LITE_LIBRARIES is ${Protobuf_LITE_LIBRARIES}")
  message(STATUS "Protobuf_LIBRARY is ${Protobuf_LIBRARY}")
  message(STATUS "Protobuf_PROTOC_LIBRARY is ${Protobuf_PROTOC_LIBRARY}")
  message(STATUS "Protobuf_INCLUDE_DIR is ${Protobuf_INCLUDE_DIR}")
  message(STATUS "Protobuf_PROTOC_EXECUTABLE is ${Protobuf_PROTOC_EXECUTABLE}")
  message(STATUS "Protobuf_LIBRARY_DEBUG is ${Protobuf_LIBRARY_DEBUG}")
  message(STATUS "Protobuf_PROTOC_LIBRARY_DEBUG is ${Protobuf_PROTOC_LIBRARY_DEBUG}")
  message(STATUS "Protobuf_LITE_LIBRARY is ${Protobuf_LITE_LIBRARY}")
  message(STATUS "Protobuf_LITE_LIBRARY_DEBUG is ${Protobuf_LITE_LIBRARY_DEBUG}")
endfunction()
```