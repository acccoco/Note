---
tags:
    - git
---

> 贮存是将当前的「工作区」和「index」创建为一次「commit」，并指向「HEAD」。
> 恢复贮存的时候，确保「工作区」和「index」都是和「HEAD」一致的状态，这样不会有冲突。



#### 原理
执行 `git stash` 后，会将当前的「工作区」和「index」都存放起来，相当于建立了一个新的「commit」：
![[_attachments/1651816445034-7599a451-829e-4695-bc3e-bea300b202a1.png | 348]]

执行完 `git stash` 后，「工作区」和「index」会被设置为和 `HEAD` 一样的状态。
```
        | Working    Index     HEAD
--------+----------------------------
 before |    A         B         C
 stash  |   [C]       [C]        C
```


#### `stash push`
没有参数的 `git stash` 就等价于 `git stash push` 命令。

默认情况下，未被跟踪的文件不会被放入贮藏，使用 `-u` 选项可以将未被跟踪的文件也贮藏。
```bash
git stash -u
```


#### `stash pop`
`git stash apply` 和 `git stash pop` 类似，只是 `apply` 并不会丢弃贮藏的内容，而 `pop` 会丢弃。

`git stash drop` 可以手动丢弃一个贮存。

恢复的时候，默认只回复「工作区」，「index」区的就被丢弃了。使用 `--index` 选项可以同时将 `index` 区给恢复出来。
```
        | Working   Index    HEAD    Stash-W   Stash-I
--------+----------------------------------------------
 before |    C        C        C        D         E
 no-opt |   [D]      [D]       C
--index |   [D]      [E]       C
```
