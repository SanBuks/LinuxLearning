#include <cstdlib>
#include <iostream>
#include <unistd.h>

// #include <stdlib.h>
// int atexit(void (*func)(void));
// ----------------------------------------------------
// 1. 注册函数指针, 在进程正常结束时, 按照注册的先后顺序, 逆序执行
// 2. 进程的正常结束包括 exit(), return from main(), 最后一个 线程结束
// 3. 至少含有 32 个最大可注册函数数量, 可通过 sysconf 获取最大函数数量
// 4. 确保 exit() 不会调用多次, 不要在注册函数中调用 exit()
// 5. 在退出阶段即运行注册函数时, 如果需要停止 exit() 进程则必须调用 _exit() 或 _Exit()
// ----------------------------------------------------
// 正常返回 0, 非正常返回 非 0
// ----------------------------------------------------
// ? After a successful call to any of the exec functions, any
// functions previously registered by atexit() shall no longer be
// registered.

void test1() {
  std::cout << "test1\n";
}
void test2() {
  std::cout << "test2\n";
}
void test3() {
  std::cout << "test3\n";
}

int main() {
  if (atexit(test1)) abort();
  if (atexit(test2)) abort();
  if (atexit(test3)) abort();
  errno = 0;
  auto max_number_for_atexit = sysconf(_SC_ATEXIT_MAX);
  if (!errno) {
    std::cout << max_number_for_atexit<< "\n";
  }
  return 0;
}
