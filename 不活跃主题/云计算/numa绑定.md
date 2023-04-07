摘要
> 本文主要介绍了计算虚拟化中用到的一种技术：numa绑定。
> 本文着重介绍了什么是numa

[toc]

#### 什么是 _NUMA_
所有CPU对内存的访问都要通过北桥中的内存控制器来完成，这样的架构叫做UMA（Uniform memory access）架构
![[不活跃主题/云计算/_attachments/1600055499343-ccfb3e09-85e4-449e-b5dc-88d64ca938b1.png ]]
随着CPU核心的增多，UMA架构遇到了总线带宽问题和内存冲突等问题。因此，提出了NUMA架构（Non U M A）。将一些CPU和内存划分到一个Node中，在同一个Node中，CPU通过继承的内存控制器来进行内存访问。
![[不活跃主题/云计算/_attachments/1600055499415-e6eb32f7-8ddb-4ee1-8370-3e8ae1cf0bbe.png ]]
处于同一个Node的内存叫做CPU的本地内存，处于不同Node的内存叫做CPU的远地内存。如果CPU想要访问远地内存，就需要通过QPI（Quick Path Interconnect）总线来进行通信，这样相比于本地内存就存在着时间延迟。

#### _numa_ 绑定
很多应用都需要频繁地访问内存，比如数据库系统需要大量内存做缓存。
NUMA优化就是让CPU尽量访问本地内存。
NUMA绑定：将qemu模拟出的Node绑定在一个物理CPU上面，对应的内存也绑定在该物理CPU的本地内存上面。
