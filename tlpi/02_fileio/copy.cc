// 存放系统数据类型
#include <sys/stat.h>
// 存放系统文件相关函数
#include <fcntl.h>

// 基础头文件
#include "include/tlpi_hdr.h"

// 定义缓冲区大小
const int BUF_SIZE = 1024;

int main (int argc, char *argv[]) {

  // 规定系统描述符
  int input_fd, output_fd;
  // 规定打开文件的模式
  int open_flags;
  // 字节数
  ssize_t num_read;
  // 缓冲区
  char buf[BUF_SIZE];
  // 文件权限
  mode_t file_perms;

  // 过滤不符合规范的调用参数
  if (argc != 3 || strcmp(argv[1], "--help") == 0) {
    usageErr("%s old-file new-file\n", argv[0]);
  }

  // 通过 只读方式打开 文件
  input_fd = open(argv[1], O_RDONLY);
  if(input_fd == -1) {
    errExit("opening file %s", argv[1]);
  }

  // 规定打开方式 和 权限
  open_flags = O_CREAT | O_WRONLY | O_TRUNC;
  file_perms =  S_IRUSR | S_IWUSR | S_IRGRP |
      S_IWGRP | S_IROTH | S_IWOTH ;
  output_fd = open(argv[2], open_flags, file_perms);
  if (output_fd == -1) {
    errExit("opeing file %s", argv[2]);
  }

  // 读取文件 并 写入
  while ((num_read = read(input_fd, buf, BUF_SIZE)) > 0) {
    if (write(output_fd, buf, num_read) != num_read) {
      fatal("write() returned error or partial write occured");
    }
  }

  if (num_read == -1) {
    errExit("read");
  }

  if (close(input_fd) == -1) {
    errExit("close input");
  }

  if (close(output_fd) == -1) {
    errExit("close output");
  }

  exit(EXIT_SUCCESS);
}
