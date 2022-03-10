/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU Lesser General Public License as published   *
* by the Free Software Foundation, either version 3 or (at your option)   *
* any later version. This program is distributed without any warranty.    *
* See the files COPYING.lgpl-v3 and COPYING.gpl-v3 for details.           *
\*************************************************************************/

/* Listing 3-2 */
/* error_functions.h */

#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

// NORETURN 替换为 C++11 引入的 [[noreturn]] 属性

[[noreturn]]
void errMsg(const char *format, ...);

[[noreturn]]
void errExit(const char *format, ...);

[[noreturn]]
void err_exit(const char *format, ...);

[[noreturn]]
void errExitEN(int errnum, const char *format, ...);

[[noreturn]]
void fatal(const char *format, ...);

[[noreturn]]
void usageErr(const char *format, ...);

[[noreturn]]
void cmdLineErr(const char *format, ...);

#endif
