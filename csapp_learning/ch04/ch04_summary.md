# 1. Y86-64 指令集
> 指令集 ( 指令与指令编码 ) 为 处理器 和 编译器设计者 之间提供了抽象层
> 高级语言 -> (编译器前端) -> 指令码 或 汇编 -> (编译器后端) -> 二进制代码 -> 处理器运行

## 本章背景
- Y86-64 简化的自定义指令集
- Y86-64 汇编器 YAS
- Y86-64 程序模拟器 YIS
- HDL 硬件描述语言种类 Verilog, VHDL 硬件描述语言的几种 
- HCL 简化的自定义硬件描述语言(只描述控制逻辑部分) & HCL 转 Verilog 工具

## 程序员可见状态
- 15个寄存器 : rax 到 r14, 其中固定字长为 64 位, 最后一个为 0xF 表示不用该寄存器
- 3个条件码 : ZF, OF, SF 最近指令相关
- 程序计数器 PC : rip
- 内存 : DMEM
- 状态 Stat : AOK, HLT, ADR(非法地址), INS(非法指令), 在遇到异常时会调用异常处理程序

## 编码
- 编码结构
![](D:\Project\LEARNING\linux_learning\csapp_learning\ch04\ch04_image\instruction_code_schema.png)

- 指令编码内容
![](D:\Project\LEARNING\linux_learning\csapp_learning\ch04\ch04_image\instruction_code.png)

- 寄存器编码内容
![](D:\Project\LEARNING\linux_learning\csapp_learning\ch04\ch04_image\register_code.png)

- 伪汇编代码
```assembly
    .pos 0 # 伪汇编指令指出程序运行开始地址 
    irmovq stack, rsp # 初始化栈指针
    call main # 调用主函数
    halt # 暂停

    .align 8 # 指定数组对齐数
array: # 定义数组元素
	.quad 0x000d000d000d
	...
main:
    ...
    .pos 0x200 # 指定栈底地址
stack: # 栈的起始地址 ( 从高往底减少 )
    ...
```

- `push rsp` 与 `pop rsp` 最终的值 都要 滞后

##  早期 RISC 的不同
- 没有较长延迟指令 
- 流水线要求
- 简单寻址方式
- load / store 体系
- 没有条件码
- 多寄存器, 在函数调用过程中尽量避免内存引用
> RISC 适用于嵌入式, 低能耗, 低成本领域

# 2. 逻辑设计与HCL
> 一个数字系统有三个主要组成部分 : 对位操作的函数的组合逻辑, 存储位的存储单元和控制存储单元更新的时钟信号

## 组合电路
- 定义 : 将多个逻辑门组合成网, 构成计算块, 称为组合电路, 实际中输入改变后会延迟一会改变输出
- 限制 : 输入来源有限(主输入, 存储单元输出, 逻辑门输出), 多个输出无连接, 网无环
- 多路复用器 : 用控制信号控制组合电路的输出逻辑
- 算数逻辑单元(ALU) : 一种多路复用, 根据控制型号选择算术类型
- HCL 情况表达式 : 冒号前是情况表达式, 满足则返回对应结果, 层层相关
```hcl
word out = [
    !a && !b : A // 00
    !a       : B // 01
    !b       : C // 10
    1        : D // 11
];
```

- HCL 集合表达式 : 
```hcl
bool s = code in {code1, code2};
```

## 存储器和时钟
- 时序电路 : 有状态且在状态上进行计算的电路系统
- 存储器定义 : 根据时钟信号, 更新 新存储值 的设备
    - 时钟寄存器 : 根据时钟信号, 存储单个字
    - DRAM : 虚拟内存 和 寄存器文件, 根据时钟信号和地址存储单个字
- 寄存器文件 : 
    - 单个写端口 : valW -> R[dstW],  读可视作组合电路 ( 可有多个写但是需要区分优先级)
    - 两个读端口 : valA -> R\[srcA], valB -> R\[srcB], 写可视作时序电路
    - 时钟信号 : 在时钟上升沿更新写入的值, 同时读出的值会延迟一会改变
    - error : 如果存在访问地址非法情况, error 会被置位

# 3. Y86-64 顺序实现
## 框架
- 硬件中 复制逻辑块 和 额外处理特殊情况要比编写软件成本大, 所以尽量让不同指令共享多的硬件
- 将各个指令的操作组织成阶段, 有助于降低复杂度, 共享硬件

## 阶段
- 取指 :
	- 读取一字节 指令格式 icode : ifun
	- 读取一字节 寄存器编码 ra : rb
	- 有条件读取四字节长数字 valC
	- 计算下一指令地址 valP
- 译码 : 
    - 将寄存器编码 转码为 寄存器标识符
    - 从寄存器文件中 读入 最多两个操作数
- 执行 : 执行 ifun 的操作 包含下列一种 :
    - 计算操作结果, 获取结果值 valE, 设置条件码 (二元操作符, 传送的结果)
    - 计算内存偏移地址 valE
    - 计算栈指针
    - 根据条件码计算 信号
    - 根据条件码进行传送操作或者跳转分支
- 访存 : 将数据写入内存 或 从内存读出数据 valM
- 写回 : 将最多两个结果 (valE, valM) 写入对应寄存器
- 更新 : PC <-- valP 或者 根据 信号 计算 PC

## 具体命令
### 从不回读
- 处理器从不为了完成一条指令而读取由该指令更新的状态
- 优点 : 
    - 产生额外的信号减少重复读的周期
    - 可以同时对多个硬件并行操作

### op rA, rB
```text
F : icode : ifun <-- M1[PC]
    rA : rB <-- M1[PC+1]
    valP <-- PC + 2
D : valA <-- R[rA]
    valB <-- R[rB]
E : valE <-- valB op valA [ALUB : ALUA]
    set CC
M :
W : R[rB] <-- valE
P : PC <-- valP
```

### irmovq, rrmovq, mrmovq
```text
irmovq $n, rB
F : icode : ifun <-- M1[PC]
    rA : rB <-- M1[PC+1]
    valC <-- M8[PC+2]
    valP <-- PC + 10
D : 
E : valE <--  0 + valC [ALUB : ALUA]
M :
W : R[rB] <-- valE
P : PC <-- valP

rrmovq rA, rB
F : icode : ifun <-- M1[PC]
    rA : rB <-- M1[PC+1]
    valP <-- PC + 2
D : valA <-- R[rA]
E : valE <--  0 + valA
M :
W : R[rB] <-- valE
P : PC <-- valP

mrmovq $n(rB), rA
F : icode : ifun <-- M1[PC]
    rA : rB <-- M1[PC+1]
    valC <-- M8[PC+2]
    valP <-- PC + 10
D : valB <-- R[rB]
E : valE <--  valB + valC
M : valM <-- M8[valE]
W : R[rA] <-- valM
P : PC <-- valP
```

### rmmovq
```text
rmmovq rA, $n(rB)
F : icode : ifun <-- M1[PC]
    rA : rB <-- M1[PC+1]
    valC <-- M8[PC+2]
    valP <-- PC + 10
D : valA <-- R[rA]
    valB <-- R[rB]
E : valE <--  valB + valC
M : M8[valE] <-- valA
W : 
P : PC <-- valP
```

### push rA & call dest
```text
push rA
F : icode : ifun <-- M1[PC]
    rA : rB <-- M1[PC+1]
    valP <-- PC + 2
D : valA <-- R[rA]
    valB <-- R[rsp]
E : valE <-- valB - 8
M : M8[valE] <-- valA # 先访存, 再写回
W : R[rsp] <-- valE
P : PC <-- valP

call dest
F : icode : ifun <-- M1[PC]
    rA : rB <-- M1[PC+1]
    valC <-- M8[PC+2]
    valP <-- PC + 10
D : valB <-- R[rsp]
E : valE <-- valB - 8
M : M8[valE] <-- valP
W : R[rsp] <-- valE
P : PC <-- valC
```

### pop rA & ret
```text
pop rA
F : icode : ifun <-- M1[PC]
    rA : rB <-- M1[PC+1]
    valP <-- PC + 2
D : valA <-- R[rsp]
    valB <-- R[rsp]
E : valE <-- valB + 8
M : valM <-- M8[valA]
W : R[rA] <-- valM # 从内存读取的数valM 写回优先级大于 valE
    R[rsp] <-- valE
P : PC <-- valP

ret
F : icode : ifun <-- M1[PC]
    valP <-- PC + 1
D : valA <-- R[rsp]
    valB <-- R[rsp]
E : valE <-- valB + 8
M : valM <-- M8[valA]
W : R[rsp] <-- valE
P : PC <-- valM
```

### jxx dest & cmovxx rA, rB
```text
jxx dest
F : icode : ifun <-- M1[PC]
    valC <-- M8[PC+1]
    valP <-- PC + 9
D : 
E : Cnd <-- Cond(CC, ifun)
M : 
W : 
P : PC <-- Cnd ? valC : valP

cmovxx rA, rB
F : icode : ifun <-- M1[PC]
    rA : rB <-- M1[PC+1]
    valP <-- PC + 2
D : valA <-- R[rA]
E : valE <-- 0 + valA
    Cnd <-- Cond(CC, ifun)
M : 
W : if(Cnd) R[rB] <-- valE
P : PC <-- valP

jxx dest
F : icode : ifun <-- M1[PC]
    valC <-- M8[PC]
    valP <-- PC + 9
D : 
E : Cnd <-- Cond(CC, ifun)
M : 
W :
P : PC <-- Cnd ? valC : valP
```

## 时钟与硬件结构
![](D:\Project\LEARNING\linux_learning\csapp_learning\ch04\ch04_image\seq_hardware_architecture.png)

- 白色部分为组合电路, 在时钟周期开始到结束时产生新的值(信号)
- 蓝色部分为时序电路, 在时钟周期结束到下一个时钟周期开始(上升沿), 更新新的值

### 取指实现
```text
bool instr_valid = (icode : ifunc) in instruction_set
bool need_regids = icode in [
    irmovq, rrmovq, mrmovq, cmovq,
    rmmovq, 
    opq,
    pushq, 
    popq,
];
bool need_valc = icode in [
    irmovq, mrmovq, rmmovq,
    call,
];
```

### 寄存器译码 与 寄存器写回实现
```text
word srcA = [ # 读地址
    icode in { opq, rrmovq, rmmovq, puhsq, comvq } : rA;
    icode in { popq, ret } : rsp; 
    1 : none;
];

wrod srcB = [ # 读地址
    icode in { opq, mrmovq, rmmovq } : rB;
    icode in { pushq, call, popq, ret } : rsp;
    1 : none;
];

word dstE = [ # valE 的写地址
    icode in { opq, irmovq, rrmovq } : rB;
    icode in { pusq, popq, call, ret } : rsp;
    icode in { comvq } && cond : rB;
    1 : none;
];

word dstM = [ # valM 的写地址
    icode in { mrmovq, popq, } : rA;
    icode in { ret } : pc;
    1 : none;
];
```

### 执行阶段实现
```text
alufun = [
    icode == opq : ifun;
    1 : addq;
];
bool setcc = icode in { opq };

aluA = [
    icode in { opq, rrmovq, cmovq } : valA;
    icode in { irmovq, mrmovq, rmmovq } : valC ;
    icode in { pushq, call } : -8;
    icode in { popq, ret } : 8
    1 : none;
];

aluB = [
    icode in { opq, mrmovq, rmmovq, puhsq, call, pop, ret} : valB;
    icode in { irmovq, rrmovq, cmovq } : 0;
    1 : none;
];
```

### 访存阶段实现
```text
word mem_addr = [
    icode in { mrmovq, rmmovq, pushq, call } : valE;
    icode in { popq, ret } : valA;
    1 : none;
];

bool mem_read = icode in { mrmovq, popq, ret };

bool mem_write = icode in { rmmovq, pushq, call };

stat = [
    !instr_valid : SINS;
    imem_error || deme_error : SADR;
    icode == hlt : SHLT;
    1 : SAOK
];
```

### 更新 PC 实现
```text
word new_pc = [
    icode == call : valC;
    icode == jxx && cond : valC;
    icode == ret : valM;
    1 : valP;
];
```

# 4. 流水线
## 计算流水线
- 在每个阶段之间增加流水线寄存器按时钟分段, 周期开始, 上一个阶段的结果更新到寄存器中
- 吞吐量 = 一条指令 / 每条指令完成的周期
- 分段越多, 吞吐量越大, 延迟越高
- 局限性 : 要解决 数据冒险 和 控制冒险

## 流水线实现
### 状态重定时 
- 改进 seq,  实现 seq+ 
- 下一条指令跟进, 需要 PC 更新阶段 前置
- 将 PC 的时钟寄存器 转移成 进行 PC 计算的信号寄存器, 通过组合电路及时计算出 PC

### pipe- 结构 
- 插入流水线寄存器
![](D:\Project\LEARNING\linux_learning\csapp_learning\ch04\ch04_image\pipe-_hardware_architecture.png)
> M 访存阶段 M_stat 位于 访存阶段的状态字段 m_stat 访存阶段产出的状态信号

- 为了流水线每个阶段都不冲突, 需要一直保存必要的寄存器状态
- valP ( 仅仅在 call 中用于访存 ) 在 SelectA中 合并到 valA 中减少中间状态
- 分支预测 ( jxx && cond ) : call 固定下一条指令为 valC,  ret 可通过调用栈成对预测
    - 总选择分支 60%
    - 从不选择分支 40%
    - 反向选择, 正向不选择 65% (循环)
    - 前向分支
- 数据冒险类型 : (条件码寄存器只与操作有关, 且读必然发生在写之后, 状态寄存器每个阶段都有一个不存在冒险)
    - 寄存器冒险 : 数据关联
    - PC 冒险 : 控制流程
    - 内存冒险 : 读之前写完成, 取指之前写完成



# 习题
- 1 & 2 : 注意 大小端, PC 的值 和 跳转指令