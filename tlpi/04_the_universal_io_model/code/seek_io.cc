#include "tlpi_hdr.h"

#include <memory>
#include <fcntl.h>
#include <cctype>

/**
  * 用法: seek_io file {r<length>|R<length>|w<string>|s<offset>}...
  * 作用: 打开文件, 根据选项进行如下操作:
  *      r<length>: 在当前位置读 'length' bytes 并显示
  *      R<length>: 在当前位置读 'length' bytes 并以 16 进制显示
  *      w<string>: 在当前位置写 'string'
  *      s<offset>: 将当前文件位置移动到 'offset' 处
  * 举例: seek_io myfile wxyz s1 r2
  */

const mode_t MODE = S_IRUSR | S_IWUSR |
                    S_IRGRP | S_IWGRP |
                    S_IROTH | S_IWOTH;
const int FLAG = O_RDWR | O_CREAT;

int main(int argc, char *argv[]) {

  if (argc < 3 || strcmp(argv[1], "--help") == 0) {
    usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n", argv[0]);
  }
  int fd = open(argv[1], FLAG, MODE);
  if (fd == -1) {
    errExit("open");
  }

  size_t len;  // length
  std::unique_ptr<char []> buf;   // 缓冲区
  ssize_t num_read, num_written;
  for (int ap = 2; ap < argc; ++ap) {
    switch(argv[ap][0]) {
      case 'r':
      case 'R': {
        len = getLong(&argv[ap][1], GN_ANY_BASE, &argv[ap][1]);
        auto temp = new char[len];
        buf.reset(temp);
        num_read = read(fd, buf.get(), len);
        if (num_read == -1) {
          errExit("read");
        }
        if (num_read == 0) {
          printf("%s: end-of-file\n", argv[ap]);
        } else {
          printf("%s: ", argv[ap]);
          for (int j = 0; j < num_read; ++j) {
            if (argv[ap][0] == 'r') {
              printf("%c", isprint((unsigned char)(buf[j])) ? buf[j] : '?');
            } else {
              printf("%02x ", buf[j]);
            }
          }
          printf("\n");
        }
        break;
      }
      case 'w': {
        auto len = strlen(&argv[ap][1]);
        num_written = write(fd, &argv[ap][1], len);
        if (num_written == -1) {
          errExit("write");
        }
        if (num_written < len) {
          errExit("partial write");
        }
        printf("%s: wrote %lld bytes\n", &argv[ap][1], num_written);
//      printf("%s: wrote %zd bytes\n", &argv[ap][1], num_written);
        break;
      }
      case 's': {
        off_t offset = getLong(&argv[ap][1], GN_ANY_BASE, &argv[ap][1]);
        if (lseek(fd, offset, SEEK_CUR) == -1) {
          errExit("lseek");
        }
        printf("%s: seek succeeded\n", argv[ap]);
        break;
      }
      default:
        cmdLineErr("Arguments must start with [rRws]: %s\n", argv[ap]);
    }
  }
  if (close(fd) == -1) {
    errExit("close()");
  }
  exit(EXIT_SUCCESS);
}