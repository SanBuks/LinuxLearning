#include "tlpi_hdr.h"

#include <fcntl.h>
#include <iostream>

int main() {
  int fd = open("t_dup_test_file", O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    errExit("open()");
  }

  if (close(STDOUT_FILENO) == -1) {
    errExit("close()");
  }

  // 1) 通过 dup 或 fcntl(F_DUPFD) 获取复制的文件描述符
//int fd1 = fcntl(fd, F_DUPFD, STDERR_FILENO);
  int fd1 = dup(fd);
  if (-1 == fd1) {
    errExit("dup()");
  }

  // 2) dup2(dup_fd, old_fd): 先将 old_fd 关闭再复制, 会忽略关闭错误,
  //                          如果失败则不会关闭 old_fd, fd 相同则不做任何事
  int fd2 = dup2(fd, STDERR_FILENO);

  // 3) dup3(fd, STDERR_FILENO, O_CLOEXEC): 同 fd2, 打开同时设置标志位
//int fd2 = dup3(fd, STDERR_FILENO, O_CLOEXEC)          // 设置 O_CLOEXEC 标志

  // 4) 同 fcntl(F_DUPFD), 打开同时设置标志位, 但是需要先关闭对应 fd 流
//int fd2 = fcntl(fd, F_DUPFD_CLOEXEC, STDERR_FILENO);  // 设置 O_CLOEXEC 标志

  if (fd2 != STDERR_FILENO) {
    errExit("dup2()");
  }

  printf("test1");
  std::cerr << "test2";

  close(fd);
  close(fd1);
  close(fd2);

  return 0;
}
