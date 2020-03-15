let s:cpo_save=&cpo
set cpo&vim
inoremap <C-Down> :m+1
inoremap <C-Up> :m-2
nnoremap <NL> o
vmap [% [%m'gv``
vmap ]% ]%m'gv``
vmap a% [%v]%
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
vnoremap <C-Down> :m'>+1gv
vnoremap <C-Up> :m-2gv
nnoremap <C-Down> :m+1
nnoremap <C-Up> :m-2 
inoremap <NL> o
inoremap { {}O
let &cpo=s:cpo_save
unlet s:cpo_save
set background=dark
set expandtab
set helplang=en
set mouse=a
set packpath=~/.vim,~/.config/nvim,/etc/xdg/xdg-ubuntu/nvim,/etc/xdg/nvim,~/.local/share/nvim/site,/usr/share/ubuntu/nvim/site,/usr/local/share/nvim/site,/usr/share/nvim/site,/var/lib/snapd/desktop/nvim/site,/usr/share/nvim/runtime,/var/lib/snapd/desktop/nvim/site/after,/usr/share/nvim/site/after,/usr/local/share/nvim/site/after,/usr/share/ubuntu/nvim/site/after,~/.local/share/nvim/site/after,/etc/xdg/nvim/after,/etc/xdg/xdg-ubuntu/nvim/after,~/.config/nvim/after,~/.vim/after
set runtimepath=~/.vim,~/.vim/plugged/gruvbox,~/.vim/plugged/vim-airline,~/.vim/plugged/vim-latex-live-preview,~/.config/nvim,/etc/xdg/xdg-ubuntu/nvim,/etc/xdg/nvim,~/.local/share/nvim/site,/usr/share/ubuntu/nvim/site,/usr/local/share/nvim/site,/usr/share/nvim/site,/var/lib/snapd/desktop/nvim/site,/usr/share/nvim/runtime,/var/lib/snapd/desktop/nvim/site/after,/usr/share/nvim/site/after,/usr/local/share/nvim/site/after,/usr/share/ubuntu/nvim/site/after,~/.local/share/nvim/site/after,/etc/xdg/nvim/after,/etc/xdg/xdg-ubuntu/nvim/after,~/.config/nvim/after,~/.vim/after
set shiftwidth=4
set showmatch
set smartindent
set tabstop=4
set window=54
" vim: set ft=vim :
