/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU Lesser General Public License as published   *
* by the Free Software Foundation, either version 3 or (at your option)   *
* any later version. This program is distributed without any warranty.    *
* See the files COPYING.lgpl-v3 and COPYING.gpl-v3 for details.           *
\*************************************************************************/

/* Listing 3-5 */
/* get_num.h */

#ifndef GET_NUM_H
#define GET_NUM_H

#define GN_NONNEG     01    // 非负数
#define GN_GT_0       02    // 正数

// 整数默认是十进制
#define GN_ANY_BASE   0100  // 任意基数
#define GN_BASE_8     0200  // 基数为 8
#define GN_BASE_16    0400  // 基数为 16

long getLong(const char *arg, int flags, const char *name);
int getInt(const char *arg, int flags, const char *name);

#endif