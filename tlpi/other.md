# 标准






# 编译选项解释

- 参考 `https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html`

- cc 
- -std=c99 
- -D_XOPEN_SOURCE=600 
```text
it tells your compiler to include definitions for some extra functions that are defined in the X/Open and POSIX standards.
```
- -D_DEFAULT_SOURCE 
```text
If you define this macro, most features are included apart from X/Open, LFS and GNU extensions: the effect is to enable features from the 2008 edition of POSIX, as well as certain BSD and SVID features without a separate feature test macro to control them.

Be aware that compiler options also affect included features:

If you use a strict conformance option, features beyond those from the compiler’s language version will be disabled, though feature test macros may be used to enable them.
Features enabled by compiler options are not overridden by feature test macros. 
```
- -g 开启 GDB 的 debug 功能
- -Idir
```text
在 搜索头文件目录表中 增加以 -I 标识的目录, 这些目录较标准目录表会优先搜索, 如果本身存在在内则会被忽略, 以此来保证默认搜索顺序和对于系统头文件文件特殊操作有效. 如果dir 以 = 开头则会被 sysroot prefix替换.
```
- `-llibrary`
  `-l library `
```text
gcc 4.8.5 manul
查找一个叫做 library 的库(第二种方法只适用于POSIX标准且不推荐).

命令中库文件和目标文件链接顺序有区别 : 他们遵循命令中出现的顺序, 比如 foo.o -lz bar.o, 链接器会在链接foo.o 后且在 bar.o 前去寻找 库z ( 如果 bar.o 使用了在 z 中的函数则不会被加载 ).

链接器会在一个标准目录表中寻找实际名为 liblibrary.a 的文件, 这个标准目录表中含有几个标准系统目录和任何你自己定义的 -Ldirs.

正常情况下, liblibrary.a 文件为静态库文件, 它由众多的目标文件组成. 链接器会扫描其中所有已声明且被引用但未定义的标识符. 如果发现最终找的文件就是一个普普通通的目标文件则就像往常一样链接, 所以 -l 和 bar.o 的区别仅仅是 -l 会去在几个目录下查找 *.a 文件.
```

- -pedantic 开启 ISO 对于警告的要求, 禁止使用 被禁止的拓展
- -Wall 开启 对于会被部分用户质疑语言使用 的警告
- -W 开启所有警告信息
- -Wmissing-prototypes (C) 限制全局函数必须在头文件有原型声明
- -Wno-sign-compare 不提示有符号数和无符号数的比较警告
- -Wimplicit-fallthrough 提示 switch 语句 fallthrough
- -Wno-unused-parameter 不提示未使用的函数参数警告
- -c 
```text
1. 编译或汇编文件为目标文件, 但是没有链接
2. 将 ‘.c’, ‘.i’, ‘.s’ 等后缀替换为 ‘.o’, 忽略无法识别的文件
```
- -o print_rlimit.o 
```text
生成最终输文件为file, 应用于目标文件, 汇编文件或被预编译的文件, 如果 file 未指定则默认生成 a.out, source.o, source.s, source.suffix.gch(预编译的头文件), file.i
```

# 预装软件
- libcap-devel
- 