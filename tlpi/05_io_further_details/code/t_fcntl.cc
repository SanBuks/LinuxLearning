#include "tlpi_hdr.h"

#include <vector>
#include <string>
#include <algorithm>
#include <fcntl.h>

int main(int argc, char *argv[]) {

  std::vector<std::string> print_str(3, "NOT SET!");
  int fd = open("test_file",
                O_WRONLY | O_CREAT | O_EXCL | O_ASYNC,
                S_IRUSR | S_IWUSR);
  if (fd == -1) {
    errExit("open()");
  }

  // 获取文件状态和访问模式
  int flags = fcntl(fd, F_GETFL);
  if (flags == -1) {
    errExit("fcntl(F_GETFL)");
  }
  // 提取出 访问模式标志
  int access_flag = flags & O_ACCMODE;

  // 判断 访问模式
  if (access_flag & O_RDWR) {
    print_str[0] = "O_RDWR SET!";
  } else if (access_flag & O_WRONLY) {
    print_str[0] = "O_WRONLY SET!";
  } else {
    print_str[0] = "O_RDONLY SET!";
  }

  // 判断 状态标志
  if (flags & O_ASYNC) {
    print_str[1] = "O_ASYNC SET!";
  } else {
    print_str[1].insert(0, "O_ASYNC ");
  }

  if (flags & O_APPEND) {
    print_str[2] = "O_APPEND SET!";
  } else {
    print_str[2].insert(0, "O_APPEND ");
  }

  std::for_each(print_str.begin(), print_str.end(),
                [](const std::string &str) { printf("%s\n", str.c_str());});

  printf("start add O_APPEND\n");

  // 修改状态标志
  flags |= O_APPEND;
  if (fcntl(fd, F_SETFL, flags) == -1) {
    errExit("fcntl(F_SETFL)");
  }
  if (fcntl(fd, F_SETFL, flags) == -1) {
    errExit("fcntl(F_SETFL)");
  }

  flags = fcntl(fd, F_GETFL);
  if (flags == -1) {
    errExit("fcntl(F_GETFL)");
  }
  if (flags & O_APPEND) {
    printf("O_APPEND SET!");
  } else {
    printf("O_APPEND STILL NOT SET!");
  }

  if (close(fd) == -1) {
    errExit("close()");
  }
  return 0;
}
