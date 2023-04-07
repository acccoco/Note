
## GCH
GHCi是一个解释程序，常用的命令如下

- `:q` 退出
- `:l xxx` 加载文件
- `:t xxx` 查看对象的类型


## 风格
变量：`someCatMeet`
类型：`SomeCatMeet`


## 变量定义
Haskell 中，变量的值无法改变
```haskell
i = 1
-- 这表示将 i 定义为 1，此后 i 的值不能改变
```


## 基本类型
| `Int`  | 大小有限，大概是 8 字节 |
| --- | --- |
| `Double` | 双精度浮点数 |
| `Float` | 单精度浮点数 |
| `Integer` | 超级大的整数，只要内存能够装下 |
| `Bool` | 布尔 |
| `Char` | Unicode 字符类型 |
| `String` | 其实是字符列表的语法糖 |



## 运算符
不等于符号是：`/=`
浮点数除法：`/`
整数除法：`div` 函数

`$` 这个操作符：`f (g (h x))` 等价于 `f $ g $ h x` 
这个操作符的优先级较低，使用场景为：
```
length . filter odd [1..12]
-- 错误

length . filter odd $ [1..12]
-- 正确
```

如果一个表达式被 `$` 分隔，两边的部分会先求值，最后再进行整个的求值
```
take 3 . repeat $ 2 + 3
-- [5,5,5]

take 3 . repeat $ (2 + 3) ++ [0]
-- 错误，因为 $ 的右半部分表达式 (2 + 3) ++ [0] 是无效的
-- 正确做法如下：
(take 3 . repeat $ 2 + 3) ++ [0]
-- [5,5,5,0]
```


`$` 表示执行的意思，接受两个参数，第一个是函数，第二个是参数：
```haskell
($) sum [1, 2, 3]
-- 6
```



## 控制语句

### if
不能省略分支，每个分支都有返回值
```haskell
if x > 100 then 1 else 2
```


### case
```haskell
case exp of 
  pat1 -> exp1
  pat2 -> exp2
  ...
```


### where
如果前面多次用到一个计算出的表达式，可以用 `where` ：
```haskell
[n+1, n..1] where 
    n = length [1..3]
```


### for
可以用 `map` 和列表实现 `for` 的功能
