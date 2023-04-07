本文主要研究了`ELF`文件的结构和`Linux`进程的内存布局。
[toc]

#### `ELF`文件结构
`ELF`文件的定义可以从`/usr/include/elf.h`中找到，其结构如下所示：
![[不活跃主题/操作系统/运行时环境/_attachments/1600093571878-ce6cd71d-3c12-4c85-b82e-b71388e65891.png | 267]]

通过`ELF header`可以找到程序入口，可以找到`segment header`和`section header`
通过`segment header`可以找到各个`segment`
通过`section header`可以找到各个`section`，比如`.data`和`.bss`。
`segment`和`section`是指向同一段内容的，区别在于：

- `segment`主要与装载的动作有关，比如某些`segment`是可执行的，而有些是运行时需要分配内存的。
- `section`主要关心各种链接特性，各种说明等。链接器会将几个`section`合成为一个`segment`。


#### ELF文件头
`ELF`文件头主要包含版本，文件类型，入口位置，`section`和`segment`的偏移，数目和尺寸信息。
`ELF header` 的定义和`readelf`命令读取内容的对照：
![[不活跃主题/操作系统/运行时环境/_attachments/1600093571948-70923af0-bbf8-47bf-a6ae-10edf12dac17.png | 691]]

#### Section header的条目格式
`section header`有很多`entry`
`entry`的定义和样子如下：
![[不活跃主题/操作系统/运行时环境/_attachments/1600093571990-676cebcd-73d8-40af-ba28-e500553ef2b7.png | 659]]
合法的`section type`定义如下
![[不活跃主题/操作系统/运行时环境/_attachments/1600093572033-cc352945-f452-485a-8a5c-8230ce19846e.png | 641]]
常见的`section`名称有：

- `.text`：代码
- `.rodata`：只读数据
- `.data`：已初始化的全局变量
- `.bss`：未初始化的全局变量
- `.symtab`：符号表
- `.debug`：调试信息

#### 符号表
结合`ELF`头部的信息，可以看到程序入口是`_start`函数
符号表的作用：

- 文件链接时需要进行符号查找

这个符号表，就是编译原理中的符号表。
为什么函数中的局部变量不出现在符号表中？函数中的局部变量不和函数外的内容发生交互，他们以代码的形式存在于代码区中。
![[不活跃主题/操作系统/运行时环境/_attachments/1600093572071-aa8de267-1c42-483e-b57e-51d4f6caf3b1.png | 795]]

#### `Linux`程序内存布局
这是进程内存的布局，不是文件布局。
![[不活跃主题/操作系统/运行时环境/_attachments/1600093572140-ec8a6320-f012-4ee4-a030-6a40481b5358.png | 288]]
代码段`.text segment`：程序执行的代码，通常是制度的
初始化数据段`.data segment`：某些已经初始化的变量
未初始化的数据段`.bss segment`
可以看到，`ELF`文件结构和`Linux`内存布局存在一些相似之处。
