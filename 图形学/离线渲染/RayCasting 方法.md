

#### 什么是光线Ray Casting
Ray Casting 是光线追踪的一种方法
Ray Casting 的基本思想是：

- 从眼睛向画面中的一个像素投射出一根射线；
- 延伸射线，判断射线找到射线和物体相交的交点；
- 对该交点进行着色（Lambert 着色，Blinn-Phong着色）

![[图形学/离线渲染/_attachments/1667212802.157745_image.png | 597]]


#### Whitted-Style Ray Tracing
> 这种方法是 Whitted 发明的


这是一种简单的递归的 Ray Casting 方法
基本思路是：

- 从眼睛发出的射线会在场景中弹射，与物体形成多个交点，每个交点都会对像素的颜色值做出共享
- 每一个点接受到的能量由两部分组成：
   - 来自直接光源的光照
   - 由后续路径提供

![[图形学/离线渲染/_attachments/1667212802.282826_image.png | 680]]

