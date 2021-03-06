[toc]

### `merge` 

典型的合并情形如下图所示：

- 当前为与 `master` 分支，执行的命令是 `git merge dev`；
- 原理是：找到 `dev` 和 `master` 的共同祖先，将「共同祖先」-「`dev`」-「`master`」三者的内容聚合在一起（如果没用冲突），生成一次新的提交。

<img src="img/image-20211221234647288.png" alt="image-20211221234647288" style="zoom:30%;" />

### `cherry-pick` 

`git cherry-pick <commit-id>` 的作用是：将「目标提交记录」-「当前提交记录」-「共同祖先」做一次汇总，然后生成一次新的提交记录。

<img src="img/image-20211221235949300.png" alt="image-20211221235949300" style="zoom:30%;" />

### `rebase` 

变基的核心是「重演」，具体原理如下：

- 当前位于 `dev` 分支，执行的命令是 `git rebase master`；
- 首先找到 `dev` 分支和 `master` 分支的「**共同祖先**」，然后将当前分支相对于共同祖先的更改，在 `master` 分支上「重演」；有几次更改，就进行几次「重演」（可能需要处理冲突），就会生成几个新的提交。

<img src="img/image-20211222002909183.png" alt="image-20211222002909183" style="zoom:25%;" />

>  注：使用 `git rebase -i <commit-id>` 命令，进行适当的调整，可以让多个「重演」合并在一起。