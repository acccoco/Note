---
tags:
    - gpu
---

访存需要关注两个指标：latency，bandwidth

-   因为 GPU 是异步任务且任务执行时间较长（ms 级别），因此 latency 可以通过切换线程和改变指令执行顺序来缓解
-   cache hierarchy 可以有效解决 latency 和 bandwidth

GPU 的访存延迟

访存大概需要 1000 个时钟周期，为了不浪费这些时间，multiprocessor scheduler 会将当前 warp 切换掉，让别的 warp 运行。

MP 上 active warp 才能做到无缝切换，active 是指在 register file 中有分配 register。MP 上的 active warp 当然越多越好。当前 \#active warp / \#max warp 叫做 occupancy，occupancy 一般来说越大越好。

occupancy 取决于 program 的资源占用情况，MP 的 register file 的大小，texture samplers，l1 cache，interpolants 等。

occupancy 高可能会起到反作用：如果 program 内存访问频繁，可能导致 cache 不够用，miss 很多。

CPU 的回读延迟

CPU 从 GPU 读取数据，延迟很高。

因为 GPU 需要将 data flush 到其显存，再传送给 CPU。

内存架构和总线

GPU 专用的内存叫做 video memory（显存）。

渲染所需的资源可以存放在 video memory 上，也可以存放在 system memory 上。

video memory 的 bandwidth 很快，system memory 的访问需要通过 PCIe 进行，bandwidth 较慢（大约 10 倍差距）

以下资源的存放位置：

-   textures，render target：video memory
-   static vertex，static index buffer：video memory。例如只需要通过 matrix 来改变的几何。
-   dynamic vertex，dynamic index buffer：system memory。需要每一帧都改变的几何。

------------------------------------------------

ROP: raster operation units，用于混合的单元。