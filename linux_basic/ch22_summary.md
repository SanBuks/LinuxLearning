
# 第22章 软件管理器
### 1. 基本概念
> 一个安装文件，包含编译后的文件和检测系统环境与依赖软件的脚本，并提供软件的文件信息，方便软件的管理升级。

- 分类 : dpkg/APT (Debian系) RPM/YUM (RedHat系)
- 名称格式 : 软件名-版本信息-发布版本次数.硬件平台 如:logrotate-3.8.6-17.el7.x86_64.rpm 
- 优点 : 检查系统环境, 检测依赖, 数据库形式记录RPM文件信息用于升级删除和认证
- SRPM(src.rpm) : 包含源码的RPM文件,可以修改源码然后编译成RPM文件,最后通过RPM文件安装
- YUM在线升级 : 发布的软件会先存储到YUM服务器内,并记录信息分析依赖列表最终形成软件仓库,安装升级时通过链接服务器获取依赖信息(下载到/var/cache/yum中)检测并自动下载软件进行安装

- RPM 安装路径
> - 软件信息 /var/lib/rpm/
> - 配置文件 /etc/
> - 执行文件 /usr/bin/
> - 动态函数库 /usr/lib/
> - 说明文件 /usr/share/doc|man/

### 2. RPM操作
#### 安装与更新
- $ rpm -i [-UFvh] package_name
> - -i 安装 -U 没有安装直接安装否则更新 -F 没有安装则不安装否则更新
> - -v 显示安装信息
> - -h 显示安装进度
> - --test 测试是否有依赖问题
> - --force 强制更新
> - --prefix newpath 安装到其他目录

#### 删除
- $ rpm -e soft_name 删除软件(必须先删除依赖的软件)
> - --nodeps 强制删除

#### 查询信息
- $ rpm -qa 查看所有软件名称
- $ rpm -qf dir_name 查看目录所属的软件名称
- $ rpm -q \[-p][-licdR] soft_name/package_name
> - -qp 对package信息查询
> - -i 查询软件信息
> - -l 软件涉及到所有的文件 -c 配置文件 -d 说明文件
> - -R 软件依赖的文件

#### 检测与修复
- $ rpm -Va 列出所有被修改后软件的文件
- $ rpm -V soft_name 查看该软件有无被修改
- $ rpm -Vf file_name 查看文件有无被修改
> - -修改提示信息为 : SM5DLUGTP c|d|g|l|r 

- $ rpm -Vp package_name 查看安装软件有无被修改
- $ rpm --rebuilddb 重建RPM数据库

> 安装软件有自己的数字签名,通过公钥对安装软件进行检测.Centos采用GPG加密,米要一般放在/etc/pki/rpm-gpg/下,含有GPG-KEY字样,使用$ rpm --import keyfile_name安装,满足某些软件的安装需求

### 3. yum操作
#### 查询
- $ yum \[-y --installroot=dirname] \[opts] \[parms]
> - -y 要求用户给与回应 --installroot=dirname 指定安装位置
> - search keyword 查找某个关键字
> - list  列出所有yum管理的软件
> - info softname 显示软件的详细信息
> - provides dirname/command 查找含有该目录文件/指令的软件

#### 安装&更新&卸载
- $ yum [opts] \[parms]
> - install soft_name 安装软件
> - update soft_name 更新软件
> - remove soft_name 删除软件

#### 软件的yum配置
- Centos默认配置路径 : /etc/yum.repos.d/CentOS-Base.repo (一般文件以repo结尾)
- 镜像网址 : http://mirrors.nju.edu.cn/centos/7/os|updates|extras/x86_64/
- 一般配置格式 : 
> - [name] : 软件源名称
> - name= : 软件源信息
> - mirrorlist= : 软件可以使用的镜像网站 可以注释掉
> - baseurl= : 直接的软件源网址 必须含有 repodata 目录(依赖数据存放处)
> - enable= : 是否被启用
> - gpgcheck= : 是否使用数字签名
> - gpgkey= : 公钥存放位置

- 同步软件源信息 : $ yum clean all 删除所有软件源的旧数据, 保持同步