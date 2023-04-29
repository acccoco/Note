
### 不同终端环境的区别

windows下常用的类似unix终端软件有：
- git： 内置精简版 msys2，缺点是自带的预编译的软件包比较少。
- mingw： 打包了gcc等编译器，默认没有git，自带的预编译的软件包比较少。
- cygwin： 最全的类Unix环境支持。缺点：比较庞大。
- msys2：自带大量预编译的软件包，提供pacman便捷安装git、zsh、gcc等软件。推荐使用该软件。
- wsl2：IO 性能非常差

注：同时安装git fow windows和msys2，y运行命令可能出现"using incompatible versions of the cygwin DLL"问题。

---

### 配置

* 下载：官网：[https://www.msys2.org/](https://www.msys2.org/)
* 修改环境变量：将 `C:/msys64/usr/bin` （如果选择 MSYS 环境）加入到环境变量。新增环境变量 `$HOME = xxx`，将 HOME 设置为 windows 的用户目录。设置 `LANG=zh_CN.UTF-8` 避免乱码。
* 为 pacman 换源：[https://mirrors.tuna.tsinghua.edu.cn/help/msys2](https://mirrors.tuna.tsinghua.edu.cn/help/msys2/)。之后执行 `pacman -Sy` 
* 为 Terminal 配置 msys2 zsh（先安装 zsh：`pacman -S zsh`）

注：msys2 会继承 windows 的环境变量。


### msys2 环境的选择

具体环境差异如下：[官网说明](https://www.msys2.org/docs/environments/) 

![[_attachments/Pasted image 20230429235832.png]]

使用不同的环境，需要将不同的路径添加到环境变量。/usr/bin 还是需要的，因为一些软件，例如 zsh 和 git，都只有这个版本。

推荐使用 MINGW64，最稳定。官方推荐的是 UCRT64。

注：Python 不要安装 /usr/bin/python，这个 pycharm 和 vscode 都识别不了。