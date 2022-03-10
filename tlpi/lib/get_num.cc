/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU Lesser General Public License as published   *
* by the Free Software Foundation, either version 3 or (at your option)   *
* any later version. This program is distributed without any warranty.    *
* See the files COPYING.lgpl-v3 and COPYING.gpl-v3 for details.           *
\*************************************************************************/

/* Listing 3-6 */
/* get_num.c
   处理命令行中数字的函数 */

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cerrno>

#include "get_num.h"

/**
 * 打印错误信息 包含以下信息
 * @param fname 函数名称, 不为空
 * @param msg   错误信息
 * @param arg   命令参数值
 * @param name  参数字符串
 */
static void gnFail(const char *fname, const char *msg,
                   const char *arg, const char *name) {
  fprintf(stderr, "%s error", fname);
  if (name != nullptr && *name != '\0') {
    fprintf(stderr, " (in %s)", name);
  }
  fprintf(stderr, ": %s\n", msg);
  if (arg != nullptr && *arg != '\0') {
    fprintf(stderr, "        offending text: %s\n", arg);
  }
  exit(EXIT_FAILURE);
}

/**
 * 将命令行参数值转换为 long
 * @param fname 函数名称
 * @param arg   参数值
 * @param flags 控制符, 控制转换基和转换条件
 * @param name  参数字符串
 * @return 返回转换的数值
 */
static long getNum(const char *fname, const char *arg,
                   int flags, const char *name) {
  long res;
  char *endptr;
  int base;

  if (arg == nullptr || *arg == '\0') {
    gnFail(fname, "null or empty string", arg, name);
  }
  base = (flags & GN_ANY_BASE) ? 0 :      // base = 0 表示自动转换
         (flags & GN_BASE_8) ? 8 :        // base = 8 表示八进制
         (flags & GN_BASE_16) ? 16 : 10;  // base = 16 表示十六进制
  errno = 0;
  res = strtol(arg, &endptr, base);
  if (errno != 0) {
    gnFail(fname, "strtol() failed", arg, name);
  }
  if (*endptr != '\0') {                  // 没有全部转换
    gnFail(fname, "nonnumeric characters", arg, name);
  }
  if ((flags & GN_NONNEG) && res < 0) {   // 必须是非负数
    gnFail(fname, "negative value not allowed", arg, name);
  }
  if ((flags & GN_GT_0) && res <= 0) {    //  必须是正数
    gnFail(fname, "value must be > 0", arg, name);
  }
  return res;
}

/**
 * 转换参数值为 long
 * @param arg   参数值
 * @param flags 控制符, 控制转换基和转换条件
 * @param name  参数字符串
 * @return 返回 long 类型
 */
long getLong(const char *arg, int flags, const char *name) {
  return getNum("getLong", arg, flags, name);
}

/**
 * 转换参数值为 int
 * @param arg   参数值
 * @param flags 控制符, 控制转换基和转换条件
 * @param name  参数字符串
 * @return 返回 int 类型
 */
int getInt(const char *arg, int flags, const char *name) {
  long res;
  res = getNum("getInt", arg, flags, name);
  if (res > INT_MAX || res < INT_MIN) {
    gnFail("getInt", "integer out of range", arg, name);
  }
  return (int) res;
}
