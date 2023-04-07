### unsafe

unsafe 仍然有 borrow checker，并不等于裸奔。

unsafe 允许做以下的事情：

1. [[#对原始指针解引用]]
2. [[#调用 unsafe 函数]]
3. [[#访问及修改可变静态变量]]
4. 实现 unsafe trait
5. 访问 Union 中的字段


#### 对原始指针解引用

原始指针就像 C 中的指针那样，签名如下：`*const T` 和 `*mut T` 。可变和不可变的原始指针，对应可变引用和不可变引用。

为什么对原始指针解引用是不安全的：因为无法保证指针是有效的，无法保证有无多个可变引用。


```rust
fn main()
{
    let mut num = 5;

    let r1 = &num as *const i32;
    let r2 = &mut num as *mut i32;

    unsafe {
        println!("r1 is: {}", *r1);
        println!("r2 is: {}", *r2);
    }
}
```

#### 调用 unsafe 函数

rust 的 borrow checker 不允许同时存在多个可变引用。

我们想要在同一个 slice 的不同部分创建多个可变引用，这些部分不会互相重叠，这种方式是安全的，但是编译器理解不了。使用 unsafe 可以帮助编译器理解：


下面的代码，将 unsafe 的函数调用封装在了 safe 的函数中。

```rust
fn split_at_mut(values: &mut [i32], mid: usize) -> (&mut [i32], &mut [i32])
{
    let len = values.len();
    let ptr = values.as_mut_ptr();

    assert!(mid <= len);

    unsafe {
        (
            slice::from_raw_parts_mut(ptr, mid),
            slice::from_raw_parts_mut(ptr.add(mid), len - mid)
        )
    }
}
```


调用其他语言的函数：

```rust
extern "C" {
    fn abs(input: i32) -> i32;
}

fn main() {
    unsage {
        println!("xxx: {}", abs(-3));
    }
}
```


#### 访问及修改可变静态变量

可变静态变量是不安全的，访问和修改都需要使用 `unsafe` 。（例如：如果多个线程同时修改。）

```rust
static mut COUNTER: u32 = 0;

fn add_to_count(inc: u32) {
    unsafe {
        COUNTER += inc;
    }
}

fn main() {
    add_to_count(3);

    unsafe {
        println!("COUNTER: {}", COUNTER);
    }
}
```

> [!note] 注：静态变量的生命期是 `'static` 
