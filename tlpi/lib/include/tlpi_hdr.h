/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU Lesser General Public License as published   *
* by the Free Software Foundation, either version 3 or (at your option)   *
* any later version. This program is distributed without any warranty.    *
* See the files COPYING.lgpl-v3 and COPYING.gpl-v3 for details.           *
\*************************************************************************/

/* Listing 3-1 */
/* tlpi_hdr.h
   Standard header file used by nearly all of our example programs. */

#ifndef TLPI_HDR_H
#define TLPI_HDR_H

#include <sys/types.h>        /* 包含系统数据类型 */
#include <cstdio>             /* 包含常用 IO 函数 */
#include <cstdlib>            /* 包含常用库函数和一些常量如 EXIT_SUCCESS, EXIT_FAILURE */
#include <unistd.h>           /* 包含多个系统调用原型 */
#include <cerrno>             /* 包含 errno 和多个 errno 常量 */
#include <cstring>            /* 包含常用字符串函数 */
#include <cstdbool>           /* 包含 'bool' 类型和 'true', 'false' 常量 */

#include "get_num.h"          /* 自定义定义处理数字型参数的函数 */
#include "error_functions.h"  /* 自定义错误处理函数 */

/* 一些 UNIX 实现定义了 FALSE 和 TRUE 宏, 这里需要 undefine them */
#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

/* 一些系统没有定义 'socklen_t' */
#if defined(__sgi)
typedef int socklen_t;
#endif

/* 一些系统需要通过其他头文件包含 FASYNC */
#if defined(__sun)
#include <sys/file.h>
#endif

/* 一些系统定义了 FASYNC 而非 O_ASYNC */
#if ! defined(O_ASYNC) && defined(FASYNC)
#define O_ASYNC FASYNC
#endif

/* BSD 系统使用 MAP_ANON, 而非 MAP_ANONYMOUS */
#if defined(MAP_ANON) && ! defined(MAP_ANONYMOUS)
#define MAP_ANONYMOUS MAP_ANON
#endif

/* 一些系统定义了 O_FSYNC 而非 O_SYNC */
#if ! defined(O_SYNC) && defined(O_FSYNC)
#define O_SYNC O_FSYNC
#endif

/* FreeBSD 系统使用以下名称作为 sigval 结构体中的字段名 */
#if defined(__FreeBSD__)
#define sival_int sigval_int
#define sival_ptr sigval_ptr
#endif

#endif