# 第零章 插件与配置
## 1. 配置文件目录
- ~/.vimrc 个人配置文件
- ~/.viminfo 记录文件的操作

- ~/.vim/autoload 自动加载脚本目录
- ~/.vim/colors 配色主题目录
- ~/.vim/plugged 插件目录

## 3. 其他问题
### 中文编码问题
- Linux 系统支持的语言 配置在/etc/locale.conf中
- Bash 语言与 LANG 和 LC\_ALL 有关
- 文本编码要与GNOME下的终端字符编码要一致
- 配置的名称 为LANG/export LC\_AL= `en_US.[编码] / zh_CN.[编码]`
> -  ascii  / gb2312 / gbk / gb18030  范围由小到大
> - big5 表示繁体中文, utf8兼容ascii

### DOS与UNIX环行符转换
- 换行符号 DOS : "^M$"(CRLF) UNIX :"$"(LF)
- 比如运行脚本出现问题 : "坏的解释器: 没有那个文件或目录"
- $ dos2unix/unix2dos [-kn] file [newfile]
> - -k 保留文本的时间格式
> - -n 保留源文件将新文件输出为newfile(推荐加上-n)

- $ file filename 查看文本以什么换行和编码方式

### 语系转换
- $ iconv --list 显示iconv支持的语系
- $ iconv -f type -t newtype filename [-o newfile]  将type转换成newtype  
> - -o 保留源文件将新文件输出为newfile(推荐加上-o)
