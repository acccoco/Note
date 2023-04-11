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