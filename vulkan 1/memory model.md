---
tags:
    - vulkan
---
  

**vulkan memory model**

vulkan memory model 的出发点，和 C++ memory model 的差异是什么：

[Khronos Blog - The Khronos Group Inc](https://www.khronos.org/blog/vulkan-has-just-become-the-worlds-first-graphics-api-with-a-formal-memory-model.-so-what-is-a-memory-model-and-why-should-i-care)

-------------------------------------------------------

下面这篇文章讲了详细的差异，C++ 一些操作的映射关系，以及出发点：

[Khronos Blog - The Khronos Group Inc](https://www.khronos.org/blog/comparing-the-vulkan-spir-v-memory-model-to-cs#)

内存：**memory location** + **reference**，C++ 中的变量等于两者加起来。

-   memory location 就是实际内存
-   reference 是用于访问内存的 variable 或者 handle

**cache maintaince 的操作：**

**available** 可以这样理解：写的一方将缓存 flush 到 main memory

**visible** 可以这样理解：读的一方处理完所有的 invalidate，现在看到的都是最新的。

（bypass：不走缓存，直接从 main memory 读取最新的）

出发点：

C++ 最开始，系统是缓存一致性的，因此没有暴露出 cache maintenance 操作；

vulkan/spir-v 一开始就运行在并行化的系统上，因此需要暴露出 cache maintenance 的操作。

对应关系：

eg. std::momory_order_release = MakeAvailable + Release 

**Alias**：这是个什么东西？？

**storage class**：同步指令中可以指定 storage class，不属于那些类型的内存访问操作不会收到 barrier 的影响。

（也就是更进一步地划分了内存访问的类型）

为什么要区分 storage class，因为不同的资源访问方式不同。例如一些资源的访问：linear；另一些资源的访问：quad。

不同的资源有不同的 cache，以及不同的 access hardware

不同类型 barrier 管不同的 storage class，这些 barrier 之间的交互用 **inter-thread happens before** 来描述。。。

**memory and execution Scope**：

GPU 上有大量的 thread 可以并行，在所有 thread 之间进行同步会非常消耗性能。

通常的做法是在较小的 group of threads 之间进行同步。

scope 的定义可以是嵌套的，最小单元是 thread。

同步指令（atomics，memory barrier）会带有 scope 这个操作数，用来表示这个同步操作是在多大的范围内进行的。

vulkan 的 scoped modification order 对应着 C++ 的 total modification order

**Memory domain：**

GPU 上有大量的执行单元，有复杂的缓存层级。

memory domain operation 和 availablility 操作一样，是用来管理 cache 的。

availability 和 visibility 操作是用于 memory domain 只能的；memory domain 操作是用于 memory domain 之间的。

memory domain 的例子：host；device；每种着色器类型都有。

**Private Memory Access**

只有 non-private access 的结果才会被其他线程影响或是影响其他线程。

**Control Barriers**

同一个执行单元中的不同的 thread，如果一个或多个线程 block 了，其他线程是否会被阻塞？control barrier 就是用来控制这个的。

hint：多个线程共用一个 PC。