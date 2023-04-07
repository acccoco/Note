
#### 软件包管理
- 搜索软件的命令：`apt search`

- `sudo apt autoremove xxx --purge`：删除包，依赖包，以及配置信息。

- apt工作原理：估计它有一个系统级别的数据库存放依赖关系吧。。

- `autoremove`这个命令：听说这个命令十分危险。它的基本原理是删除自动安装的，且不被依赖的软件包。十分有可能删掉一些系统组件。不要乱用。

- apt和apt-get 的关系：APT相关的操作分散在一系列命令中：apt-get，apt-cache，apt-config中，不太方便，然后apt命令就出现了，同意了这些分散的操作。

- `dpkg`和`apt`并不在一个系统下工作，`dpkg`安装的东西并不会计入`apt`的数据库，但是**新立得知道**。\

- 软件分为这么几种
   - `[已安装，自动]`：apt自动安装的依赖包

   - `[已安装]`：通过apt install 命令手动安装的

   - `[已安装，本地]`：通过.deb包安装的。



#### `deb`软件包内容

```
*.deb
├── control.tar.gz
│   ├── control      # 描述信息：版本，依赖等
│   ├── postinst     # 脚本：安装后执行
│   ├── postrm       # 脚本：卸载前执行
│   └── prerm		 # 脚本：卸载前执行
└── data.tar.xz
    ├── etc
    ├── opt			 # 包主体内容
    └── usr
        ├── bin
        │   └── soft link
        └── share    # 文档，帮助，等
```

- 包的内容分为两部分：`control.tar.gz`和`data.tar.xz`。

- `data.gar.xz`：`dpkg`会将之提取到`/`目录，所以应预先准备好目录树
- `control.tar.gz`：设置`触发器`，设置`man数据库`，卸载干净等都在这里面完成
   - `prerm`：卸载前会执行的脚本
```shell
# remove icons form the system icons
xdg-icon-resource uninstall --size SIZE entry_name
update-menus
# update cache of .desktop file MIME types
update-desktop-database		
update-alternatives --remove xxx path
```

   - `postrm`：卸载后会执行的脚本
```shell
apt-key
apt-config
apt-source
```

   - `postinst`：安装后会执行的脚本
```shell
# add icons to the system icons
xdg-icon-resource install --size SIZE icon_path entry_name
update-menus
# update cache of .desktop file MIME types
# update-alternatives --install xxx xxx xxx xxx
update-desktop-database
# install key
# source
# source list
```
