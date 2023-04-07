---
tags:
    - gpu
---

**GPU - 架构 IMR 和 TBR**

一言以蔽之：

-   tile based rendering 按照 tile 来划分 framebuffer，这些 framebuffer 可以直接装进 SRAM 中（cache 中）。
-   绘制时，集中某个 tile 来进行绘制，绘制完后，再将 tile 对应的 framebuffer 放回 DRAM 中
-   imr 绘制时，framebuffer 没有被进行分割，全部放在 DRAM 中。

**IMR：immediate mode rendering**
![[-最近/_attachments/Pasted image 20221103015456.png]]
  

蓝色的是「处理过程」，灰色的是「显存」。

**TBR：tile based rendering**

TBR 是移动端的架构。
![[-最近/_attachments/Pasted image 20221103015502.png]]
  

-   需要延迟渲染的。
-   中间的灰色是 GPU 的缓存
-   下面的灰色是系统内容，没有「显存」

效果大概是这样：
![[-最近/_attachments/Pasted image 20221103015506.png]]


手绘的示意图：

![[GPU硬件/_attachments/Pasted image 20221106175157.png |400]]


**参考链接：**

[IMR, TBR, TBDR 还有GPU架构方面的一些理解 - 知乎](https://zhuanlan.zhihu.com/p/259760974)

[A look at the PowerVR graphics architecture: Tile-based rendering - Imagination](https://www.imaginationtech.com/blog/a-look-at-the-powervr-graphics-architecture-tile-based-rendering/)