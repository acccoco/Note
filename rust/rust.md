### 最棒的参考资料


```cardlink
url: https://zh.practice.rs/why-exercise.html
title: "关于 pracitce.rs - Rust By Practice( Rust 练习实践 )"
description: "Learning Rust By Practice, narrowing the gap between beginner and skilled-dev with challenging examples, exercises and projects."
host: zh.practice.rs
favicon: favicon.svg
```


```cardlink
url: https://doc.rust-lang.org/book/
title: "The Rust Programming Language - The Rust Programming Language"
host: doc.rust-lang.org
favicon: favicon.svg
```


```cardlink
url: https://doc.rust-lang.org/stable/rust-by-example/
title: "Introduction - Rust By Example"
description: "Rust by Example (RBE) is a collection of runnable examples that illustrate various Rust concepts and standard libraries."
host: doc.rust-lang.org
favicon: favicon.svg
```


### [[rust/模块]]

### debug

可以将类型标记为 `#[derive(Debug)]`，这样可以直接用 `println!` 打印出来。

使用 `{:?}` 可以打印出类型，使用 `{:#?}` 可以以 pretty 的形式打印。


### 变量声明

默认变量是不可变的：

```rust
let mut m1 = 123;    // 可变
let m2 = 123;        // 常量
```

#### shadow

shadow：可以通过再次声明同名变量来 shadow 之前的声明，存在作用域：

```rust
let x = 114;
println!("{x}");       // 114
{
    let x = 514;
    println!("{x}");   // 514
}
println!("{x}");       // 114
```


shadow 可以改变变量的类型：

```rust
let spaces = "    ";         // str
let spaces = spaces.len();   // usize
```



### 引用

引用默认是不可变的：

```rust
io::stdin()
    .read_line(&mut content)
```

rust 中的常量等价于 cpp 中的编译时常量，且必须显式声明起类型：

```rust
const THREE_HOURS_IN_SECOND: u32 = 60 * 60 * 3;
```


### 类型

#### 标量类型

注意：`isize` 和 `usize` 和当前架构有关的，可以是 `32bit` 或者 `64bit`  

`char` 类型的长度为 `4bytes` ，可以表示 unicode scalar value。


#### tuple

可以将不同类型的组装在一起

可以通过 destructuring 或者下标的方式来访问元素

```rust
let tup = (500, 6.4, 'l');  

// destructuring
let (a, b, c) = tup;

// 通过下标访问
let a = tup.0;
```

#### array

类型一致，长度固定，无法动态改变。

```rust
let a: [i32; 4] = [1, 2, 3, 4];
```


### expression 与 statement


> [!info] rust 是 expression-based language
> 有两个概念：statement 和 expression
> - statement 就是指令
> - expression 可以求值



> [!note] rust 中的赋值语句并不是 expression
> - 在 C 语言中，赋值语句是 expression，可以这样写 `x=y=6`
> - 在 rust 中，赋值语句是 stagement


一个典型的例子：

```rust
// 大括号里面的内容是一个 expression
let y = {
    let x = 3;
    x + 1
};
```



### 函数

函数定义时必须要指定参数的类型，如果存在返回值，也需要指定返回值类型

函数默认将最后一个 expression 作为返回值，也可以通过 `return` 语句提前返回值

```rust
fn plus_one(x: i32) -> i32 
{
    x + 1    // 注意结尾没有分号
}
```


### 控制流

#### if

if 只接受 `bool` 类型作为条件

if 语句是一个 expression，可以这样用：

```rust
let num = if 2 > 1 { 5 } else { 6 };
```

如果 if 的分支是 expression 而不是 statement，需要确保所有分支的 expression 的类型一致。


#### loop

loop 是一个表达式，可以求值

```rust
let mut counter = 0;
let result = loop {
    counter += 1;
    if counter == 10 {
        break counter * 2;
    }
};
```


如果有多层 loop 嵌套，可以选择跳出到哪一层：

```rust
// label 以单引号开始
'label_1: loop {
    break 'label_1;
}
```


#### while

```rust
while bool {

}
```


#### for

用于在集合中进行 loop：

```rust
let a = [1, 2, 3, 4, 5];
for e in a {}
```





### 字符串

栈上的字符串，硬编码的：string literals

堆上的字符串：`String` 


[[rust/ownership]]



### structure

```rust
let user1 = User {
    email: String::from("someone@example.com"), 
    username: String::from("someusername123"), 
    active: true, 
    sign_in_count: 1, 
};
```

结构体只能被标记为整体 mut 的，无法单独为某个字段标记 mut

结构体的更新语法

```rust
let user2 = User {
    email: String::from("xxx"),
    ..user1     // 从另一个结构体中得到
};
```


#### tuple strut

这个更像是为 tuple 赋予了特定的名称：

```rust
struct Color (i32, i32, i32);

let black = Color(0, 0, 0);
```


#### 方法

方法可以和字段同名

```rust
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn width(&self) -> bool {
        self.width > 0
    }
}
```


#### 构造函数

没有特定的构造函数名称，只有 `Self` 这个类型别名。可以这样实现和使用：

```rust
impl Rectangle {
    fn square(size: u32) -> Self {
        Self {
            width: size,
            height: size,
        }
    }
}

fn main() {
    let s1 = Reacangle::square(42);
}
```


[[rust/模式匹配]]

### collection

#### vec

常见错误

```rust
let v = vec![1, 2, 3, 4];

let first = &v[0];   // immutable 引用

// first 已经持有了 immutable 引用，push 会使用 mutable 引用，报错
v.push(114);
```

修改元素的做法：

```rust
let mut v = vec![1, 2, 3];
for i in &mut v {
    *i += 3;    // 需要 * 运算符来解引用
}
```


#### string

String 的实现是 `vec<u8>` ，需要注意。

下面这段代码，看起来再 `push_str()` 时，`s2` 发生了 `move` ，为什么最后 `s2` 仍然是有效的？

```rust
let mut s1 = String::from("foo");
let s2 = "bar";
s1.push_str(s2);
println!("s2 is {}", s2);
```

因为 `push_str` 的参数类型是 `str&` ，此处发生了类型转换。


**字符串切片**：

由于 String 中存放的是 byte，因此在进行切片操作时，应该明确表示需要的是 byte 还是 char：

```rust
for c in "你好".chars() {
    println!("{c}");
}
// 你 好

for b in "你好".bytes() {
    println!("{b}");
}
// 228 189 160 229 165 189
```


### 错误处理

#### panic

一些内部错误，例如数组访问越界，以及手动调用 `panic!()` 都会引发 panic

可以在 `Result<T>` 对象上调用以下方法来进行快速错误处理：

- `unwarp()` ：成功，则返回内容；失败，则引发 panic
- `expect(&str)`：可以自定义错误信息


#### 错误传播

另一个种错误处理方式是：将错误传递给上层。

rust 提供了 `?` 运算符来简化相关操作。

```rust
use std::fs::File;
use std::io;
use std::io::Read;

fn read_username_from_file() -> Result<String, io::Error> {
    // 出现错误，直接返回错误；没有出错，则提取出 Ok(res) 中的 res
    let mut username_file = File::open("hello.txt")?;
    let mut username = String::new();
    username_file.read_to_string(&mut username)?;
    Ok(username)
}
```


`?` 运算符也可以和 `Ooption<T>` 一起使用：（注意，`next()` 函数本身返回的就是 `Option<T>` 

```rust
fn last_char_of_first_line(text: &str) -> Option<char> {
    text.lines().next()?.chars().last()
}
```


使用 `?` 时，`Result` 和 `Option` 不能混用。


在 `main` 函数中使用 `?` 运算符：

```rust
use std::error::Error;
use std::fs::File;

// 其中：Box<dyn Error> 表示任何种类的错误，对应 C 代码的各种退出值
fn main() -> Result<(), Box<dyn Error>> {
    let greeting_file = File::open("hello.txt")?;

    Ok(())
}
```


### 范型

在函数中使用范型：

```rust
// 函数中使用
fn foo<T>(list: &[T]) -> &T {}
```


在范型结构体上实现方法：

```rust
// 结构体中使用
struct Point<T> {
    x: T,
    y: T,
}

impl<T> Point<T> {
    fn x(&self) -> &T {
        &self.x
    }
}

// 这个方法仅在 Point<f32> 中存在
impl Point<f32> {
    fn distance_from_origin(&self) -> f32 {
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}
```


函数调用时，使用 `::<T>` 来显式指定范型类型：

```rust
foo::<i32>(...);
```


#### const 范型

可以将编译时常量作为类型参数，例如：

```rust
struct Array<T, const N: usize> {
    data: [T; N]
}
```


### Trait

定义以及实现 trait

```rust
trait Summary {
    // 提供了默认实现的 trait
    fn summarize(&self) -> String {
        String::from("(to impl)")
    }
}

struct Tweet {
    username: String,
    content: String,
    reply: bool,
    retweet: bool,
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }
}
```


让函数支持 trait

```rust
fn foo(item: &impl Summary) {}

// 或者下面这种方式
// 下面这种方式还可以确保 item1 和 item2 类型相同
fn foo<T: Summary>(item1: &T, item2: &T) {}
```


使用 `+` 来表示支持多种 trait：`<T: Summary + Display>` ，使用 `where` 可以让类型更加明确：

```rust
fn foo<T, U>(t: &T, u: &U) -> i32
where 
    T: Display + Clone,
    U: CLone + Debug,
{}
```


可以为返回类型指定 trait，外部将不会看见类型的细节：

```rust
fn foo() -> impl Summary {}
```


如果多个 trait 具有同名的方法，如何调用特定的 trait 实现：

```rust
struct Dog;

impl Dog {
    fn baby_name() -> String {}
}

impl Animal for Dog {
    fn baby_name() -> String {}
}

fn main() {
    println!("{}", <Dog as Animal>::baby_name());
}
```


#### super trait

要实现某个 trait，必须先实现另一个 trait，可以这样指定：

```rust
trait TraitA: TraitB {

}
```



#### trait object

```rust
let a: Vec<Box<dyn Draw>> = vec![];
```

使用 trait objet，就可以在 `Vec` 中存放实现了特定 trait 的各种对象。

> [!note]
> 这里一定要使用 Box，因为需要在编译期知道内存大小。

如果使用范型，那么 `Vec` 只能存放特定一种类型的对象。

也可以这样使用：

```rust
fn main()
{
    let b = Bili;
    let a : [&dyn Acc; 2] = [&b, &b];
}

trait Acc {}

struct Bili;

impl Acc for Bili {}
```


> [!note] 
> 通过范型实现的叫做静态分发；通过 dyn Trait 实现的就叫做动态分发。


### 生命周期注解

> [!info]
> 生命周期注解是用于==引用==的。

生命周期注解并不会改变参数和返回值的生命周期，它会让 checker 拒绝无法满足约束的值。

生命周期注解是函数签名的一部分，就像函数的参数类型一样。

语法：需要以 `'`  开头

```rust
// 返回值的生命周期和 `x, y` 中生命周期更短的一个一样。
fn longest<'a>(x: &'a str, y: &'a str) -> &'a str
{
    if x.len() > y.len() { x } else { y }
}

fn main() {
    let string1 = String::from("long string is long");
    let result;

    {
        let string2 = String::from("xyz");
        result = longest(string1.as_str(), string2.as_str());
        println!("The longest string is {}", result);
    }
    // 如果解除下一行的注释，则编译不通过
    // println!("The longest string is {}", result);
}
```

分析：`result` 运行下来，就是 `string1` 的引用，即使离开了大括号，`result` 仍然有效。但是后续想要使用，就会无法通过变异。==所以说：生命周期注解并不影响声明周期，只会影响编译器的检查==。


随着编译器越来越强大，程序员可以省略越来越多的生命周期注解，例如上述情况。


结构体的生命周期注解：

```rust
struct Foo<'a> {
    part: &'a str,
}
```

上面代码表示：结构体的实例的生命周期不应该比 `part` 成员更长。


下面是一个综合使用：

```rust
fn longest_with_an_announcement<'a, T>(
    x: &'a str,
    y: &'a str,
    ann: T,
) -> &'a str
    where
        T: Display,
{
    println!("Announcement! {}", ann);
    if x.len() > y.len() { x } else { y }
}
```



#### 静态生命周期

有一个特殊的生命周期注解：`'static` ，他表示引用可以在程序持续时间内存在。

所有的字符串字面量都符合这种生命周期：（因为直接存放在程序的 `.text` 部分，直接存放在磁盘上的。

```rust
let s: &'static str = "Hello world.";
```



---

### 示例：simple grep

> [!info] 示例代码
> simple_grep: 实现最简单的文本搜索功能，包含测试代码
> - ![[rust/_attachments/main.rs|src/main.rs]]
> - ![[rust/_attachments/lib.rs | src/lib.rs]]



### 闭包

闭包的语法：（一般不用类型注释）

```rust
// 完整的
let expensive_closure = |num: u32| -> u32 {
    println!("calculating slowly...");
    thread::sleep(Duration::from_secs(2));
    num
};

// 最简短的
let simple_closure = |num| num;
```


注意：虽然不用为闭包指定类型，但是一旦确定了类型，就不可以再更改：

```rust
let identy = |x| x;

let s = identy(String::from("hello"));
let n = identy(5);     // 出错，因为前面已经将类型 string 锁定在闭包中了。
```


通过 mutable 引用来捕获变量时需要注意：

```rust
let mut list = vec![1, 2, 3];
let mut borrow_mutably = || list.push(7);   // 闭包进行 mutable 引用

// 下面这一行会出错，因为 mutable 引用在闭包定义和使用期间一直有效，期间不允许其他引用存在
println!("before calling closure: {:?}", list);

borrow_mutably();

// 下面这一行不会出错
println!("after calling closure: {:?}", list);
```


通过 move 来捕获变量，多线程中会用到：

```rust
use std::thread;

fn main() {
    let list = vec![1, 2, 3];
    println!("Before defining closure: {:?}", list);

    thread::spawn(move || println!("From thread: {:?}", list))
        .join()
        .unwrap();
}
```


#### 闭包的 trait

有 3 个 trait：

- `FnOnce` ：所有闭包都需要实现这个。表示闭包可以被调用一次。
- `FnMut` ：不会将捕获到的值 move 到闭包之外，但是可能会改变捕获到的值
- `Fn` ：不会将捕获到的值 move 到之外，也不会改变捕获到的值。

三个 trait 的层级关系：`Fn` 需要 `FnMut` ，`FnMut` 需要 `FnOnce` 。所有闭包默认实现了 `FnOnce` ，这是最弱的 trait

如果一个闭包会将其捕获的变量 move 到闭包之外，那么它只能实现 `FnOnce` 

闭包的类型约束形式如下：

```rust
fn xxx<F>(f: F) 
where
    // 闭包只能被调用一次；无参数，且返回类型为 i32
    F: FnOnce() -> i32
{}
```

在参数列表前面使用 `move` 关键字，可以将变量 move 到闭包中。

#### 常用的函数

- `unwrap_or_else` ：是 `Option<T>` 对象的方法。如果是空，就使用闭包来生成一个值，如果不为空，就返回对应的值。


### 迭代器

迭代器是 lazy 的。

迭代器的 trait 定义：

```rust
pub trait Iterator {
    type Item;    // 一个关联类型
    fn next(&mut self) -> Option<Self::Item>;
}
```

几种创建迭代器的方法：

- `iter()` ：所有权是原数组，可以获取每个元素的 immutable 引用
- `into_iter()` ：将值 move 到 iter 中了，所有权变成了 iter
- `iter_mut()` ：所有权仍然是原数组，可以修改每个元素，也就是 mutable 引用


#### 消耗掉迭代器

一些方法可以消耗掉迭代器：

```rust
fn iterator_sum() {
    let v1 = vec![1, 2, 3];
    let v1_iter = v1.iter();
    let total: i32 = v1_iter.sum();
    // 在此之后，迭代器不可用，因为 iter 是以 move 形式传入 sum 的
}
```


#### 产生新的迭代器

一些方法可以消耗原迭代器，并产生新的迭代器：

```rust
let v1: Vec<i32> = vec![1, 2, 3];
v1.iter().map(|x| x + 1);
```

可以使用 `collect()` 方法将 iter 转换为一个集合。`collect` 方法非常强大，需要手动指出生成的类型：

```rust
let v1: Vec<_> = vec![1, 2, 3]; 
let v2: Vec<_>  = v1.iter().map(|x| x + 1).collect();
```



[[rust/智能指针]]

[[rust/unsafe]]

### newtype

最简单的实践：

```rust
struct MyVec(Vec<String>);

impl fmt::Display for MyVec {}
```

由于 rust 不允许为外部类型实现外部 trait，因此这种包装是有用的。


### 动态大小的类型

只有在运行时才知道具体大小的类型。

默认的范型类似都是编译时大小已知的，他们默认符合 `Sized` 这个 trait。

如果允许接受编译时大小不可知的类型 DST(dynamically sized type)，那么可以如下（一定要是引用类型）：

```rust
fn foo<T: ?Sized>(t: &T) {}
```


### 函数指针

可以将函数作为参数。函数指针默认实现了所有的 `Fn, FnMut, FnOnce` trait，因此需要闭包作为参数的地方，都可以用函数指针代替。

一种用法：

```rust
enum Status {
    Value(u32),
    Stop,
}

let list_of_status: Vec<Status> = (0u32..20).map(Status::Value).collect();
```


返回闭包：通过如下方法，可以返回一个闭包：

```rust
fn returns_closure() -> Box<dyn Fn(i32) -> i32> {
    Box::new(|x| x + 1)
}
```


[[rust/宏]]