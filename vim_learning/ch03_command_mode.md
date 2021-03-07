# 第三章 命令模式
## 1. 保存与退出
- `:w` 写入`:w!` 强制写入
- `:q` 退出 `:q!` 强制退出
- `:wq` 保存退出 `:wq!` 强制保存退出 `ZZ` 修改后保存退出 没修改直接退出
- `:w filename` 另存为另一个文件 `:20,30 w filename` 将20行到30行的内容另存为另一个文件

## 2. 环境修改
- `:set all / :h option-list` 查看所有属性配置 
- `:set options?` 显示options 的设置内容
- `:set incsearch` 显示搜索过程高亮
- `:set showcmd` 显示当前正在输入的命令
- `:set iskeyword` 设置什么组成了一个单词
- `:set comment` 设置什么构成注释
- `:source ~/.vimrc` 令配置生效

## 3. 其他操作
- `ctrl + p` 返回上一个命令
- `:help` 查询帮助文档 
- `:! command` 暂时退出到执行command
- `:e!` 重新加载文档

##  4. 多窗口多文件编辑
### 多文件
- `$ vim file1 file2 (-O 多窗口)` 打开多个文件 `:e filename` 打开或新建另外一个文件
- `:n / bnext / next` 编辑下一个文件 `:N / bpre / last` 编辑上一个文件 `b 1` 跳转到第1个buffer中
- `:files` 列出所有编辑中的文件

### 多窗口
- `:h window-resize` 查看调整窗口文档
-  `:sp`横向划分窗口 `:sp filename` 将filename打开或新建
-  `:sv`垂直划分窗口 `:sv filename` 将filename打开或新建
-  `ctrl + w + ` : `hjkl` 方向键切换当前窗口 `HJKL` 方向键移动当前窗口 `w` 循环切换当前窗口

### 多标签页
- `:h tabpage` 查看tabpage文档
- `:tabnew / tabe filename` 在新标签页中打开文件
- `:tabc` 关闭当前标签页 `:tabo` 关闭其他标签页
- `ctrl + w + T` 移动当前窗口到新的标签页
- `[N]gt` 切换[第N个]下一个标签页 `gT` 切换上一个标签页 
