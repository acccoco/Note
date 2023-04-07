### `cin`
`cin`的基本规则：接触到非空白字符（空格，制表，换行）即开始阅读，遇到空白字符即停止阅读。

`istream.get()`可以读取一个字符

1. `cin.get()`：获取一个字符，包括空白字符。如果遇到结束符号，则返回`-1`。
2. `cin.get(char)`读取一个字符，到指定字符中。
3. `cin.get(char*, int, char)`：读取到字符串/数组中，直到指定个数，或者遇到终止字符。

`istream.getline(char*, int, char)`可以读取一串字符

1. 提取一行字符到字符串/数组中，直到指定个数，或遇到终止字符。

`istream.peek()`

- 观测下一个字符，指针并不后移。

`istream.putback(char)`

- 将一个字符添加到输入流中，下一个将会读到。

`istream.ignore()`

- 跳过n个字符，或者直到遇到了终结字符。
- 实质是修改流缓冲的指针：`basic_streambuf._Gnext`。

### `cout`
`ostream.flush()`

- 实质是清空缓冲流`ios._Mystrbuf`

### 缓冲区
文件描述符是数字，是操作系统的概念。默认情况下，文件描述符 `0, 1, 2`都连接到终端 `/dev/ptsx`的。

`stdin`是一个文件指针，类型为 `FILE*`，也就是「流」，这是 C 语言的概念。默认情况下，`stdin`连接到进程的文件描述符 `0`，例如 `/dev/tty/xxx`。`stdin`和 `stdout`是有缓冲的，这个缓冲是用户区缓冲，是 C 语言提供的；而 `stderr` 没有缓冲。

`cin` 是 `basic_istream`类型的全局变量。
以下部分是猜想：`cin`连接到进程的文件描述符 `0`；C++ 为 `cin` 提供了缓冲，也就是所谓的流缓冲。
为什么不要混用 `cout` 和 `printf`，因为两者使用不同的缓冲机制；听说 C++ 会将自身的流缓冲和 C 的输出缓冲区同步。
注：`cerr`是无缓冲的。
![[C++/输入输出/_attachments/Pasted_Graphic.png|400]]

为什么需要缓冲区：因为 `write()`是系统调用，消耗比较大（涉及到从用户态到内核态的切换），减少调用次数可以提高效率。

参考：[https://stackoverflow.com/questions/21084218/difference-between-write-and-printf](https://stackoverflow.com/questions/21084218/difference-between-write-and-printf)


