
## 环境变量
- 变量可以分为：**局部变量**，**环境变量**，**shell变量**。 
   - shell变量：一部分是局部变量，一部分是环境变量，对shell很重要。比如：`IFS`，`PS1`是局部shell变量
   - 环境变量使用`export`进行导出，环境变量可以让子进程继承
- `.bashrc`：在每次创建bash进程时会执行一次
- `/dev/null`：垃圾箱，黑洞


## 输入输出

-  标准输入输出：`stdin-0`, `stdout-1`, `stderr-2`。其中，数字是文件描述符。 
-  标准输入输出在其他程序中的体现：可以和`c++`一起使用 

```c
// main.cpp
void main() {
    char str[256];
    cin.getline(str, 5);
    cout << str << endl;
}
```

```shell
echo "acccoco" | ./main
# 得到输出：accc
```


## 重定向
输出重定向：

- `>` 将 `stdout` 重定向到文件
- `2>` 将 `stderr` 重定向到文件
- `&>` 将 `stdout` 和 `stderr` 重定向到文件
- `>>`表示将输出追加到文件末尾

将 `stderr` 和 `stdin` 都输出到文件，顺序不能变：

- 注：`>&` 表示重定向的目标是文件描述符，而不是文件名称
```
# 将错误输出重定向到标准输出，再输出到文件中
cmd > file 2>&1
```


-  `|`：管道运算符：将标准输出重新作为标准输入 
```shell
# 将stderr合并到stdout，将stdout输出到文件中。顺序不能改变
ls + . > file 2>&1;

# 将stdout输出到file1，将stderr输出到file2
ls + . >file1 2>file2;

# 将 stderr 重定向到 stdout，并用作 pipe 的输入
cmd1 2>&1 | cmd2
```



## 后台任务
`nohup`表示忽略所有的挂起信号（`SIGUP`），进程在终端退出后仍然可以运行；
`&`让进程在后台运行
```shell
nohup cmd &
```



## 语法

### 括号的作用
**单小括号**`**()**`
```shell
# 新开一个shell，执行命令
(ls)

# 初始化数组
arr=(1 2 3 4)

# 获取命令执行结果
foo=$(ps -ef | grep ssh | wc -l)
```

**双小括号 **`**(())**`
```shell
# 引用整数计算的值
echo $((2+4))     

# 进行整数运算
((num1++))
```

**中括号**`**[]**`
用于判断
```shell
# 使用 [[]]
if [[ 2 <= 3 ]]; then ls; fi

# 使用 []，相当于 test 命令
if [ 2 -le 3 ]; then ls; fi
```


### 字符串
```shell
# 判断是否相等
if [ $str1 = $str2 ];

# 判断不相等
if [ $str1 != $str2 ];

# 判断长度不为0
if [ -n $str1 ];

# 判断长度为0
if [ -z $str1 ];

# 是否包含子串
if [[ "${str}" =~ "sub" ]];

# 获取字符串长度
len=${#str}
```


### 数组


### `if` 
```shell
# 单行形式
if [ cdt ]; then cmd; fi

# 多行形式
if [ cdt ]; then
	xxx
fi
```


### `while` 
```shell
while [ cdt ]; do
	cmd
done
```


### `for` 
```shell
# 第一种格式
for i in {0..10..1}; do
	echo $i
done

# 第二种格式
for ((i = 0; i < 10; ++i)); do
	echo $i
done

# 第三种格式
for str in "123 abc 456"; do
	echo $str
done
```

