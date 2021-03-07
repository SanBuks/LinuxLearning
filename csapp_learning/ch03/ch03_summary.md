# 第三章 程序的机器级表示
## 3.1 程序编码
- 基础命令
    - `gcc -Og -S` 生成符合原始C代码的汇编 
        - `-O1/-O2` 表示不同优化等级
        - `-masm=intel` 使用intel格式 默认为ATT格式
    - `objdump -d xxx.o` 对目标的代码反汇编
	- `(gdb) x/14xb multstore` multstore的地址开始 打印(x/) 14个十六进制的字节(14xb)

- 寄存器 : 
    - PC 程序计数器 %rip 存放下一条指令地址
    - 16个通用寄存器 存放整数或地址, 一般用于保存实参, 局部变量和返回值等
    - 条件码寄存器 保存算术或逻辑指令状态信息, 保存控制流信息
    - 向量寄存器 保存多个整数或浮点数
- 程序内存 : 
    - 机器代码
    - 操作系统信息 和 运行时栈
    - 手动分配的内存块 堆

## 3.2 数据格式

| 类型   | 汇编后缀 | 大小(x86-64) |
| ------ | -------- | ------------ |
| char   | b        | 1B           |
| short  | w        | 2B           |
| int    | l        | 4B           |
| long   | q        | 8B           |
| char * | q        | 8B           |
| float  | s        | 4B           |
| double | l        | 8B           |

## 3.3 访问信息
### 整数寄存器
- 寄存器类型 :

| 用途         | 寄存器名字       |
| ------------ | ---------------- |
| 返回值       | a                |
| 栈指针       | sp                |
| 参数1-6      | di si d c 8 9    |
| 调用者保存  | 10 11            |
| 被调用者保存1-6 | b bp 12 13 14 15 |

- 不同大小的寄存器名字命名方式 :

| 64位 | 32位 | 16位 | 8位  |
| ---- | ---- | ---- | ---- |
| rax  | eax  | ax   | al   |
| rdi  | edi  | di   | dil   |
| r8   | r8d  | r8w  | r8b  |

> 生成1,2字节数字的指令 其余不变 ; 生成4字节数字指令 高位置零

### 操作数指示符

| 格式           | 操作数值             | 类型         |
| -------------- | -------------------- | ------------ |
| $ num          | num                  | 立即数寻址   |
| ra             | R[ra]                | 寄存器寻址   |
| num            | M[num]               | 绝对寻址     |
| (ra)           | M[R[ra]]             | 间接寻址     |
| num(ra, rb)    | M[num+R[ra]+R[rb]]   | 变址寻址     |
| num(ra, rb, s) | M[num+R[ra]+R[rb]*s] | 比例变址寻址 |

> 比例因子 s=(1,2,4,8)

### 数据传送指令
- 传送 S -> D 中 源可以是立即数, 内存和寄存器, 目标可以是内存和寄存器 
- 传送过程中不可以内存->内存, 必须有寄存器进行中间过度

| 移动指令        | mov S D (S->D) |
| ------------- | -------------- |
| movb          | 传送 字节       |
| movw          | 传送 字         |
| movl          | 传送 双字(同时高双字置零)       |
| movq          | 传送 四字<br>(如果源是立即数只能为32位补码, 符号扩充到高位) |
| movabsq num R | 传送 绝对四字立即数到 寄存器 |

- 传送 S -> R 中 源可以是 内存和寄存器, 目标是寄存器

| 移动零拓展指令        | movz S R (S->R) |
| ------------- | -------------- |
| movzbw          | 字节 零拓展到 字 |
| movzbl          | 字节 零拓展到 双字 (同时高双字置零) |
| movzbq          | 字节 零拓展到 四字 |
| movzwl          | 字 零拓展到 双字 (同时高双字置零) |
| movzwq		  | 字 零拓展到 四字 |
| movzlq 被 movl 取代	| - |

| 移动符号拓展指令        | movs S R (S->R) |
| ------------- | -------------- |
| movsbw          | 字节 符号拓展到 字  |
| movsbl          | 字节 符号拓展到 双字 |
| movsbq          | 字节 符号拓展到 四字 |
| movswl          | 字 符号拓展到 双字 |
| movswq		  | 字 符号拓展到 四字 |
| movslq		  | 双字 符号拓展到 四字|
| cltq		  	  | %eax 符号拓展到 %rax|


- 类型转换如果发生截取则 先转存再截取
- 注意某些生成双字的命令可以取代生成四字的命令 如 movzbq => movzbl 
- 注意 char 在 gcc实现层面为有符号数

### 压栈弹栈

| 指令    | 效果                  |
| ------- | --------------------- |
| pushq S | %rsp -=8<br>M[%rsp]=S |
| popq D  | D=M[%rsp]<br>%rsp+=8  |

- 一般栈底在地址高位, 可以通过%rsp+n\*8 读取栈内任意元素

## 3.4 算术与逻辑运算
### 加载有效地址
- `leaq S, D` : D <-- &S 将源的地址作为立即数(如 $123) 赋予目标
- 一般作用于加法和优化成有限形式乘法

### 一元和二元操作
> 一元二元, 移位和逻辑操作都有 b w l q四个版本

- 一元 : `inc, dec, neg, not D` : D <-- op D
- 二元 : `add, sub, imul, xor, or, and S, D` : D <-- D op S

### 移位操作
- `sal(shl), sar(算术右移), shr(逻辑右移) k, D` : D <-- D op k  
- k 是立即数或者存放在 %cl 
    - %cl 有效位数m :  2^m=w(D)  (确保移位k<数据位数) 
- D 可存放在寄存器和内存

### 特殊算术操作

| 指令                 | 效果                                                      |
| -------------------- | --------------------------------------------------------- |
| imulq S 有符号全乘法 | %rdx : %rax <-- S\*%rax                                   |
| mulq S 无符号全乘法  | %rdx : %rax <-- S\*%rax                                   |
| clto 符号拓展为8字   | %rdx : %rax <-- %rax                                      |
| idivq S 有符号全除法 | %rdx <-- %rdx : %rax mod S<br>%rax <-- %rdx : %rax div S  |
| divp S 无符号全除法  | %rdx <-- %rdx : %rax mod S<br/>%rax <-- %rdx : %rax div S |

## 3.5 控制
### 条件码
- CF : 进位标志 检测无符号溢出
- ZF : 判断结果是否为零
- SF : 判断结果是否为负数
- OF : 是否产生补码溢出
> leaq 不改变任何条件码

- `cmp S1, S2` 根据 S2-S1 结果设定条件码 , 有bwlq四个版本
- `test S1, S2`根据S1&S2 结果设定条件码, 有bwlq四个版本

### 访问条件码

| 指令                        | 效果                   |
| --------------------------- | ---------------------- |
| sete/setz D 相等            | D <-- ZF               |
| setne/setnz D 不相等        | D <-- ~ZF              |
| sets D 负数                 | D <-- SF               |
| setns D 非负数              | D <-- ~SF              |
| setg/setnle D 大于(有符号)  | D <-- ~( OF^SF ) & ~ZF |
| setge/setnl D 大于等于      | D <-- ~( OF^SF )       |
| setl/setnge D 小于          | D <-- OF^SF            |
| setle/setng D 小于等于      | D <-- ( OF^SF \| ZF )  |
| seta/setnbe D 大于 (无符号) | ~CF & ~ZF              |
| setae/setnb D 大于等于      | ~CF                    |
| setb/setnae D 小于          | CF                     |
| setbe/setna D 小于等于      | CF \| ZF               |

- D是低8字节寄存器, 在命令之前要将寄存器高位清零

### 跳转指令
- `jmp Label` : 直接跳转到Label处(程序内)
- `jmp *Oprend` : 间接跳转
- `j* Label` : 条件跳转, \*通配set指令





