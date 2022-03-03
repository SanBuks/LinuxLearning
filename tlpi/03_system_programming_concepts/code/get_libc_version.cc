#include <gnu/libc-version.h>
#include <iostream>

int main() {
  std::cout << "获取版本号方法\n";
  std::cout << "宏获取标准库版本号 : " << __GLIBC__ << "." << __GLIBC_MINOR__ << "\n";
  std::cout << "函数获取标准库版本号 : " << gnu_get_libc_version() << "\n";
  return 0;
}

