#include "tlpi_hdr.h"

#include <sys/stat.h>
#include <fcntl.h>

const int BUF_SIZE = 5000;

void PrintFileSize(struct stat &st, const char *file_name) {
  printf("%s size is %lld bytes\n", file_name, st.st_size);
  printf("%s uses %lld blocks\n", file_name, st.st_blocks);
  printf("per %lld bytes per block\n", st.st_blksize);
}

int main() {

  char buf[BUF_SIZE];
  const char *file = "t_truncate_file";
  int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    errExit("open()");
  }
  for (int i = 0; i < BUF_SIZE; ++i) {
    buf[i] = static_cast<char>(i % 128);
  }
  size_t num_write = write(fd, buf, BUF_SIZE);
  if (num_write == -1 || num_write < BUF_SIZE) {
    close(fd);
    errExit("write() or partially write");
  }
  if (close(fd) == -1) {
    errExit("close()");
  }

  struct stat my_stat{};
  if (-1 == stat(file, &my_stat)) {
    errExit("stat()");
  }
  PrintFileSize(my_stat, file);

  // ftruncate(int fd, off_t length) 同作用
  if (truncate(file, 10) == -1) {
    errExit("truncate()");
  }
  if (-1 == stat(file, &my_stat)) {
    errExit("stat()");
  }
  PrintFileSize(my_stat, file);

  if (truncate(file, 10000) == -1) {
    errExit("truncate()");
  }
  if (-1 == stat(file, &my_stat)) {
    errExit("stat()");
  }
  PrintFileSize(my_stat, file);

  return 0;
}
