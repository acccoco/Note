撤销工作区某一个文件的修改：

```shell
git checkout --<file>
```

fork 远程仓库的情形：
参考这个：https://zhuanlan.zhihu.com/p/291845721
具体的命令为：
```shell
# 将上游分支添加到本地
git remote add <upstream-name> <url>
# 拉取上游分支
git fetch <upstream>
# 确保当前分支为 master 分支
git checkout <master>
# 合并
git merge <upstream>/<master>
# 编辑提交记录
git rebase ...
```

修改全局的 .gitignore
```shell
git config --global core.excludesFile '~/.gitignore'
```


乱码:

```shell
git config --global core.quotepath false
```



### merge

典型的合并情形如下图所示：

- 当前为与 `master` 分支，执行的命令是 `git merge dev`；
- 原理是：找到 `dev` 和 `master` 的共同祖先，将「共同祖先」-「`dev`」-「`master`」三者的内容聚合在一起（如果没用冲突），生成一次新的提交。

![[_attachments/1651816137329-ad606652-aa5c-414d-b785-d9364f688c84.png | 346]]


### cherry-pick
`git cherry-pick <commit-id>` 的作用是：将「目标提交记录」-「当前提交记录」-「共同祖先」做一次汇总，然后生成一次新的提交记录。
![[_attachments/1651816154749-42313124-d3b1-480c-bdeb-e7e8e96ccef8.png | 333]]


### rebase
变基的核心是「重演」，具体原理如下：

- 当前位于 `dev` 分支，执行的命令是 `git rebase master`；
- 首先找到 `dev` 分支和 `master` 分支的「**共同祖先**」，然后将当前分支相对于共同祖先的更改，在 `master` 分支上「重演」；有几次更改，就进行几次「重演」（可能需要处理冲突），就会生成几个新的提交。

![[_attachments/1651816169225-773fac34-8907-4be4-bc68-1f97cc467c34.png | 399]]

> 注：使用 `git rebase -i <commit-id>` 命令，进行适当的调整，可以让多个「重演」合并在一起。
