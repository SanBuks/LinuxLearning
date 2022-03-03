/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU Lesser General Public License as published   *
* by the Free Software Foundation, either version 3 or (at your option)   *
* any later version. This program is distributed without any warranty.    *
* See the files COPYING.lgpl-v3 and COPYING.gpl-v3 for details.           *
\*************************************************************************/

/* Listing 3-3 */
/* error_functions.c
   Some standard error handling routines used by various programs.
*/

#include <cstdarg>             /* 引入可变参数 */
#include "ename.c.inc"         /* 定义 errno 常量对应的字符串数组 */
#include "error_functions.h"
#include "tlpi_hdr.h"

/**
 * 中止进程
 * 如果环境参数 EF_DUMPCORE 已定义且不为空, 则通过 abort() 函数产生 dumpcore
 * 否则判断参数 `ueseExit3` 调用不同退出函数
 * @param useExit3 true  : 使用 exit() 退出
 *                 falst : 使用 _exit() 退出
 */
static void terminate(Boolean useExit3) {
  char *s = getenv("EF_DUMPCORE");
  if (s != nullptr && *s != '\0') {
    abort();
  } else if (useExit3) {
    exit(EXIT_FAILURE);
  } else {
    _exit(EXIT_FAILURE);
  }
}

/**
 * 将 errno 名称 和 用户自定义错误字符串 按格式输出到 stderr 中
 * 其中 errno 名来自 build_ename.sh 生成出的字符串数组, 且附加上 strerror 描述字符串
 * @param useErr      是否采用 errno 对应的错误名称
 * @param err         errno 编号
 * @param flushStdout 是否刷新 stdout
 * @param format      用户自定义的输出格式
 * @param ap          用户自定义的不定参数
 */
static void outputError(Boolean useErr, int err, Boolean flushStdout,
                        const char *format, va_list ap) {
  const int BUF_SIZE = 500;
  char userMsg[BUF_SIZE], errText[BUF_SIZE], buf[BUF_SIZE];

  vsnprintf(userMsg, BUF_SIZE, format, ap);

  if (useErr) {
    snprintf(errText, BUF_SIZE, "[%s : %s]",
             (err > 0 && err <= MAX_ENAME) ? ename[err] : "?UNKNOWN?",
             strerror(err));
  } else {
    snprintf(errText, BUF_SIZE, "");
  }

  // GCC 提供 编译段落的 诊断参数
  // #pragma GCC diagnostic push
  // #pragma GCC diagnostic warning "-XXX"
  // #pragma GCC diagnostic error   "-XXX"
  // #pragma GCC diagnostic ignored "-XXX"
  // #pragma GCC diagnostic pop
  // ignore "-Wformat-truncation" 忽视截断问题
#if __GNUC__ >= 7
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-truncation"
#endif
  snprintf(buf, BUF_SIZE, "ERROR%s : %s\n", errText, userMsg);
#if __GNUC__ >= 7
#pragma GCC diagnostic pop
#endif

  if (flushStdout) {
    fflush(stdout);  // 刷新 stdout
  }
  fputs(buf, stderr);
  fflush(stderr);    // 防止 stderr 不是行缓冲 */
}

/**
 * 显示 errno 名称 和 自定义错误信息
 * @param format 用户自定义的输出格式
 * @param ...    用户自定义的不定参数
 */
void errMsg(const char *format, ...) {
  va_list argList;
  int savedErrno;
  savedErrno = errno;  // 防止改动
  va_start(argList, format);
  outputError(TRUE, errno, TRUE, format, argList);
  va_end(argList);
  errno = savedErrno;
}

/**
 * 显示 errno 名称 和 自定义错误信息, 然后通过 exit() 中止进程, 刷新 stdout
 * @param format 用户自定义的输出格式
 * @param ...    用户自定义的不定参数
 */
void errExit(const char *format, ...) {
  va_list argList;
  va_start(argList, format);
  outputError(TRUE, errno, TRUE, format, argList);
  va_end(argList);
  terminate(TRUE);
}

/**
 * 显示 errno 名称 和 自定义错误信息, 然后通过 _exit() 中止进程, 不刷新 stdout
 * _exit() 不会调用 退出 handler, exit() 会调用 exit handler
 * 特别用处: 子进程使用此函数退出时不会刷新父进程的 stdio , 不会调用父进程创建的 exit handler
 * @param format 用户自定义的输出格式
 * @param ...    用户自定义的不定参数
 */
void err_exit(const char *format, ...) {
  va_list argList;
  va_start(argList, format);
  outputError(TRUE, errno, FALSE, format, argList);
  va_end(argList);
  terminate(FALSE);
}

/**
 * 与 errExit() 类似, 提供自定义 errno
 * @param errnum 自定义的错误编号
 * @param format 用户自定义的输出格式
 * @param ...    用户自定义的不定参数
 */
void errExitEN(int errnum, const char *format, ...) {
  va_list argList;
  va_start(argList, format);
  outputError(TRUE, errnum, TRUE, format, argList);
  va_end(argList);
  terminate(TRUE);
}

/**
 * 仅仅打印用户自定义的错误信息, 调用 exit() 退出
 * @param format 用户自定义的输出格式
 * @param ...    用户自定义的不定参数
 */
void fatal(const char *format, ...) {
  va_list argList;
  va_start(argList, format);
  outputError(FALSE, 0, TRUE, format, argList);
  va_end(argList);
  terminate(TRUE);
}

/**
 * 打印命令错误使用信息, 调用 exit() 退出
 * @param format 用户自定义的输出格式
 * @param ...    用户自定义的不定参数
 */
void usageErr(const char *format, ...) {
  va_list argList;
  fflush(stdout);           // 打印 stderr 前注意刷新 stdout
  fprintf(stderr, "Usage: ");
  va_start(argList, format);
  vfprintf(stderr, format, argList);
  va_end(argList);
  fflush(stderr);           // 防止 stderr 不是行缓冲
  exit(EXIT_FAILURE);
}

/**
 * 打印命令参数错误信息, 调用 exit() 退出
 * @param format 用户自定义的输出格式
 * @param ...    用户自定义的不定参数
 */
void cmdLineErr(const char *format, ...) {
  va_list argList;
  fflush(stdout);
  fprintf(stderr, "Command-line usage error: ");
  va_start(argList, format);
  vfprintf(stderr, format, argList);
  va_end(argList);
  fflush(stderr);
  exit(EXIT_FAILURE);
}