#include <fcntl.h>
#include "tlpi_hdr.h"

void errMsgTest() {
  auto fd = open("xxxx", O_RDONLY);
  if (fd == -1) {
    errMsg("%s", "错误信息");
  } else {
    close(fd);
  }
}

void errExitTest() {
  auto fd = open("xxxx", O_RDONLY);
  if (fd == -1) {
    errExit("%s", "错误信息");
  } else {
    close(fd);
  }
}

void err_exitTest() {
  auto fd = open("xxxx", O_RDONLY);
  if (fd == -1) {
    err_exit("%s", "错误信息");
  } else {
    close(fd);
  }
}

// void errExitEN(int errnum, const char *format, ...);
void errExitEnTest() {
  auto fd = open("xxxx", O_RDONLY);
  if (fd == -1) {
    errExitEN(23, "%s", "错误信息");
  } else {
    close(fd);
  }
}

void fatalTest() {
  fatal("%s", "错误信息");
}

void usageErrTest() {
  usageErr("%s", "错误信息");
}

void cmdLineErrTest() {
  cmdLineErr("%s", "错误信息");
}

int main() {
//  errMsgTest();
//  errExitTest();
//  err_exitTest();
//  errExitEnTest();
//  fatalTest();
//  usageErrTest();
//  cmdLineErrTest();
  return 0;
}
