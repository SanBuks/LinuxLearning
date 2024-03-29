# 1. 计算机基本概念
## 1.1 基本概念组成
- 计算机定义: 计算机本质是接收用户输入信息, 由CPU处理后, 输出或存储有效信息的机器 
- 计算机组成: 输入输出设备, 存储器, 算术逻辑单元(PU), 控制单元(CU)
- 中央处理器: 算术逻辑单元 + 控制单元, 执行某指令集的指令(微指令), 完成相应操作
## 1.2 指令集及其分类
- 精简指令集(RISC): SPARC, PowerPC, ARM
- 复杂指令集(CISC): AMD, Intel, VIA 的 x86 系列
- 指令集影响: CPU设计架构, 性能, 省电和虚拟化
- 常见指令集: 
  - 多媒体微指令集: MMX, SSE, SSE2, SSE3, SSE4, AMD-3DNow!
  - 虚拟化微指令集: Intel-VT, AMD-SVM
  - 省电功能: Intel-SpeedStep, AMD-PowerNow!
  - 64/32位相容技术: AMD-AMD64, Intel-EM64T
## 1.3 电脑分类
- 巨型机(Supercomputer): 天河, 用于核物理研究、核武器设计等科学计算任务
- 大型机(Mainframe Computer): IBM计算机, 用于商业等安全稳定性数据处理任务
- 小型机(Minicomputer): UNIX服务器, 用于后台业务
- 微型机(Microcomputer): 个人计算机, 用于满足个人需求
## 1.4 进制
- 单位: bit B K M G T P E Z
- 单位区别: 容量一般用二进制, 速度频率用十进制, 如 1KB = 1024B, 1KHz = 1000Hz
  - 硬盘容量一般用十进制计算便于计算扇区, 如500GB = 500\*1000\*1000\*1000B
  - 网速带宽的单位是 Mbit/s 不是 MB/s, 需要除以 8 来确定正常存储的大小
# 2. x86架构基本概念
## 2.1 主板
- 主板: 负责 连接各个组件
- 北桥: 负责 CPU 与 内存, 显卡等速度较快的组件之间通过前端总线(外部总线)传输, 是数据传输的瓶颈
- 南桥: 负责 CPU 与 外存, USB, 网卡等速度较慢的组件之间传输
- 内置北桥: 通过 QPI(Intel), DMI(Intel), Hyper Transport(AMD)等技术, 将内存控制器整合到 CPU 内部达到与显卡, 内存直接通信功能
## 2.2 CPU
- 频率: 每秒工作的次数, 单位GHz (架构不同不能单纯用频率来比较)
- 外频: CPU 与 外部设备(外部总线)一起工作的频率 
- 内频: CPU 的 内部时钟频率
- 倍频: 内频 / 外频
- 超频: 一般指的是超外频, 提高外频和相应的组件芯片频率达到更高的性能, Intel睿频技术可以自动超频, 更好管理分配性能
## 2.3 外部总线(前端总线)
- 外部总线频率: CPU 通过外部总线与北桥相连, 外部总线频率与 CPU 缓存频率一致
- 外部总线位宽: 外部总线一次传输信息的位数
- 外部带宽: 外部总线频率\*外部总线位宽, 如 64bit * 1600MHz = 12.8GB/s (十进制)
## 2.4 线程与字长
- 机器字长: CPU 一次性能够处理信息的位数, 其中 x86 架构CPU一般为32位以下, x86-64架构为64位
- 线程: 是操作系统能够进行运算调度的最小单位, 通过调度机制等让多个线程竞争内核运算实现并行, 提高效率
- 超线程: 增加必要寄存器等其他物理组件, 在逻辑上模拟成两个内核进行运算, 增加线程数量
- 中断申请(IRQ): 通过 IRQ 对 CPU 发送中断请求讯号, 让 CPU 储存并暂停正在进行的工作, 先行处理周边硬件提出的需求(每个部件 IRQ不同)
# 3. 内存
## 3.1 随机存储器
- 静态随机存取内存(SRAM): 速度大于接近于 CPU, 造价高, 一般用于 CPU 二级缓存(L2 Cache), 弥补 CPU 与其他部件速度的不一致性
- 动态随机存取内存(DRAM): 断电后记录消失, 其中规格有 SDRAM 和 DDR SDRAM, 主要用于内存存储,两个内存条组可成128位双通道, 增加内存宽带
## 3.2 只读存储器
- 只读存储器(ROM): 只能读出无法写入信息, 信息一旦写入后就固定下来无法改变, 断电后信息依然存在, 一般存放 BIOS 等开机启动程序
- 带电可擦可编程只读存储器(EEPROM): 同 ROM, 可以更新程序
- 固件(firmware): 写入硬件中的软件
## 3.3 BIOS & CMOS
- 基本输入输出系统(BIOS): 固化到 ROM 的程序, 保存着计算机基本输入输出程序, 开机自检程序和系统自启动程序, 它可从 CMOS 中读写系统设置信息
- CMOS: 是主板上的一块可读写的并行或串行 FLASH 芯片, 指保存计算机基本启动信息(如日期、时间、启动设置等) 
# 4. 显卡
- 显卡(VGA): 通过 GPU 控制芯片与 CPU, 内存等通信, 其中通信规格有 PCI, AGP 和 PCI-Express
- 显卡作用: 显卡缓存存储像素个数和颜色信息, 整体影响分辨率和色彩, GPU处理每秒显示的图形运算结果
- 显卡与显示器连接方式: DVI, HDMI, DisplayPort
# 5. 硬盘与接口
- 机械硬盘(HDD)构成: 主轴马达让碟片转动, 机械手臂可伸展让磁头在碟片上进行读写操作
- 机械硬盘碟片构成: 分有扇区(最小存储单元, 存在第零扇区), 磁道, 柱面(所有碟片的同一个磁道)
- 机械硬盘通信规格: SATA, SAS3, USB (其中 SATA 传输存在 2bit 作为校验位, 所以 1B = 10bit)
- 固态硬盘(SSD): 闪存作为硬盘, 速度比机械硬盘快一个等级
# 6. 操作系统
- 产生需求: 没有操作系统需要面向硬件编程, 不同硬件使得程序不具有可移植性, 所以需要一个程序能够驱动硬件, 并提供一组规范的程序接口, 方便开发调用
- 操作系统(OS): 管理和分配计算机资源的程序, 其中主要功能由内核提供
- 内核(Kernel): 参考硬件规格编写负责硬件的管理和驱动, 提供系统调用接口, 管理进程和内存, 文件管理, 驱动管理等功能