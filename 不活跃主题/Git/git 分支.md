---
tags:
    - git
---


### 分支创建与切换

#### 一、创建与切换分支
使用以下命令，可以基于当前的分支创建一个新的分支
```shell
git branch <branch-name>
git checkout <branch-name>
```

或者使用：
```shell
git checkout -b <branch-name>
```

如下图所示：
![[_attachments/1651816082108-e4e19b58-e46f-426d-95ae-38edb7f98657.png | 459]]

注：工作区的修改未暂存，或者暂存区的修改未提交，都无法切换分支。因为分支切换的操作 `checkout` 会用 `commit` 对应的内容替换当前的工作区，并清空暂存区。


#### 二、从某次提交创建分支
可以切换到某次提交，然后基于这次提交创建一个新的分支：
```shell
git checkout <commit-id>
git branch -b <branch-name>
```


### 远程分支
添加一个远程仓库：
```shell
git remote add <repo-name> <url>
```

本地分支和远程分支的提交拉取配置信息，位于 `.git/config` 中：
```shell
[remote "github"]
        url = git@github.com:acccoco/Note.git
        fetch = +refs/heads/*:refs/remotes/github/*
[branch "master"]
        remote = github
        merge = refs/heads/master
```

手动从远程分支拉取：
```shell
git fetch <remote-repo> <local-branch>:<remote-branch>
```

手动推送到某个远程分支：
```shell
git push <remote-repo> <local-branch>:<remote-branch>
```


### 标签
