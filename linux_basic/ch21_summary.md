# 第二十一章 源代码与tarball安装

1. $ file filename 查看文件类型
    - executable 可执行
    - dynamically linked 动态链接
    - test executable 脚本
2. 源代码通过编译器编译,连接器链接后生成可执行二进制程序,程序执行过程中会调用由函数库提供的函数
3. Make 与 Configure
    - make 帮助简化编译过程的命令
    - makfile 是执行make所依赖的文件,记录源代码如何编译
    - confgure检测操作环境来生成相关的makefile文件,检测内容有:编译器,函数库,操作系统,头文件等
    - tarball是包含源代码,configure,说明文件的压缩安装文件
    - 
4. $ gcc [-coO wall] file1.c file2.c ... 编译链接
    - -c 进行编译输出file.out 不能执行目标文件 (默认输出a.out可执行文件)
    - -o newfile将多个编译好的目标文件链接在一起为newfile可执行文件
    - -O 优化编译时的速度
    - -Wall 编译时提示信息
    - -l 加入动态链接库 比如 -lm 加入libm函数库
    - -L path1 -L path2 ... 限定加入动态链接库的文件目录
    - -I/path 限定include文件目录
    