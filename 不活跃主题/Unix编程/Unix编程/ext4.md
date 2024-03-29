> 
##### 摘要
> 本文主要介绍了 `ext4` 文件系统。分为以下几个部分：
> `ext4` 的分区结构，`inode` 的作用，如何找到一个文件的数据块，软链接和硬链接。
> 初次之外，还介绍了扩展属性，以及操作扩展属性的命令。



#### `ext4` 的分区结构
`ext4` 文件系统是一种在 `linux` 中广泛使用的文件系统
`ext4` 分区的大致组成：
![[不活跃主题/Unix编程/Unix编程/_attachments/1600050435399-5bb3a968-e3a8-45f1-b74a-9311b1f9393e.png | 381]]
上述分区中每一部分的作用分别为：

超级块：超级块包含该文件系统的各种属性信息。超级块位于分区的固定为位置，在挂载时会最先读取这个块，相当于文件系统的入口。

`inode`表：`inode表` 区域的大小是固定的，每一个 `inode表项` 的大小也是固定的。`inode表项` 记载了文件的相关性信息，以及数据块的索引。

- `inode表项` 的信息：文件的创建者，大小，访问权限等。不包括文件名称。

数据块：就是存放文件数据的地方。

ext4中文件分为两种：普通文件和目录文件，在 `ls` 中分别表示为 `-` 和 `d`


#### 目录文件
目录文件：记录了 `<文件名-inode号>` 之间的对应关系，如下图所示：
![[不活跃主题/Unix编程/Unix编程/_attachments/1600050478073-7215c57e-9b63-482d-a7a8-b8517b83e4fd.png | 242]]

在 `ext4` 中，`inode号` 就是文件的唯一标识，文件名只是一个标记 。
注1：移动文件和重命名文件并不会改变 `inode` 号，只会改变目录文件的记录。
注2：因为目录文件也是文件，所以目录和文件不能重名


#### 查找一个文件的过程
在 `ext4` 文件系统中，查找一个文件，大致是以下的过程：

- 在目录文件中找到对应项，得到 `inode` 号
- 根据 `inode` 号，在 `inode` 表中找到对应表项，索引到文件块
- 重复上述步骤

以查找 `/home/charvl/main.cpp` 文件为例：

![[不活跃主题/Unix编程/Unix编程/_attachments/1600050514982-d4731ebe-5995-458b-bbfe-3218aa9cfc7a.png | 524]]


#### 硬链接和软链接
硬链接：硬链接的两个文件具有相同的 `inode号`，删除任意一个文件，都不会影响另一个文件的可用性。
添加硬链接，会在 `inode` 中增加引用计数
如图所示：在两个不同的目录下都有文件 `acc` ，两者的地位是相等的：

![[不活跃主题/Unix编程/Unix编程/_attachments/1600050545878-7427d66b-ddab-4f27-9d69-d09d5bbb17f8.png | 364]]

软链接：软链接的两个文件具有不同的 `inode号`，软链接文件中记录的是源文件的路径。删除源文件，软链接文件也会不可用。

如图所示：在 `目录1` 和 `目录2` 下都有文件 `acc`，两者地位是不相等的：

![[不活跃主题/Unix编程/Unix编程/_attachments/1600050566589-d84922a5-7f80-41ac-8aa2-6ea21552eadb.png | 486]]

值得一提的是，目录文件中自动存在两个文件 `.` 和 `..`

- `.` 文件是当前目录文件的硬链接
- `..` 文件是父目录的硬链接

如下图所示：`dir` 和 `dir/.` 具有相同的 `inode` 号

![[不活跃主题/Unix编程/Unix编程/_attachments/1600050593025-3eaf1418-99fe-4cf1-bbe2-99c188231b03.png | 315]]


#### 扩展属性
什么是扩展属性：就是将一些键值对``<key, value>`关联到文件。扩展属性需要底层文件系统的支持，`ext4` 是支持的。

扩展属性有命名空间的限制：`system, security, trusted, user`

如何使用扩展属性：需要在挂载时增加相应的选项，以 `/home` 目录为例：

```bash
mount -o remount, acl, user_xatter /home
```

操作扩展属性的命令：`setfattr, getfattr, attr`
