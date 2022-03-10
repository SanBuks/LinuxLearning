#include "tlpi_hdr.h"

#include <sys/stat.h>
#include <fcntl.h>

const int BUF_SIZE = 1024;

int main (int argc, char *argv[]) {
  // 过滤不符合规范的调用参数
  if (argc != 3 || strcmp(argv[1], "--help") == 0) {
    usageErr("%s path_to_file path_to_new_file\n", argv[0]);
  }

  // 通过 只读方式打开 文件
  int input_fd = open(argv[1], O_RDONLY);
  if(input_fd == -1) {
    errExit("open(): file %s", argv[1]);
  }

  // 规定打开方式 和 权限
  int open_flags = O_CREAT | O_WRONLY | O_TRUNC;
  // 文件权限
  mode_t file_perms =  S_IRUSR | S_IWUSR | S_IRGRP |
                       S_IWGRP | S_IROTH | S_IWOTH ;
  // 通过 只读方式打开 文件
  int output_fd = open(argv[2], open_flags, file_perms);
  if (output_fd == -1) {
    errExit("open(): file %s", argv[2]);
  }

  // 缓冲区
  char buf[BUF_SIZE];
  // 读取字节数
  ssize_t num_read;
  // 读取文件 并 写入
  while ((num_read = read(input_fd, buf, BUF_SIZE)) > 0) {
    if (write(output_fd, buf, num_read) != num_read) {
      fatal("write(): error or partial write");
    }
  }
  if (num_read == -1) {
    errExit("read()");
  }
  if (close(input_fd) == -1) {
    errExit("close(): input");
  }
  if (close(output_fd) == -1) {
    errExit("close(): output");
  }
  exit(EXIT_SUCCESS);
}
