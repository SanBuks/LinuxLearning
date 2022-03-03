#include <cstdarg>
#include <iostream>

void simple_printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  while (*fmt != '\0') {
    if (*fmt == 'd') {
      int i = va_arg(args, int);
      std::cout << i << '\n';
    } else if (*fmt == 'c') {
      // 注意自动转换到整数类型
      int c = va_arg(args, int);
      std::cout << static_cast<char>(c) << '\n';
    } else if (*fmt == 'f') {
      double d = va_arg(args, double);
      std::cout << d << '\n';
    }
    ++fmt;
  }
  va_end(args);
}

int main() {
  // char, short 实际提升为 int,    需要通过 va_arg(args, int)    然后强转
  // float       实际提升为 double, 需要通过 va_arg(args, double) 然后强转
  simple_printf("dcff", 3, 'a', 1.999, 42.5);
  return 0;
}
