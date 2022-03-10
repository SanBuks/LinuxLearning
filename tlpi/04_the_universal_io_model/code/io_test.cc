#include "tlpi_hdr.h"
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h>

int main() {
  const int BuffSize = 1000;
  char buff[BuffSize + 1] = "1234";
  int fd = open("io_test_file", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    fatal("open()");
  }
  ssize_t num_write = write(fd, buff, BuffSize + 1);
  if (num_write == -1) {
    errExit("write()");
  }
  if (num_write != BuffSize + 1) {
    errExit("write(): partial write");
  }
  if (close(fd) == -1) {
    errExit("close()")
  }
  return 0;
}