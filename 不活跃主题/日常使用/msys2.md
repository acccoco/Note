想要在 windows 下获得接近 unix 的编程体验，只需安装 msys2。

根据官网的步骤安装即可，之后：

- 将 `/mingw64/bin`添加到 shell 的环境变量中
- 利用 pacman 安装常用软件：`vim`，`cmake` 等

注：msys2 会继承 windows 的环境变量，msys2 的 shell 里面可以配置环境变量。应该修改 msys2 的环境变量，而不是 windows 的环境变量。
