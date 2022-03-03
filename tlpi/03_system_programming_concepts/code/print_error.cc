#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <iostream>

// #include <stdio.h>
// void perror(const char *s);
// ------------------------------------------------------------------
// #include <string.h>
// char *strerror(int errnum);
// 注意: 后续的 strerror 调用会覆盖上一次调用返回的内容
// ------------------------------------------------------------------
// POSIX.1-2001 permits strerror() to set errno if the call
// encounters an error, but does not specify what value should be
// returned as the function result in the event of an error.  On
// some systems, strerror() returns NULL if the error number is
// unknown.  On other systems, strerror() returns a string something
// like "Error nnn occurred" and sets errno to EINVAL if the error
// number is unknown.  C99 and POSIX.1-2008 require the return value
// to be non-NULL.

int main() {
  const char * const p_message = "open_for_perror";
  auto fd = open("sadf", O_RDONLY);
  if (fd == -1) {
    perror(p_message);
  }
  std::cout << strerror(errno) << "\n";
  exit(EXIT_FAILURE);
}
