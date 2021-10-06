" 编码设置
set encoding=utf-8
set termencoding=utf-8
set fileencoding=utf-8 " 设置保存的格式
set fileencodings=ucs-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1 " 设置探测的格式会覆盖fileencoding

" 提示信息
syntax on " 语法高亮
set number " 行号
set hlsearch " 搜索高亮

" 空格缩进与折叠
set tabstop=4 " 制表符=4空格
set shiftwidth=4 " 缩进=4空格
set backspace=2 " 设置删除模式可以删除光标前
set autoindent " 自动缩进
set foldmethod=syntax " 设置语法折叠

" 配色与主题
colorscheme gruvbox " 配色主题 ~/.vim/colors/*.vim

" 寄存器
set clipboard=unnamedplus " 设置系统剪切板为无名

" 映射
" 设置 <space>为自定义热键
let mapleader=" " 

" <leader> + n 行号toggle
nnoremap <leader>n :set number! number?<CR>
" <leader> + p Paste模式toggle
nnoremap <leader>p :set paste! paste?<CR>
" <leader> + g 打开目录
nnoremap <leader>g :NERDTreeToggle<CR>
" <leader> + v 回到目录窗口 
nnoremap <leader>v :NERDTreeFind<CR>

" ctrl + p 打开搜索文件
let g:ctrlp_map='<c-p>'
nmap ss <Plug>(easymotion-s2)
" 启动递归映射开启 快速移动

call plug#begin('~/.vim/plugged')
" 目录浏览 延迟启动
Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }
" 自动补全
Plug 'ycm-core/YouCompleteMe'
" 启动页面
Plug 'mhinz/vim-startify'

Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'ctrlpvim/ctrlp.vim'
Plug 'easymotion/vim-easymotion'
Plug 'tpope/vim-surround'
call plug#end()
