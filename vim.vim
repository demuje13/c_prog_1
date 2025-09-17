" ----------------------------
" vim-plug setup
" ----------------------------
call plug#begin('~/.vim/plugged')

" Auto close brackets, quotes, etc.
Plug 'jiangmiao/auto-pairs'

" Smart indentation for multiple languages
Plug 'sheerun/vim-polyglot'

call plug#end()

" ----------------------------
" Basic settings
" ----------------------------
set nocompatible
set background=dark
syntax on

" Disable swap files
set noswapfile
set nobackup
set nowritebackup

" Enable smart indentation
set autoindent
set smartindent
set smarttab
set expandtab
set shiftwidth=4
set tabstop=4

" Show line numbers
set number

" Search settings
set showmatch
set incsearch
set hlsearch
set ignorecase
set smartcase
