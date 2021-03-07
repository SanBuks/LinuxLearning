
- -o xxx.exe : 编译生成最终的可运行文件
- -std= : 编译标准如下
	- C++98
    - C++11 (aka C++0x)
    - C++14 (aka C++1y)
    - C++17 (aka C++1z)
    - C++2a (next planned standard in 2020)
- -Wall : 显示所有警告信息
- -g : 生成额外的debug信息

```bash
# 可以加上 -v 提示额外信息
$ cpp hello.c > hello.i
# 预处理
$ gcc -S hello.i
# 编译成汇编代码
$ as -o hello.o hello.s
# 汇编成机器代码
$ ld -o hello.exe hello.o ...libraries...
# 链接多个目标文件和库
```

- 库文件是一组被编译成目标文件的代码集合 :  
	- 静态库 链接时拷贝到可运行目标的位置 ".a" (archive file)
	- 动态库 链接时只在可运行目标位置创建小的表, 运行时根据信息加载相关机器代码 ".so" (shared objects)

- 环境 : 
	- PATH: For searching the executables and run-time shared libraries (.dll, .so).
	- CPATH: For searching the include-paths for headers. It is searched after paths specified in -I<dir> options. C_INCLUDE_PATH and CPLUS_INCLUDE_PATH can be used to specify C and C++ headers if the particular language was indicated in pre-processing.
	- LIBRARY_PATH: For searching library-paths for link libraries. It is searched after paths specified in -L<dir> options.
