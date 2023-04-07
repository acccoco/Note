---
tags:
    - 渲染路径
---


### forawrd+ 的思路

按照 framebuffer 的 tile，将场景划分为一个个 frustum。计算得到每个 frustum 内的有效光源数量，减少光源数量的 overdraw。


### forward+

相当于 tiled + forward

阶段：

- 预计算阶段：预计算每个 tile 对应的 frustum 的侧面的平面参数，一个 thread 负责一个 tile
- depth prepass：记录场景深度信息，可以有效减少最终着色阶段的 overdraw
- light culling：将 screen space 划分为均匀的网格，能够影响到每个 tile 的光源。这一步在 compute shader 中完成，主要是 tile frustum 与 light volume 的求交
- final shading：正常的 forward 方法

注：光源必须以 linear 的形式存放，方便在 shader 中采样

如何理解：

- depth prepass 可以减少 pixel 的 overdraw
- light culling 可以减少 light 的 overdraw

优先：

- memory traffic 更少
- 可以使用多种的 shading model


### 实现细节

**平面的表示方法**

使用平面的法向量 $N$ 以及原点到平面的有向距离 $d$ 来表示平面：

设 $P$ 是平面上一点，$O$ 是原点，则有：

$$\vec{N} \cdot \vec{OP} = d$$


**frustum 的表示方法**

在 view space 中描述 frustum：

- 近平面与远平面都是平行于坐标轴平面的，只需要平面到原点的距离这一个参数即可描述
- 四个侧面使用上述的表示方法来描述


**确定 frustum 的近平面和远平面**

需要首先渲染一遍场景，得到屏幕空间的深度信息，分别以最小深度和最大深度对应的平面作为近平面和远平面。

例如：

![[图形引擎/渲染路径/_attachments/Pasted image 20221106162144.png | 500]]


**判断 frustum 与球体是否相交**

场景中的点光源可以视为球体，light cull pass 会找到每个 frustum 中实际有效的光源，并记录下来。

如果光源的包围球体和 frustum 发生相交，那么该光源就是 tile 的有效光源。

相交的示意图：

![[图形引擎/渲染路径/_attachments/Pasted image 20221106164841.png | 320]]


> [!note] 如何判定
> 发生相交不好判断，没有发生相交很好判断：
> 
> - 如果球体完全位于 frustum 之外，那么就**没有**发生相交。
> - 也就是说：只要球体位于==**任意**==一个平面的外侧，那么就没有发生相交。

只要满足以下表达式，那么球体就位于平面的外侧：

$$
\vec{OC} \cdot \vec{N} - d > R
$$

其中：$N$ 是平面的法向量，$d$ 是原点到平面的有向距离，$C$ 是球心，$R$ 是球的半径。
![[图形引擎/渲染路径/_attachments/Pasted image 20221106165952.png |200]]

**如何存放每个 tile 的光源列表**

使用如下的结构来存放：

- `Light List` 是 `struct Light` 的数组，存放这场景中所有光源的详细信息。通过 SSBO 的形式在着色器中访问。
- `Light Index List` 是 `uint` 的数组，每个 tile 对应一段连续的空间，每个元素都是 `Light List` 的索引。
- `Light Grid` 是一个二维矩阵，每个矩阵元素由两个部分组成：`Light Index List` 的起始位置 `offset` 以及 tile 在 `Light Index List` 对应的长度 `count` 。

![[图形引擎/渲染路径/_attachments/Light-List-Data-Structure.png | 400]]

为什么要使用这样一个数据结构？因为 light cull pass 是在 compute shader 中进行的，各个 workgroup 只有在向 `Light Index List` 中申请空间的时候需要进行同步。

可以用一个原子计数器（SSBO + atomic operator 实现）来完成 workgroup 之间的同步操作。计数器中存放的是 `Light Index List` 中已经分配出去的元素个数。


### 常见问题

在物体的边缘位置，frustum 的深度范围会非常大：

![[图形引擎/渲染路径/_attachments/Pasted image 20221106171634.png | 200]]

这回造成对应的 tile 中 light 的数量突然增多，运算量增大。

> [!note] 
> 或许可以通过两次深度 pass 来缓解这个问题：第一次使用 less，第二次使用 greate。


### 实现效果

光源分布是均匀的，间隔固定，颜色随机，总光源数 4096

![[图形引擎/渲染路径/_attachments/Pasted image 20221106172612.png | 400]]


### 参考

- [渲染路径（Rendering Path）：Forward、Deferred、Light-PrePass、Tiled、Clustered](https://www.cnblogs.com/KillerAery/p/15962110.html) 工业界常用渲染路径的比较
- [[图形引擎/渲染路径/_attachments/forward_plus.pdf | Takahiro Harada - forward plus]] ：forward+ 的论文
- [Forward vs Deferred vs Forward+ Rendering with DirectX 11](https://www.3dgep.com/forward-plus/) ：这是本文的主要参考
- [github - vulkan forward plus renderer](https://github.com/WindyDarian/Vulkan-Forward-Plus-Renderer) github 上的一个 vulkan 实现
