CSM：cascaded shadow maps


cascade 是用于缓解阴影锯齿问题的，只能用于 **directional light** 的情形。
由于**透视投影近大远小**的特效，近处阴影会看到明显的锯齿（假设方向光自上而下照射）：
![[图形学/阴影/_attachments/u4e34d1b4_ShadMapFrustumDiagram.svg | 402]]

思路：根据离摄像机的距离，将场景划分为不同的区域，生成不同的「shadow map」，如下图所示：
![[图形学/阴影/_attachments/u053f55b4_ShadMapCascadeDiagram.svg | 241]]
![[图形学/阴影/_attachments/u78e81f42_Pasted Graphic.png | 251]]

**一种实现方法**：
首先将 view frustum 划分为不同的区域，然后为每个区域创建包围盒，包围盒即为对应 level 的 light frustum
![[图形学/阴影/_attachments/u5a62c92a_Mew frustum.jpg | 240]]
如何划分 view frustum：需要计算，确保每个 level 在「screen space」中对应的锯齿大小在某个误差范围内。　

**CSM 阴影闪烁问题**：
随着观察摄像机的移动，阴影摄像机也会跟着移动，而阴影的 camera 是**连续**移动的，造成阴影的锯齿在移动：
![[图形学/阴影/_attachments/u4d49e82b_Pasted Graphic.png | 405]]

解决方法是：让阴影摄像机不再连续地移动，每次移动的距离等于 shadow map 中像素的大小。

**参考**：

- [Unity - Manual: Shadow Cascades](https://docs.unity3d.com/Manual/shadow-cascades.html)
- [nvidia cascaded shadow maps](https://developer.download.nvidia.com/SDK/10.5/opengl/src/cascaded_shadow_maps/doc/cascaded_shadow_maps.pdf)
- [Cascade Shadow Map 实现记录](https://zhuanlan.zhihu.com/p/515385379)
- [LearnOpenGL - CSM](https://learnopengl.com/Guest-Articles/2021/CSM)

