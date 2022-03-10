#include "tlpi_hdr.h"

#include <fcntl.h>
#include <sys/uio.h>
#include <climits>

const int STR_SIZE = 2;

// 1) 通过 vim 修改二进制文件
// $ vim -b datafile
// 所有行(%) 用本地(!) xxd 十六进制打开
// :%!xxd -g 1 表示每1个字节为1组
// :%!xxd -g 2 表示每2个字节为1组(默认)
// :%!xxd -r 将vim恢复成原来的显示

// 2) 读入文件 t_readv_file, 默认小端
// 0000000: 6300 0000 2000 0000 4000 0000 6465

// 3) Data 的对齐标志是 4 字节
//    复杂结构体以最大基础类型为准
struct Data{
  char a;
  int b;
};

int main(int argc, char *argv[]) {

  // 打印最大 iov 数量
  printf("max number of iov is %lld", IOV_MAX);

  if (argc != 2 || strcmp(argv[1], "--help") == 0) {
    usageErr("%s file\n", argv[0]);
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    errExit("open()");
  }

  int x;
  Data data{};
  char str[STR_SIZE];

//Structure for scatter/gather I/O.
//struct iovec
//{
//  void *iov_base;	/* Pointer to data. */
//  size_t iov_len;	/* Length of data.  */
//};
  struct iovec iov[3];
  // 计算总字节大小
  size_t sum_bytes = 0;

  iov[0].iov_base = &data;
  iov[0].iov_len = sizeof(data);
  printf("size of data is : %d\n", sizeof(data));
  sum_bytes += iov[0].iov_len;

  iov[1].iov_base = &x;
  iov[1].iov_len = sizeof(x);
  sum_bytes += iov[1].iov_len;

  iov[2].iov_base = str;
  iov[2].iov_len = STR_SIZE;
  sum_bytes += iov[2].iov_len;

  // 获取读入总数
  size_t sum_read = readv(fd, iov, 3);
  if (sum_read == 1) {
    errExit("readv()");
  }

  if (sum_read < sum_bytes) {
    printf("读入字节 %lld 数小于预期 %lld\n", sum_read, sum_bytes);
  } else {
    printf("读入字节 %lld 数等于预期 %lld\n", sum_read, sum_bytes);
  }

  printf("{%c, %d}\n", data.a, data.b);
  printf("{%d}\n", x);
  printf("{%c, %c}\n", str[0], str[1]);

  if (-1 == close(fd)) {
    errExit("close()");
  }

  fd = open("t_writev_file", O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    errExit("open()");
  }
  // writev 同 readv
  size_t sum_write = writev(fd, iov, 3);
  if (sum_write < sum_bytes) {
    printf("写入字节 %lld 数小于预期 %lld\n", sum_write, sum_bytes);
  } else {
    printf("写入字节 %lld 数等于预期 %lld\n", sum_write, sum_bytes);
  }
  if (-1 == close(fd)) {
    errExit("close()");
  }

  exit(EXIT_SUCCESS);
}


