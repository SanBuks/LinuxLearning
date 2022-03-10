/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 5-1 */
/* bad_exclusive_open.c
   这个命令显示了为什么要使用 open() 的 O_EXCL 标志 */

#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

// 调用命令 ./bad_exclusive_open test sleep & ./bad_exclusive_open test
// 注意是 & 而非 &&

int main(int argc, char *argv[]) {
  if (argc < 2 || strcmp(argv[1], "--help") == 0) {
    usageErr("%s file\n", argv[0]);
  }

  // 确定文件不存在
  int fd = open(argv[1], O_WRONLY);
  if (fd != -1) {
    printf("[PID %lld]: 文件 \"%s\" 已存在\n", (long long)getpid(), argv[1]);
    if (-1 == close(fd)) {
      errExit("close()");
    }
  }
  // 确定是不存在文件的错误
  if (errno != ENOENT) {
    errExit("open()");
  }
  printf("[PID %lld]: 文件 \"%s\" 还不存在\n", (long long)getpid(), argv[1]);
  if (argc > 2) {
    sleep(5);
    printf("[PID %lld]: 停止休眠\n", (long long)getpid());
  }
  // 这里未必是独占方式打开文件
  fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR );
  if (fd == -1) {
    errExit("open()");
  }
  printf("[PID %lld]: 独占方式创建文件 \"%s\"\n", (long long)getpid(), argv[1]);
  if (close(fd) == -1) {
    errExit("close()");
  }
  exit(EXIT_SUCCESS);
}
