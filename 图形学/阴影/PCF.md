
PCF：_percentage-closer filtering_


### 软阴影
阴影有「本影」和「半影」的区别，「软阴影」就是对这种现象的近似。
> 软阴影同时还可以实现阴影的**抗锯齿**。

![[图形学/阴影/_attachments/u0daca1a6_image.png | 230]]


### PCF
PCF 可以软化硬阴影的边缘，近似得到「软阴影」。

PCF 的做法：在对「shadow map」进行采样时，会同时采样邻近的像素，与 fragment 的深度值进行比较，最后对比较的结果取平均，得到一个在 $[0,\ 1]$ 范围内的值。percentage-closer filtering 因此而得名。
> percentage：实际上是 fragment 深度在区域内**排名的百分比**。
> PCF 并不是先 filter 再采样。因此无法对「shadow map」预处理以减小采样次数。
> _硬件会内置 4 sampler 的 PCF 的功能，例如 _`_sampler2DShadow()_`


![[图形学/阴影/_attachments/uaa81cf57_Pasted Graphic.png | 161]]
![[图形学/阴影/_attachments/uca55f49d_Pasted Graphic.png | 467]]


使用 PCF 的效果如图：
![[图形学/阴影/_attachments/ua5181c2a_image.png | 388]]


### PCF 改进
**减少采样次数**：
如果要进行 $4\times 4$ 的 PCF，可以不用进行 $16$ 次 sample：
第 $0$  帧采样标记为 $0$ 的像素；第 $1$ 帧采样标记为 $1$ 的像素；
![[图形学/阴影/_attachments/u3640a620_image.png | 100]]

**使用 poisson sample**：
> poisson disc 的特点：采样点随机分布，紧密排列，任意两点的具体不会小于某个值
[poisson disc](https://www.jasondavies.com/poisson-disc/)

一种实现方法是：

- 预先计算好 poisson 的各个 sample，存放到代码中
- 渲染每个 fragment 时，**随机选择 poisson 中的几个采样点**，使用这些采样点去采样「shadow map」，并应用 PCF


### 参考
[https://developer.nvidia.com/gpugems/gpugems/part-ii-lighting-and-shadows/chapter-11-shadow-map-antialiasing](https://developer.nvidia.com/gpugems/gpugems/part-ii-lighting-and-shadows/chapter-11-shadow-map-antialiasing)

这篇文章虽然没有实践，但是很多观点具有启发性
[Chapter 8. Summed-Area Variance Shadow Maps](https://developer.nvidia.com/gpugems/gpugems3/part-ii-light-and-shadows/chapter-8-summed-area-variance-shadow-maps)

[open tutorial shadow mapping](https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/#pcf)

