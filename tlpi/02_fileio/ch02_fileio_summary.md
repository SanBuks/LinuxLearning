- 通用 IO : 每一个文件系统和设备驱动程序都实现了相同的 I/O 系统调用集, 且所有的操作细节在内核中处理, 为应用程序提供了抽象层
- 文件描述符 ( int ) : 标识所有类型的已打开文件, 其中继承自 shell 的文件描述符为 : 
    - stdin : 0 / STDIN_FILENO 标准输入
    - stdout : 1 / STDOUT_FILENO 标准输出
    - stderr : 2 / STDERR_FILENO 标准错误
> 注意固定的描述符也会发生改变 ( 关闭后重新分配给其他的文件 ) 

## open() 
- `int open(const char *pathname, int flags, mode_t mode)`
- 返回进程中未用文件描述符中的最小值, 错误则返回-1, errno 标明错误类型
- falgs 分三类 : 文件访问模式(不可组合,可检索), 文件创建标志(可检索), 文件状态标志(可检索, 可修改)

## create()
- `int creat(const char *pathname, mode_t mode);`
- 等价 `open(const char *pathname, O_WRONLY | O_CREAT | O_TRUNC, mode_t mode)`
- 早期实现中负责创建文件的函数, 现已被 open 整合

## read()

## write()
## close() 
## lseek()
```c++
int fd = open("test", O_RDONLY); 
int fd = open("test", O_RDWR | O_CREAT | O_TRUNC | O_APPEND); 
```