### ownership

```rust
// 发生了 copy
let a = 1;
let b = a; 

// 发生了 move
let c = String::from("hello");
let d = c;
```


#### move

>[!warning]
>rust 的 move 就是 memcpy，然后编译器不允许访问旧的值。编译器可以将 memcpy 优化掉。

默认执行的是 move 行为，原来的对象会实效。

如果需要深拷贝，使用 `.clone()` 方法

这种类型需要实现 `Drop` trait

move 的示意图：

![[rust/_attachments/trpl04-04.svg | 300]]





#### copy 与 clone

> [!info]
> 非引用赋值或传参时，要么发生 move，要么发生 copy

copy 与 clone 的发生时机：

- copy 动作是「隐式」发生的，只有在赋值语句中才会出现。
- clone 动作是「显式」发生的，只有调用 `clone()` 函数时才会发生。

copy 的行为是固定的，就是逐字节复制。只有当 struct 的所有成员都是 `Copy` 时，struct 才能是 `Copy` 的。

`Clone` 是 `Copy` 的 supertrait，能够 copy 就一定能 clone。

最简单的实现方式：

```rust
#[derive(Copy, Clone)]
struct Acc();
```

临时构造出来的类型也满足这个：

```rust
let x = (1, 2, (), "hello");
let y = x;    // 这里发生的是 copy 而不是 move
```


#### 函数传参

函数传参和赋值语句类似，也有 copy 和 move 的区别：


#### borrow

创建引用就是 borrow 的行为

引用相当于一个指针，传递引用不会发生 move 或者 copy，离开作用域也不会发生 drop

引用的示意图：

![[rust/_attachments/trpl04-05.svg | 400]]

在同一个作用域中，如果存在 ==mutable== 引用，那么不允许有其他任何的引用。可以这样使用：

```rust
let mut s = String::from("hello");
{
    let r1 = &mut s;
    // 使用
}
let r2 = &mut s;
// 使用
```


> [!info]
> 引用的作用域在最后一次使用时结束，而不是在打括号处结束，这和 cpp 有区别

下面的代码是没问题的：

```rust
let mut s = String::from("hello");
let r1 = &s;
println!("{r1}");    // 编译器分析出，r1 的作用域结束

let r2 = &mut s;     // 没问题
```


#### slice

slice 是一种引用，

```rust
let s = String::From("hello world");
let world = &s[6..11];
```

slice 的示意图：

![[rust/_attachments/trpl04-06.svg | 250]]


slice 也是一种 immutable 引用，下面是错误用法：

```rust
let mut s = String::from("hello world");
let world = &s[6..11];
s.clear();     // clear 会使用 mutable 引用，当前还存在 immutable 引用，不允许
println!("{world}");   // immutable 引用在这里才结束
```

