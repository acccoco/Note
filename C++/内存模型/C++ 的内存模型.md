这篇文章参考 preshing 的一系列 blog（2011 - 2015）：
https://preshing.com/archives/


### memory reorder
memory reorder 的来源，可能是：

- 指令执行顺序发生改变（编译器，CPU 运行时）
- 由于各种缓存机制（store buffer，invalidation queue），导致读到了旧数据

memory reoder 的原则：
![[C++/内存模型/_attachments/The_cardinal_rule_of_memory_reordering,_which_universally_followed_by_compiler.png|600]]



只有 lock-free 编程才需要关注内存模型。
Acquire - Release 是最常用的一种模型，在此之前，先回顾一下 memory barrier


### memory barrier

之前的文章介绍了 memory barrier 的原理：
[内存屏障和缓存一致性](https://www.yuque.com/charvl/yd71bq/hmgzou?view=doc_embed)

不去考虑实现细节，可以抽象出四类 memory barrier：

![[C++/内存模型/_attachments/image.png]]


以 `#LoadLoad`为例，介绍其作用：`#LoadLoad`不允许「其前方的 load」和「其后方的 load」发生 reordering。

如果不使用 memory barrier，以下代码，在某些平台可能会出现意想不到的结果：
```cpp
x = y = 0;
// thread 1
x = 1;
r1 = y;
// thread 2
y = 1;
r2 = x;
```
由于内存 reorder，因此最终结果有可能是： `r1 = r2 = 0`。
以下是测试代码：
```cpp
#include <array>
#include <atomic>
#include <vector>
#include <thread>
#include <random>
#include <utility>
#include <iostream>
#include <semaphore>


/**
 * 这个例子可以检测出内存乱序。
 * 在 M1 Mac 中，大概有 10% 的几率内存乱序。
 */


int main()
{
    // semaphore
    std::binary_semaphore      sem1{0}, sem2{0};
    std::counting_semaphore<2> sem{0};

    // random num
    std::random_device                 rd;
    std::mt19937                       engine(rd());
    std::uniform_int_distribution<int> dist(0, std::numeric_limits<int>::max());

    int x, y;
    int r1, r2;

    auto f1 = [&]() {
        for (;;)
        {
            sem1.acquire();
            while (dist(engine) % 8 != 0)
            {}

            x = 1;
            asm volatile("" ::: "memory");    // prevent compiler reordering
            r1 = y;

            sem.release();
        }
    };


    auto f2 = [&]() {
        for (;;)
        {
            sem2.acquire();
            while (dist(engine) % 8 != 0)
                ;

            y = 1;
            asm volatile("" ::: "memory");    // prevent compiler reordering
            r2 = x;

            sem.release();
        }
    };

    std::thread t1(f1);
    std::thread t2(f2);

    int detected = 0;
    for (int iter = 0;; ++iter)
    {
        x = 0;
        y = 0;

        sem1.release();
        sem2.release();
        // thread run
        sem.acquire();
        sem.acquire();

        if (r1 == 0 && r2 == 0)
        {
            ++detected;
            std::cout << detected << " reorders detected after " << iter << " iterations: " << float(detected) / iter
                      << std::endl;
        }
    }
}
```


### 原子操作与非原子操作
这里只提醒一下，store 或 load 操作不一定是原子的，因为：

- 要 store 一个 64bit 的数，在 32-bits 机上，需要两个指令。
- 单个指令并不一定是原子的，例如 `mov`指令，如果数据没有**内存对齐**，就不是 atomic 的。

为了写出 portable 的代码，需要 atomic 特性的时候，应该显式指出

**原子操作的修改顺序**
C++ 的 specification 中提到，对**同一个原子变量**的修改在系统的其他部分看起来是有序的。
这一条规则，现在看来没什么太大用处，因为我们更关注对**不同原子变量**操作的顺序。

![Modification order.png](C++/内存模型/_attachments/Modification_order.png)



多线程之间存在两种关系：竞争，合作。Acquire - Release 就是用于「合作」的。
### Acquire，Release 语义
Acquire 语义：如果一个 load 操作具有 Acquire 语义，那么可以保证其后方的 load 或 store 操作无法 reorder 到这个 load-acquire 操作前方。
Release 类似。

Acquire 和 Release 可以通过 memory barrier 来实现：

![acqure semantics.png](C++/内存模型/_attachments/acqure_semantics.png)

要实现 Acquire 语义，只需要把 `#LoadLoad`和 `LoadStore`放在 load 操作后方即可。

在 C++ 中，有以下几种方法可以实现 Acquire-Release 语义：

- 使用 `atomic_thread_fence(memory_order_release)`
- 使用 `atomic`变量，并在 operation 中指定 memory order
- 使用 mutex，lock 操作对应着 acquire；unlock 对应着 release

注：acquire 和 release 一定要成对使用，否则就没有意义了。

#### acquire，release fence
fence 和直接使用 atomic 的 memory order，两者的效果大致相同。

例如，fence 的使用：
```cpp
// thread 1
void SendTestMessage(void* param)
{
    // Copy to shared memory using non-atomic stores.
    g_payload.tick  = clock();
    g_payload.str   = "TestMessage";
    g_payload.param = param;
    
    // Release fence.
    std::atomic_thread_fence(std::memory_order_release);

    // Perform an atomic write to indicate that the message is ready.
    g_guard.store(1, std::memory_order_relaxed);
}
// thread 2
bool TryReceiveMessage(Message& result)
{
    // Perform an atomic read to check whether the message is ready.
    int ready = g_guard.load(std::memory_order_relaxed);
    
    if (ready != 0)
    {
        // Acquire fence.
        std::atomic_thread_fence(std::memory_order_acquire);

        // Yes. Copy from shared memory using non-atomic loads.
        result.tick  = g_payload.tick;
        result.str   = g_payload.str;
        result.param = g_payload.param;
        return true;
    }
    return false;
}
```
两个线程之间建立起的 synchronizes-with 关系：
![Thread 1.png](C++/内存模型/_attachments/Thread_1.png)


有些情况下，fence 和 atomic 操作的 memory order 是不同的：

- `x.store(val, memory_order_release)`只能保证前方的 read 和 write 不能 reorder 到**这个** `store`的后方。其后方的 `store`操作，可以随意 reorder
- `atomic_thread_fence(memory_order_release)`可以保证其前方的 read 和 write 不能 reorder 到其后方的**任意** `store`之后执行。

例如，下图中的 memory order 没有任何用处：

![Singleton tmp.png](C++/内存模型/_attachments/Singleton_tmp.png)


### release-consume
consume 和 acquire 的目的都是，在线程之间安全地传递 non-atomic 信息。
consume 可以做到的，acquire 都能做到；但是有些情形下使用 consume 就够了，还可以得到更高的性能。
release-acquire 构建起的是「synchronizes-with 关系」；release-consume 构建起的是「data dependency order 关系」。

如果需要的数据 payload 和 guard 之间存在着 data dependency 的关系，可以直接使用 release-consume。

data dependency 的例子：

- 第一个指令输出一个值，第二个指令使用这个值

![1Wz.png](C++/内存模型/_attachments/1Wz.png)


- 第一个指令写入内存，第二个指令从内存中读取

![Stw.png](C++/内存模型/_attachments/Stw.png)


data dependency 可以组成 chain，data dependency-order 可以保证 chain 内的顺序，无法保证 chain 之间的顺序：
![r9, 8(r3).png](C++/内存模型/_attachments/r9,_8(r3).png)


一下是通过 release-consume 建立起「data dependency order」的例子：
```cpp
atomic<int*> Guard(nullptr);
int Payload = 0;

// thread 1
Payload = 42;
Guard.store(&Payload, memory_order_release);

// thread 2
g = Guard.load(memory_order_consume);
if (g != nullptr)
    p = *g;
```

![Asynchronous Task.png](C++/内存模型/_attachments/Asynchronous_Task.png)



使用 memory barrier，是为了得到 happens-before 的关系
### Happens-before
我们想要确保不同线程的部分操作之间存在先后关系，也就是需要「happens-before」。
acquire-release 是抽象出的实现模型，memory barrier 是具体的实现手段。
![Let A and B represent operations performed by a multithreaded process. IfA.png](C++/内存模型/_attachments/Let_A_and_B_represent_operations_performed_by_a_multithreaded_process._IfA.png)
可以建立起 happens-before 的方法：

![Happens-before.png](C++/内存模型/_attachments/Happens-before.png)


#### synchronizes-with 关系

可以通过 acquire-release 来建立起 synchronizes-with 关系。
在这种模式中，一般存在 `gurad`和 `payload`两个角色。代码如下：

```cpp
// thread 1
void SendTestMessage(void* param)
{
    // Copy to shared memory using non-atomic stores.
    g_payload.tick  = clock();
    g_payload.str   = "TestMessage";
    g_payload.param = param;
    
    // Perform an atomic write-release to indicate that the message is ready.
    g_guard.store(1, std::memory_order_release);
}
// thread 2
bool TryReceiveMessage(Message& result)
{
    // Perform an atomic read-acquire to check whether the message is ready.
    int ready = g_guard.load(std::memory_order_acquire);
    
    if (ready != 0)
    {
        // Yes. Copy from shared memory using non-atomic loads.
        result.tick  = g_payload.tick;
        result.str   = g_payload.str;
        result.param = g_payload.param;
    }
    return false;
}
```

上面的代码可以建立如下的 synchronizes-with 关系：

![image.png](C++/内存模型/_attachments/image-1.png)


acquire 应该用于消费者的一方，release 应该用于生产者的一方，而不是只看 load 和 store 操作。

例如，两个线程运行相同的代码，一个线程既是消费者，又是生产者，这个例子不容易判断哪里用 acquire，哪里用 release：

![3 fo tove对c庭 w比.png](C++/内存模型/_attachments/3_fo_tove对c庭_w比.png)

