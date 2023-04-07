---
tags:
    - git
---


### Git 内部的对象
Git 内部有三种对象：

1. `commit` 对象：包含提交相关的信息。例如提交者，此次的 `commit id`，前一次提交的 `commmit id` 等。
2. `tree` 对象：目录信息。表示此次提交包含哪些文件。
3. `blbd` 对象：实际的文件内容。

三者的关系如下：
![[_attachments/1651816277029-b48f59f8-33de-48e8-b2f7-43c0765eb01b.png | 497]]

> 上述对象都位于 `.git/objects/` 目录下，以 `SHA-1` 的前 2 位为目录名，后 38 位为文件名。



### Git 的引用
Git 中的分支，标签，`HEAD` 都是引用。引用实际上是一个指向 `commit` 对象的指针。
> 引用相关的信息存放于 `.git/refs/` 文件夹里面



##### 一、分支引用
分支引用相关的信息存放在 `.git/refs/heads/` 文件夹下，每个分支都有一个单独的文件。

某个分支的例子：
```shell
# .git/refs/heads/master 文件中的内容 (SHA-1)
22ae1011a1f1631ec82a637f64b5a3dcbba23355
```


##### 二、`HEAD` 引用
`HEAD` 指针指向某个分支或者某次提交记录，表示当前的 `commit` 引用。

例如，某个 `HEAD` 指针的内容：
```shell
# .git/HEAD 文件中的内容
ref: refs/head/master
```

> 注：如果切换到某次提交，而不是切换到某个分支，那么 `HEAD` 指针会直接指向这次提交：

```shell
git checkout 3056627627
cat .git/HEAD
# 3056627627a3d08aac95efcdcbeeff57830379cf
```


##### 三、标签引用
标签引用分为两种：简单标签和复杂标签。

简单标签直接指向某个 `commit` 对象。例如：
```shell
# .git/refs/tags/v1.1 文件的内容
9585191f37f7b0fb9444f35a9bf50de191beadc2
```

复杂标签会有一个「标签对象」，这个对象中记载了标签的详细信息。
![[_attachments/1651816307484-84a5cb64-66f7-4c66-aca0-b78562f52f8b.png | 500]]


### Git 的暂存区
暂存区的实质是 `.git/index` 文件，这个文件可以视为一个 `tree` 对象，记录了即将提交的更改。
```shell
git ls-files --stage
# 100644 a5bce3fd2565d8f458555a0c6f42d0504a848bd5 0       file1
# 100644 180cf8328022becee9aaa2577a8f84ea2b9f3827 0       file2
# 100644 df6b0d2bcc76e6ec0fca20c227104a4f28bac41b 0       file3
```

执行不同命令时，暂存区的变化：

- 通过 `git add <file>` 将文件的更改暂存后，会创建一个 `blob` 对象并放入 `.git/objects/` 中，然后会向 `.git/index` 文件中记录这个文件。
- 使用 `git commit` 命令时，会用暂存区对应的 `tree` 对象来创建一个 `commit` 对象。
- 执行 `git reset HEAD` 后，会用 `HEAD` 指向的分支的 `tree` 对象写入 `.git/index` 文件。
