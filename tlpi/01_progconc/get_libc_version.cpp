#include <gnu/libc-version.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

int main() {
  std::cout << "获取版本号方法 : \n";
  std::cout << "静态编译版本号 : " << __GLIBC__ << "." << __GLIBC_MINOR__ << "\n";
  std::cout << "动态获取版本号 : " << gnu_get_libc_version() << "\n";

  char *pathbuf = nullptr;
  size_t n;
  n = confstr(_CS_PATH, nullptr, (size_t) 0);
  if (n) {
    std::cout << "byte count : " << n << "\n";
    pathbuf = (char *) malloc(n + 10);
    if (!pathbuf) {
      abort();
    }
    // confstr(_CS_GNU_LIBC_VERSION, pathbuf, n + 10);
    confstr(_CS_GNU_LIBPTHREAD_VERSION, pathbuf, n + 10);
    // confstr(_CS_PATH, pathbuf, n);
    std::cout << "confstr 测试 : " << pathbuf;
  } else {
    std::cout << "confstr 测试 : " << "失败";
  }

  free(pathbuf);
  return 0;
}


