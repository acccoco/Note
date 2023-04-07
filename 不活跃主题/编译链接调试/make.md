
## rule
makefile 的核心是 rule，由三部分组成：
![[_attachments/1633265259982-1f36fd25-902e-435b-8c94-930bd3f900ee.png | 346]]

可以这样理解：rule 就是菜谱，target 就是最终要做出的菜肴，prerequisites 就是原材料；command 是做菜的步骤。

makefile 默认 target 是文件名

注：如果存在一个叫 `clean` 的 target，用来做项目清理；恰好还存在着一个名为 `clean` 的文件，由于 `clean` 是最新的，导致 `clean` 无法正常工作。这时候可以将 `clean` 声明为：`.PHONY`


### 1. 有多个 target 的 rule
```makefile
f1.o f2.o:
	echo $@
# 等价于
f1.o:
	echo $@
f2.o:
	echo $@
```

这就表示这两个 `target` 的“配方”是相同的，这种写法就像是缩写一样

如果只执行 `make f1.o`，得到的输出为：
```shell
echo "1"
```

如果执行 `make all` 命令，会得到如下输出：
```shell
echo "1"
echo "1"
```

有多个 target 时，可以通过 `$@` 得到每个 target 的名称


### 2. 静态模式规则
使用通配符来匹配 target，通过匹配到的部分来生成 prerequisites：
```makefile
foo.o bar.o: %o: %c
	echo $@
# 等价于：
foo.o: foo.c
	echo foo.o
bar.o: bar.c
	echo bar.o
```


### 3. 隐式规则
makefile 对 C 非常友好，它提供了很多的隐式规则，方便构建 C 程序
这也是 makefile 最让人迷惑的地方
```makefile
# 隐式规则：将 .o 文件链接为可执行文件
foo:
# 隐式规则：将 .c 文件编译为 .o 文件
foo.o:
# 正常的显式规则
foo.c:
	echo "int main() { return 0; }" > foo.c
```

隐式规则如下：

- 对于 `n`，将其视为可执行文件，自动地通过 `$(CC) $(LDFLAGS) n.o` 构建
- 对于 `n.o`，将其视为目标文件，自动地通过 `$(CC) -c $(CPPFLAGS) $(CFLAGS)` 或 `CXX -c $(CPPFLAGS) $(CXXFLAGS)` 构建

同时提供了一些内建变量：
```makefile
# C 编译器，默认为 cc
CC = 
# C++ 编译器，默认为 G++
CXX = 
# C 编译的 flags
CFLAGS = 
# C++ 编译的 flags
CXXFLAGS = 
# C 预处理器的 flags
CPPFLAGS = 
# 链接器的 flags
LDFLAGS =
```


### 4. 模式规则
```makefile
# 指定如何将任意 .c 文件编译为 .o 文件
%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
```


## 增量构建的原理
makefile 中存在文件的依赖关系，make 可以判断文件的情况，决定是否重新构建
makefile 如何感知文件是否为最新的？

-  如果目标不存在，则会尝试生成目标 
-  如果目标和依赖都是文件，则会通过最后修改时间检查依赖是否比目标更新，如果更新，则会重新生成目标 

可以构造这样的情形来验证：
```makefile
# makefile 的内容
a: b
	echo "a"
b:
	echo "b"
	
# 先创建 a，再创建 b，使得 b 比 a 更新
touch a; touch b
```

之后，无论执行多少次 `make`，a 的构建流程都会被执行，因为 make 感知到 a 所依赖的 b 比 a 更新。


## 变量

### 1. 变量定义
变量是**字符串**
声明变量时，开头的空格会被忽略，结尾的空格不会被忽略
通过 `=` 声明的变量，可以看到后来的变量
通过 `:=` 声明的变量，只能看到目前为止的变量
```makefile
var_one = one ${var}
var_two = two ${var}

var = 123

foo:
	echo ${var_one}		# 得到输出：one 123
	echo ${var_two}		# 得到输出：two
```

通过 `:=` 定义变量的方式，可以用于为变量追加值
```makefile
one = hello

# one 现在是 hello world
one := ${one} world

# 无限递归，出错
one = ${one} world
foo:
	echo ${one}
```

也可以使用 `+=` 来为变量追加值
当变量未被定义时，`?=` 可以为变量设定值：
```makefile
one = hello
one ?= one first
two ?= two first

foo:
	@echo ${one}		# 输出：hello
	@echo ${two}		# 输出：two first
```

可以通过命令行来指定变量的值：`make var=value`
可以在 `makefile` 中做出声明，表示不受命令行变量的影响
```makefile
override var = 123
```


### 2. 自动变量
内置了许多自动变量
```makefile
t1: one two
	# 表示当前 target
	echo $@
	
	# 表示比 target 更新的 prerequisites
	echo $?
	
	# 表示所有的 prerequisites
	echo $^
```


## 命令
在 cmd 前面加 `@`，在执行时就不会输出命令了


### 每一行命令都运行在独立的 shell 中
上一行不会影响下一行
```makefile
foo:
	# 1. cd 不会影响 pwd
	cd ..
	echo `pwd`
	
	# 2. 由于在同一行，cd 可以影响到 pwd
	cd ..; echo `pwd`
	
	# 3. cd 会影响 pwd
	cd ..; \
	echo `pwd`
```


### export
可以通过 `export` 来导入一个变量，让 shell 也可以使用这个变量
```makefile
foo := 123
export bar := 456
all:
	# 使用 makefile 里面的变量 foo
	# 得到输出：123
	@echo ${foo}
	
	# 双 $$ 相当于转义符号，表示使用 shell 中的 foo 变量
	# 得到输出：
	@echo $${foo}
	
	# 导出 foo 变量，使得其他行的 shell 也能使用该变量
	# 得到输出：456
	@echo $${bar}
```

可以通过 `.EXPORT_ALL_VARIABLES:` 指定，导出所有的变量


### define
可以通过 define 来定义一系列的命令。
```makefile
# 定义 foo 表示一系列命令
define foo
echo ${bar}
endef

bar := 123

all:
	# 展开并执行 foo，得到输出：123
	${foo}
```


### `.DELETE_ON_ERROR:`
该命令表示，如果出现错误，就删除 target，这个命令建议时常开启


### ifeq
相等的判断 `ifeq`
```makefile
all:
ifeq (${foo}, ok)		# 注意 ifeq 后的空格
	echo "foo is ok"
else
	echo "foo is not ok"
endif
```

判断变量是否定义：`ifdef`


## 通配符
使用 `*` 通配符时，最好配合 `wildcard` 函数一起使用
```makefile
# 如果没有完成匹配，则 prerequisite 就是 *.c
t1: *.c
	...
	
# 使用通配符函数，如果没有完成匹配，则 prerequisite 为空
t2: $(wildcard *.c)
	...
```


### * 和 % 的差别
`*` 用于搜索已经存在的文件，`%` 一般用作 target
例如：在空文件夹下有：
```makefile
# 当前文件夹下并不存在 *_1.c 文件，* 通配符匹配不到，保持原状
*_1.c:
	echo 1 $@
# 可以匹配外部传进来的 target，不局限于已存在的文件
%_2.c:
	echo 2 $@
```

执行 `make acc_1.c`，报错；执行 `make acc_2.c`，正确输出结果


## 函数
函数调用的方式：`$(fn, args)` 或 `${fn, args}`
使用函数时注意空格：字符串前后的空格，参数前后的空格
（因为变量是字符串，函数一般用来处理字符串，所以对空格非常敏感）

```makefile
comma := ,
empty :=
# 通过这种方式来定义 1 个空格
space := ${empty} ${empty}

foo := a b c
# 将 foo 里面的空格替换为逗号，注意参数之间没有空格
bar := $(subst ${space},${comma},${foo})

all:
	@echo ${bar}
```


### 后缀替换
因为后缀替换比较常用，所有有很简洁的方法：
```makefile
foo := a.o b.o l.a c.o
bar := $(foo:.o=.c)
all:
	# 输出：a.c b.c l.a c.c
	@echo ${bar}
```


### filter 函数：
从参数中筛选出符合模式的字符串
```makefile
obj_files = foo.1.o foo.2.o bar.1.o bar.2.o
$(filter %.2.o,$(obj_files)): %o: %c
	echo "target: $@, prereq: $<"
# 等价于：
foo.2.o: foo.2.c
	...
bar.2.o: bar.2.c
	...
```


### foreach 函数：
可以识别以空格分隔元素的列表
```makefile
foo := a b c
bar := $(foreach var,${foo},${var}.c)
all:
	# 输出：a.c b.c c.c
	@echo ${bar}
```


### if 函数：
类似于三元运算符，会判断第一个参数是否为空
```makefile
foo := $(if no_empty,1,2)
all:
	# 输出 1
	@echo ${foo}
```


### 自定义函数
定义函数和定义变量相同，可以通过 `$(0)` 这样来索引参数，通过 `call` 来调用函数
```makefile
func = function name is $(0), params: $(1) $(2)
all:
	# 输出：function name is func, params: 2233 bili
	@echo $(call func,2233,bili)
```


### shell 里面的函数
通过 `$(shell <func> [params])` 来执行 shell 里面的函数，输出的换行会被空格替代
```makefile
foo:
	# 得到输出：......
	@echo $(shell ls -al ./)
```
