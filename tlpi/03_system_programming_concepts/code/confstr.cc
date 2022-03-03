#include <iostream>
#include <cstdlib>
#include <memory>
#include <cerrno>
#include <unistd.h>

// <unistd.h>, 配置名称定义在其中
// size_t confstr(int name, char *buf, size_t len);
// ---------------------------------------------------------------------
// The original need for this function was to provide a way of
// finding the configuration-defined default value for the
// environment variable PATH.
// ---------------------------------------------------------------------
// name : 配置名称
// buf  : 写入 buf 的指针
// len  : len - 1 bytes + null-terminate
// ---------------------------------------------------------------------
// len =  0, buf =  nullptr  返回一个整数值代表长度(包括 null-terminate 在内)
// len != 0, buf != nullptr  将值存储在 buf 位置
// len =  0, buf != nullptr  UB
// len != 0, buf =  nullptr  UB
// ---------------------------------------------------------------------
// return 0: 1) name 合法: 若配置内容值为空, errno 不变
//           2) name 非法: errno == EINVAL

static void TestConfStr(int conf_value, const char *conf_name) {
  // 分配 buf
  std::unique_ptr<char []> buf;
  // 记录 errno
  auto old_errno = errno;
  // 清空 errno
  errno = 0;
  // 获取 buf 长度
  std::size_t num_bytes = confstr(conf_value, nullptr, 0);

  if (num_bytes) {  // 合法的配置名, 且值不为空
    char *p_temp = new char[num_bytes];
    buf.reset(p_temp);
    if (confstr(conf_value, buf.get(), num_bytes) != num_bytes) {
      std::abort();
    }
    std::cout << "[" << conf_name << "(" << num_bytes << ")" << "]: "
              << buf.get() << "\n";
    // 恢复 errno
    errno = old_errno;
  } else if (errno == EINVAL) {  // 非法配置名称
    std::cout << "[" << conf_name << "(0)"
              << "]: configuration name is invalid\n";
    // 不用恢复 errno
  } else {  // 合法配置名称, 值为空
    std::cout << "[" << conf_name << "(0)"
              << "]: configuration name is unset\n";
    // 恢复 errno
    errno = old_errno;
  }
}

int main() {
  // PATH 环境变量
  TestConfStr(_CS_PATH, "_CS_PATH");
  // glibc 版本号
  TestConfStr(_CS_GNU_LIBC_VERSION, "_CS_GNU_LIBC_VERSION");
  // 模拟非法的配置名称
  constexpr const int kNonsense = 199;
  TestConfStr(kNonsense, "kNonsense");

  // <unistd.h> 中定义的 POSIX 配置名称
  TestConfStr(_CS_V7_ENV, "_CS_V7_ENV");
  TestConfStr(_CS_POSIX_V7_ILP32_OFF32_CFLAGS, "_CS_POSIX_V7_ILP32_OFF32_CFLAGS");
  TestConfStr(_CS_POSIX_V7_ILP32_OFF32_LDFLAGS, "_CS_POSIX_V7_ILP32_OFF32_LDFLAGS");
  TestConfStr(_CS_POSIX_V7_ILP32_OFF32_LIBS, "_CS_POSIX_V7_ILP32_OFF32_LIBS");
  TestConfStr(_CS_POSIX_V7_ILP32_OFFBIG_CFLAGS, "_CS_POSIX_V7_ILP32_OFFBIG_CFLAGS");
  TestConfStr(_CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS, "_CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS");
  TestConfStr(_CS_POSIX_V7_ILP32_OFFBIG_LIBS, "_CS_POSIX_V7_ILP32_OFFBIG_LIBS");
  TestConfStr(_CS_POSIX_V7_LP64_OFF64_CFLAGS, "_CS_POSIX_V7_LP64_OFF64_CFLAGS");
  TestConfStr(_CS_POSIX_V7_LP64_OFF64_LDFLAGS, "_CS_POSIX_V7_LP64_OFF64_LDFLAGS");
  TestConfStr(_CS_POSIX_V7_LP64_OFF64_LIBS, "_CS_POSIX_V7_LP64_OFF64_LIBS");
  TestConfStr(_CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS, "_CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS");
  TestConfStr(_CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS, "_CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS");
  TestConfStr(_CS_POSIX_V7_LPBIG_OFFBIG_LIBS, "_CS_POSIX_V7_LPBIG_OFFBIG_LIBS");
//  TestConfStr(_CS_POSIX_V7_THREADS_CFLAGS, "_CS_POSIX_V7_THREADS_CFLAGS");
//  TestConfStr(_CS_POSIX_V7_THREADS_LDFLAGS, "_CS_POSIX_V7_THREADS_LDFLAGS");
  TestConfStr(_CS_POSIX_V7_WIDTH_RESTRICTED_ENVS, "_CS_POSIX_V7_WIDTH_RESTRICTED_ENVS");
  TestConfStr(_CS_V7_ENV, "_CS_V7_ENV");
  TestConfStr(_CS_POSIX_V6_ILP32_OFF32_CFLAGS, "_CS_POSIX_V6_ILP32_OFF32_CFLAGS");
  TestConfStr(_CS_POSIX_V6_ILP32_OFF32_LDFLAGS, "_CS_POSIX_V6_ILP32_OFF32_LDFLAGS");
  TestConfStr(_CS_POSIX_V6_ILP32_OFF32_LIBS, "_CS_POSIX_V6_ILP32_OFF32_LIBS");
  TestConfStr(_CS_POSIX_V6_ILP32_OFFBIG_CFLAGS, "_CS_POSIX_V6_ILP32_OFFBIG_CFLAGS");
  TestConfStr(_CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS, "_CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS");
  TestConfStr(_CS_POSIX_V6_ILP32_OFFBIG_LIBS, "_CS_POSIX_V6_ILP32_OFFBIG_LIBS");
  TestConfStr(_CS_POSIX_V6_LP64_OFF64_CFLAGS, "_CS_POSIX_V6_LP64_OFF64_CFLAGS");
  TestConfStr(_CS_POSIX_V6_LP64_OFF64_LDFLAGS, "_CS_POSIX_V6_LP64_OFF64_LDFLAGS");
  TestConfStr(_CS_POSIX_V6_LP64_OFF64_LIBS, "_CS_POSIX_V6_LP64_OFF64_LIBS");
  TestConfStr(_CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS, "_CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS");
  TestConfStr(_CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS, "_CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS");
  TestConfStr(_CS_POSIX_V6_LPBIG_OFFBIG_LIBS, "_CS_POSIX_V6_LPBIG_OFFBIG_LIBS");
  TestConfStr(_CS_POSIX_V6_WIDTH_RESTRICTED_ENVS, "_CS_POSIX_V6_WIDTH_RESTRICTED_ENVS");
  TestConfStr(_CS_V6_ENV, "_CS_V6_ENV");
  return 0;
}
