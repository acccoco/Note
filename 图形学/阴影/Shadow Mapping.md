
### shadow map
什么是阴影：可以被 camera 看见，无直接光照照射的就是阴影。
![[图形学/阴影/_attachments/u5470a91d_Tav.png | 238]]

「shadow map」中存放的是场景到光源的**深度**信息：
![[图形学/阴影/_attachments/u77a9b0b1_Pasted Graphic 1.png | 309]]

例如：
![[图形学/阴影/_attachments/u106c85ed_scene.png | 363]]


### 自遮挡
自遮挡会让地面出现很多的条纹：
![[图形学/阴影/_attachments/u7578f8d0_image.png | 236]]

自遮挡出现的原因：「shadow map」的分辨率是有限的。解决办法是，使用 bias。
未使用 bias，自遮挡的原因：
![[图形学/阴影/_attachments/u56d8e57f_directional light.png | 337]]
使用 bais 后：
![[图形学/阴影/_attachments/u894e3de2_image.png | 252]]

bias 值应该是多少？需要考虑这几个因素：

- 「shadow map」的 texel 在「world space」中对应的大小
- 物体表面法线方向，光照方向

bias 的种类：

- depth bias：沿光照方向移动物体（大小可以固定，也可以基于物体的斜率来计算）
- normal bias：沿着物体法线方向移动物体

一般同时使用上面两种，效果较好。

下图是 normal-bias 的示意图：
![[图形学/阴影/_attachments/u4c87d019_depth ilue D.png | 533]]
说明：

- 在生成「shadow map」时，让 object 的位置沿着法线方向移动一段距离
- `bias_base`与「shadow map」的 texel 在「world space」中的大小有关。
   - 对于 directional light，每个 texel 的大小时相同的，仅与近平面的大小有关


:::danger
解决自遮挡还有一种方法：shadow map 中记录物体背面的深度值，这样物体的正面就不会有条纹了，不过背面仍然会有条纹。
改进方法是：渲染两次，第一次记录物体正面的深度值，第二次记录背面的深度值，最后求平均。
这种方法比 bias 需要更多的计算量。
:::


### 阴影悬浮
为了解决自遮挡问题，为「shadow map」添加了 bias，这又会引入新的问题：阴影悬浮。
![[图形学/阴影/_attachments/ucab10f2f_image.png | 367]]

产生原因：
![[图形学/阴影/_attachments/ue50a46aa_Pasted Graphic 6.png | 300]]


### 阴影锯齿
可以看到，阴影边缘有明显的锯齿：
![[图形学/阴影/_attachments/u092dcaac_image.png | 354]]

这是因为「shadow map」的分辨率是有限的，一定会出现场景中的多个像素对应「shadow map」中一个像素的情况。

解决办法：filter（PCF），cascade（CSM）



### 实现效果

1. 以点光源为中心，记录物体到点光源的**距离**，作为 cube map：

![[图形学/阴影/_attachments/uc557a257_image.png | 442]]

2. 仅计算某个朝向中物体到点光源的深度，作为 texture 2d：

![[图形学/阴影/_attachments/ub79f13ae_image.png | 293]]


### 参考
- [opengl tutorual shadow mapping](https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/)
- [cat like coding - unity rendering](https://catlikecoding.com/unity/tutorials/rendering/part-7/#1)
