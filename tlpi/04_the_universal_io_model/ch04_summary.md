# 1. 综述
- 文件描述符(int): 标识所有类型的已打开文件, 各个进程内, 文件描述符自成一套
- 标准文件描述符: shell 默认打开, 程序继承, 宏定义在 <unistd.h>, 注意, freopen 会更改变量指代的对象
  - stdin:  0 / STDIN_FILENO  标准输入
  - stdout: 1 / STDOUT_FILENO 标准输出
  - stderr: 2 / STDERR_FILENO 标准错误
- 通用 IO: 要求每个文件系统和设备驱动程序都实现了相同的 I/O 系统调用集, 且所有的操作细节在内核中处理

# 2. 通用操作
## open()
```c++
// 打开文件, 返回进程中未用文件描述符中的最小值, 可以通过 close, open 方式指定描述符
int open(const char *pathname, int flags, mode_t mode);
// pathname: 如果是符号链接则解析
// flags:    指定访问方式
// mode:     指定文件权限, 且受 umask, 父目录权限影响
// return -1: 错误
// --------------------------------------------------------
// falgs 分三类: 
// 文件访问模式(不可组合, 可检索, 可修改): O_RDONLY, O_WRONLY, O_RDWR
// 文件创建标志(可组合, 不可检索, 不可修改): O_CREATE, O_TRUNC, O_EXCL, O_DIRECTORY
// 文件状态标志(可组合, 可检索, 可修改): O_APPEND
// --------------------------------------------------------
int creat(const char *pathname, mode_t mode);
// 没有更多的创建标志, 缺少相关功能, 尽量不用, 等价于
open(const char *pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
```
- `O_CREATE`: 创建文件, 即使是只读方式, 必须给定 mode, 否则为栈中随机值
- `O_TRUNC`: 清空文件内容, 长度置为 0
- `O_EXCL`: 与 `O_CREAT` 结合, 如果文件已存在则失败, 如果 pathname 是符号链接则失败, 检测文件存在与创建是原子操作

## read()
```c++
ssize_t read(int fd, void *buf, size_t count);
// buf: 缓冲区, 至少 count 个字节大
// count: 至少读取 count 个字节
// return -1: 出错
//         0: 遇到 EOF
//        ssize: 实际读取的字节个数
```
- 经常出现读取字节数小于请求字节数情况, 比如: 终端 '\n' 会结束调用
- 缓冲区注意预留 '\0' 空间

## write()
```c++
ssize_t write(int fd, const void *buf, size_t count);
// buf: 缓冲区, 至少 count 个字节大
// count: 至少写入 count 个字节
// return -1: 出错
//        ssize: 写入的字节数
```
- 会产生部分写, 磁盘满或者进程对文件大小有上限(RLIMIT_FSIZE)
- 内核会缓存磁盘 IO

## close() 
```c++
int close(int fd);
// fd: 磁盘描述符
// return -1: 出错
```
- 关闭失败会导致文件描述符资源消失殆尽

## lseek()
```c++
off_t lseek(int fd, off_t offset, int whence);
// offset: 文件偏移量, 可为负值, 默认打开的偏移量为 0
// whence: SEEK_SET 指向 0, 此时 offset 必须 >= 0
//         SEEK_CUR 指向 当前
//         SEEK_END 指向 N
```
- 只调整内核中与文件描述符相关的文件偏移量记录, 不引起设备访问
- 不可应用于管道, FIFO, socket 或 终端设备(出错ESPIPE) 

## 文件空洞
- 文件结尾到新写入的数据之间为文件空洞
- 文件空洞不占空间(存储块界限外), 所以一个文件大小名义上会大于实际占据的磁盘容量
- 在文件空洞中写入数据后内核会实际分配磁盘空间
```c++
int posix_fallocate(int fd, off_t offset, off_t len);
// 确保 [offset, offset + len) 范围内分配磁盘空间
// 防止在文件空洞写数据因为磁盘空间不够而失败
```

# 3. 习题
- (#copy_file_hole.cc)
> rpm2cpio package.rpm | cpio -idmv