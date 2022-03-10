#define _FILE_OFFSET_BITS 64

// LFS API 需要的宏
//#define _LARGEFILE64_SOURCE 64

#include "tlpi_hdr.h"

#include <fcntl.h>


int main(int argc, char *argv[]) {


  if (argc != 3 || strcmp(argv[1], "--help") == 0) {
    printf("%s pathname offset\n", argv[0]);
  }

  int fd = open(argv[1], O_RDWR | O_CREAT | O_LARGEFILE, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    errExit("open64");
  }

  off_t off = atoll(argv[2]);

  // LFS API 规定的类型
//off64_t off = atoll(argv[2]);
  // LFS API
//if (lseek64(fd, off, SEEK_SET) == -1) {

  if (lseek(fd, off, SEEK_SET) == -1) {
    errExit("lseek64()");
  }
  if (write(fd, "test", 4) == -1) {
    errExit("write");
  }

  exit(EXIT_SUCCESS);
}
