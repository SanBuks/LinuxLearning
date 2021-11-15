# 1. 相关历史
- 1960年前: 批处理操作系统, 通过读卡机和打印机与计算机交互
- 1960年初: MIT 发展兼容分时系统, 通过数个终端让主机进行分时操作
- 1969年: MIT, Bell(属于AT&T) 和 GE 发展 Multics 系统, 拓展支持终端的数量
- 1969年: Ken Thompson 使用汇编语言简化 Multics 完成 Unics 系统内核和文件系统(所有程序和设备都是文件思想)
- 1973年: Thompson 和 Ritchie 使用 C 语言完成 UNIX 系统内核并带有一定可移植性
- 1977年: Bill Joy 修改 UNIX 内核并增加了工具软件和编译器, 最终形成 UNIX 第一个分支 BSD
- 1979年: AT&T 发布 System V 第七版, 支持个人电脑的 x86 架构并取消 UNIX 内核源代码对学生的提供
- 1984年: Andrew Tanenbaum 完成 x86 架构的 Minix 内核, 主要用于教育行业
- 1984年: Richard Stallman 发起 GNU 计划, 在此期间成立(FSF Free Software Foundation) 基金会完成 Emacs, gcc, glibc, Bash 等软件
- 1985年: Richard Stallman 与律师草拟 GPL
- 1988年: MIT 与其他组织成立 XFree86 发布并维护 X Window System GUI
- 1991年: Linus Torvalds 发布 Linux0.02 内核

# 2. GNU计划与自由软件
- 自由软件: free 指自由度, 而非免费, 自由度包含用户可以自由地执行, 复制, 修改, 再发行, 回馈自由软件
- GNU(GNU's Not UNIX)计划: 目的是建立一个自由开放的操作系统以及相关软件, 倡导自由软件
- 开源软件: 1998 成立的 Open Source Initiative 提出开源软件的授权, 与GPL的主要差别在于授权可以与原版不同商业上的限制较少
- GPL: 防止开自由软件被引用成专利软件, 引用或修改源代码后不能修改 GPL 授权, 不可单纯销售, 但附加上咨询, 售后, 升级, 其他工具的服务进行销售
- [选择开源协议](http://www.ruanyifeng.com/blog/2011/05/how_to_choose_free_software_licenses.html)

# 3. Linux
## 3.1 内核
- 可移植操作系统接口(POSIX): 规范内核和应用程序之间的接口
- 模块化内核: 所有的硬件驱动程序和其他程序都以模块化的规则加入
- 版本号: 3.0版本之前, 奇数版本号为测试版本, 偶数版本号为稳定版本, 后来转变成主线版本, 其中分为长期维护版本和结束开发版本
## 3.2 发行版本
- 发行版本: 整合 Linux 内核, 自由软件, 专属软件, 工具, 文档的可安装程序成为发行版本(用户友好, 可做商业用途)
- 发行版本规则: 这些发行版本会根据Linux Standard Base 和 FHS 规则开发,统一使用官方的Linux内核
- 发行版本分类: 
  - RPM  系: RHEL, SUSE (, Fedora, Centos)
  - DPKG 系: Ubuntu (, Debian, B2D)