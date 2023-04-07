---
tags:
    - git
---

> `checkout` 与 `reset` 是什么：
>  
> - `checkout` 主要用来修改「工作区」和「暂存区」。提交记录并不会发生改变。
> - `reset` 主要用来修改「提交记录」。「工作区」和「暂存区」按情况改变。



### `checkout`
`**git checkout <commit-id> <files>**` ：
这个命令可以用来从某次提交中恢复出某个文件，恢复到「**暂存区**」和「**工作区**」。

用下表来表示执行 `git checkout <target> <file>` 前后文件内容的变化：

- `working` 表示工作区，`index` 表示暂存区，`target` 表示目标分支/提交记录；
- `A, B, C` 表示文件的内容/状态，发生的变化用 `**[]**` 来强调
```
        | working    index    target
--------+----------------------------
 before |    A         B         C
 after  |   [C]       [C]        C
```

> 注：常常会使用 `git checkout HEAD -- <file1> <file2>` 命令来撤销对文件的修改。
> 其原理是，让「**工作区**」和「**暂存区**」的文件状态同 `HEAD` 保持一致。


`**git checkout <files>**` ：
这个命令可以将某个文件从「**暂存区**」中恢复到「**工作区**」。

用下表来表示执行 `git checkout <file>` 前后文件内容的变化：

- `working` 表示工作区，`index` 表示暂存区，`HEAD` 表示当前分支指向的提交记录；
- `A, B, C` 表示文件的内容，发生变化的部分用 `[]` 强调
```
        | working    index     HEAD
--------+----------------------------
 before |    A         B         C
 after  |   [B]        B         C
```


### `reset`

`git reset` 主要用于将当前的提交记录恢复到指定的提交记录：
![[_attachments/1651816229577-4f9c0a72-541f-410d-904c-1fda4f668f08.png | 380]]

`git reset` 可以搭配不同的选项来使用，控制「**工作区**」和「**暂存区**」的文件状态。

- 执行的命令是 `git reset <option> <target>`
- `working` 表示工作区，`index` 表示暂存区，`HEAD` 表示当前分支指向的提交记录，`target` 表示目标提交记录。
- `A, B, C` 表示文件的内容，发生变化的部分用 `**[]**` 强调
```
           | working    index     HEAD     target
-----------+------------------------------------
  before   |    A         B         C        D
 no option |    A        [D]       [D]       D
  --soft   |    A         B        [D]       D
  --hard   |   [D]       [D]       [D]       D
```

说明：

- 使用 `--soft` 选项，只改变 `HEAD` 的状态，并不改变「**工作区**」和「**暂存区**」文件的状态；
- 不使用选项，则会改变「**暂存区**」；
- 使用 `--hard` 选项，同时改变「**工作区**」和「**暂存区**」的文件状态。

> 注：
> - `HEAD~2` 表示 `HEAD` **之前的之前的**一次提交记录
> - `HEAD^` 等价于 `HEAD~1`



### `git clean`
这个命令用于将「工作区」的「未被追踪」的文件清除掉。


### `rm`
这个命令一个将「index」或「index 和 工作区」的文件移除，并不会单独移除「工作区」。
使用一下命令仅仅移除「index」，适合取消跟踪某个文件
```bash
git rm --cached -r <dir>
```
