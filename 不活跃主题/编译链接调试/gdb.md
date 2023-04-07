
## 前置条件
- 编译的时候使用 `-g` 选项，附加符号信息
- 源代码：调试文件中并不保存代码文本，只有符号信息和对应的行号信息，如果移动了源代码位置，gdb就没法显示代码上下文了


## 基本操作
```shell
# 运行到断点
r, run

# 继续执行到下一个断点
c, continue

# 下一步，不进入函数
n, next

# 下一步，要进入函数
s, step

# 退出循环
until

# 退出 gdb
q, quit
```


## 带参数调试
```bash
# 方法1
gdb hello
run your_name
> hello your_name

# 方法2
gdb hello
set args your_name
> hello your_name
```


## 查看代码
```shell
# 查看代码，默认看 10 行
l, list

# 某行上下的 10 行
list <line>

# 查看函数
list <func>
```


## 断点
```shell
# 在某行打断点
b <line>

# 显示所有的断点
b

# 删除某行的断点
cl <line>
```


## 查看表达式
```shell
# 查看表达式的值
print <exp>

# 观察表达式的值，单步后立即展示这个表达式
display <exp>

# 监视表达式的变化，一旦表达式发生了变换，gdb就会 终止？
watch <exp>
```


## 堆栈
```bash
# 查看当前堆栈
bt, backtrace
```


## 调试正在运行的进程
```shell
gdb --pid=<pid>
```


## 调试线程
```shell
# 显示所有可调试的线程
info threads

# 调试某一个线程
thread <n>
```


## 调试 core
主动产生 core 文件：
```shell
gcore <pid>
```

调试 core 文件：
```shell
gdb -core=<core-file>
```

应该和可执行文件一起调试，否则没有符号表
