# 2. 基本概念
## 2.1 内核
### 计算机系统
- 广义 : 管理和分配计算机硬件资源的核心层软件 (内核) 及 附带所有标准软件工具如 gcc, make,  bash, vim 等
- 狭义 : 管理和分配计算机硬件资源的核心层软件 (内核)
- 内核 : 接管进程的调度与通信, 虚拟内存与物理内存的映射, 与IO的交互, 是所有进程的运行中枢 

### 职责
- 进程调度,创建和中止
- 内存管理,虚拟内存, 内存隔离
- 系统调用接口
- 文件管理, IO管理, 联网

### 内核态和用户态
- CPU 执行状态分有内核态和用户态两种, 可以通过硬件指令进行切换, 对应的虚拟内存空间也分为用户空间和内核空间
- 用户态 : 可以访问用户空间, 不可访问内核空间
- 内核态 : 可以访问用户空间, 可以访问内核空间
> 个人理解 : 内核态和用户态的存在, 在硬件角度上保证了操作系统运行的一定安全性

## 2.2 其他特性
### 用户
- 用户名 - UID - /etc/passwd
- 组名 - GID - /etc/group
```bash
# /etc/passwd 维护用户信息
root:x:0:0:root:/root:/bin/bash
#用户名:密码:UID:GID:描述信息:主目录:默认shell 
#超级用户 ID 为 0

# /etc/group 维护组信息
root:x:0:
#组名:密码:GID:用户列表
```
 


# 3. 系统编程概念
## 3.1 系统调用
- 定义 : 受控内核入口, 进程可以请求内核以自己名义通过API形式执行某些动作 
- 铁律 : 执行系统调用 或 库函数 必须检查返回值
- 特点 : 
3. 系统调用特点 : 用户态 -> 核心态, 组成固定, 有系统调用标识(唯一数字), 可传额外参数
4. 系统调用过程(x86-32) : 
    - 调用 C语言 外壳函数 : 
       - 确保系统调用参数有效
       - 将参数复制到寄存器
       - 将系统调用编号复制到 %eax 中
       - 执行中断机器指令(int 0x80), 处理器切换为核心态, 执行系统中断代码 (0x80地址所指)
    - 内核响应中断, 调用 system_call 例程(.S) :
       - 在内核栈中保存寄存器值, 审核系统调用编号的有效性 
       - 内核变量 sys_call_table 中找到对应调用服务例程, 检测参数有效性
       - 执行调用服务例程(.c), 返回结果状态给 system_call
       - 在内核栈中回复寄存器值, 将返回值置于栈中
    - 返回到外壳函数, 进入用户态, 若出错设置全局变量 errno, 外壳函数返回整数值
5. sysenter 指令替换 int0x80, 系统调用存在开销
6. 例程出错, 对 errno 取反, 返回负值, 外壳函数再对返回值取反, 拷贝到 errno, 返回负数
```bash
$ ldd copy
#    linux-vdso.so.1 =>  (0x00007fff79ff2000)
#    libtlpi_header.so => /home/LinuxLearning/build/lib/libtlpi_header.so (0x00007ff3e1dce000)
#    libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007ff3e1ac6000)
#    libm.so.6 => /lib64/libm.so.6 (0x00007ff3e17c4000)
#    libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007ff3e15ae000)
#    libc.so.6 => /lib64/libc.so.6 (0x00007ff3e11e0000)
#    /lib64/ld-linux-x86-64.so.2 (0x00007ff3e1fd3000)
$ /lib64/lib.so.6 
#    GNU C Library (GNU libc) stable release version 2.17, by Roland McGrath et al.
#    Copyright (C) 2012 Free Software Foundation, Inc.
#    This is free software; see the source for copying conditions.
#    There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
#    PARTICULAR PURPOSE.
#    Compiled by GNU CC version 4.8.5 20150623 (Red Hat 4.8.5-44).
#    Compiled on a Linux 3.10.0 system on 2021-04-28.
#    Available extensions:
#            The C stubs add-on version 2.1.2.
#            crypt add-on version 2.1 by Michael Glad and others
#            GNU Libidn by Simon Josefsson
#            Native POSIX Threads Library by Ulrich Drepper et al
#            BIND-8.2.3-T5B
#            RT using linux kernel aio
#    libc ABIs: UNIQUE IFUNC
#    For bug reporting instructions, please see:
#    <http://www.gnu.org/software/libc/bugs.html>.
```
7. 
     
     