
### PCSS
PCF 可以软化阴影，且阴影的模糊程度和 filter 的半径有关。PCSS 的思路是，根据实际的半影尺寸来确定 filter 的尺寸。


**半影尺寸**
软阴影和半影有关，半影的大小可以计算出来：
![[图形学/阴影/_attachments/u5d91fec4_Pasted Graphic.png | 301]]

根据上图中的相似关系，可以算出半影的宽度 $W_P$ ：
$$W_P = (D_R - D_B) \cdot W_L / D_B$$

> 实现细节：这里的 $D$  是物体在光源的「view 空间」中的**实际深度**，而不是物体到光源的距离。



**FCSS 的整体过程如下**：

1. blocker search：确定搜索范围，计算出遮挡物的平均深度 $D_B$ 
2. 计算半影尺寸 $W_P$ ，得到 PCF 的 filter 尺寸
3. 进行 PCF

**计算遮挡物的深度**：
为了计算半影尺寸，需要首先知道遮挡物的深度 $D_B$ 。PCSS 的方法是，在 shadow map 中的一定区域内搜索所有的 blocker，然后以他们的平均值作为遮挡物的深度。
![[图形学/阴影/_attachments/VSu4x_Pasted Graphic.png | 272]]

根据上图可以确定出搜索范围「blocker search size」，只有在这个范围内的才有可能遮挡住 fragment。
> 注：只考虑范围内的所有遮挡物，计算这些遮挡物的平均深度。非遮挡物不考虑。


实现的参考：
![[图形学/阴影/_attachments/ub7183707_image.png | 594]]



效果如图：
![[图形学/阴影/_attachments/u13e268eb_image.png | 420]]

> 注：
> 1. 不同的采样函数确实非常影响最终的效果。NVIDIA 推荐的泊松圆盘就好于动态生成的泊松圆盘
> 2. PCF 相比于 shadow mapping 会更容易产生自遮挡，因此可以用更大的 bias 来避免这个问题


**参考**：
[https://developer.download.nvidia.cn/whitepapers/2008/PCSS_Integration.pdf](https://developer.download.nvidia.cn/whitepapers/2008/PCSS_Integration.pdf)
[https://developer.download.nvidia.com/shaderlibrary/docs/shadow_PCSS.pdf](https://developer.download.nvidia.com/shaderlibrary/docs/shadow_PCSS.pdf)

问答社区里面 PCSS 的实现
[https://computergraphics.stackexchange.com/questions/10655/how-to-implement-pcss-correctly](https://computergraphics.stackexchange.com/questions/10655/how-to-implement-pcss-correctly)

pboechat 实现的 PCSS，还可以参考下他的项目代码
https://github.com/pboechat/PCSS

diharaw 实现的 PCSS，可以参考下他的项目代码
https://github.com/diharaw/area-light-shadows

这里有实现方法：
[Unity SRP 实战（三）PCSS 软阴影与性能优化](https://zhuanlan.zhihu.com/p/462371147?utm_medium=social&utm_oi=551847284401283072&utm_psn=1553355036897267712&utm_source=ZHShareTargetIDMore)
