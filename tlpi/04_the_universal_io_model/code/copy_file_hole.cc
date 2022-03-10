#include "tlpi_hdr.h"
#include <fcntl.h>
#include <memory>

/**
 *  考虑文件空洞的拷贝
 *  参考手册 lseek(2): SEEK_HOLE, SEEK_DATA
 */
int main(int argc, char *argv[]) {

  if (argc < 3 || strcmp(argv[1], "--help") == 0) {
    usageErr("%s <path_to_file> <path_to_copy>", argv[0]);
  }

  const mode_t mode = S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP;
  int read_fd = open(argv[1], O_RDONLY, mode);
  if (read_fd == -1) {
    errExit("open(): file to read");
  }

  int write_fd = open(argv[2],O_WRONLY | O_CREAT, mode);
  if (write_fd == -1) {
    errExit("open(): file to write");
  }

  const int BUF_SIZE = 1024;
  std::unique_ptr<char []> buf(new char[BUF_SIZE]);
  off_t pos_data, pos_hole = 0;

  while (-1 != (pos_data = lseek(read_fd, pos_hole, SEEK_DATA))) {
    bool end = false;
    // 如果 pos_hole 到了文件末尾, 则设定 pos_hole 指向文件末尾
    if (-1 == (pos_hole = lseek(read_fd, pos_data, SEEK_HOLE))) {
      pos_hole = lseek(read_fd, 0, SEEK_END);
      end = true;
    }
    // 移动 read_fd 和 write_fd 的偏移量
    if (-1 == lseek(read_fd, pos_data, SEEK_SET)) {
      errExit("lseek(): read_fd move");
    }
    if (-1 == lseek(write_fd, pos_data, SEEK_SET)) {
      errExit("lseek(): write_fd move");
    }

    // 计算拷贝 buf 的次数和剩余的数量
    auto len = pos_hole - pos_data;
    auto allowance= len % BUF_SIZE;
    // 拷贝
    for (int i = 0; i < len / BUF_SIZE; ++i) {
      if (-1 == read(read_fd, buf.get(), BUF_SIZE)) {
        errExit("read()");
      }
      if (BUF_SIZE != write(write_fd, buf.get(), BUF_SIZE)) {
        errExit("write(): fail or partial write");
      }
    }
    if (allowance) {
      if (-1 == read(read_fd, buf.get(), allowance)) {
        errExit("read()");
      }
      if (allowance != write(write_fd, buf.get(), allowance)) {
        errExit("write(): fail or partial write");
      }
    }
    // 如果 hole 到了末尾, 则退出
    if (end) {
      break;
    }
  }
  if (-1 == close(read_fd)) {
    errExit("close(): read_fd");
  }
  if (-1 == close(write_fd)) {
    errExit("close(): write_fd");
  }
  exit(EXIT_SUCCESS);
}