物体表面的示意图如下：

![[图形学/表面模型/_attachments/ucca3c52d_N veflett.png | 196]]

其中：$\vec{l}$  是光照方向，$\vec{n}$ 是物体法线，$\vec{r}$ 是光线的反射方向，$\vec{v}$ 是视线方向，$\vec{h}$ 是半程向量（是 $\vec{l}$ 和 $\vec{v}$  的对称线。）


#### Phong 着色

![[图形学/表面模型/_attachments/u30a007af_Amblent.png | 454]]

![[图形学/表面模型/_attachments/u0a0cbcf2_ambiert coe ficient.png | 466]]


其中，光滑程度越高，高光部分越小，高光越尖锐：

![[图形学/表面模型/_attachments/u1d383c68_90.png | 463]]


#### Blinn-Phong 着色

phong 着色的问题：

![[图形学/表面模型/_attachments/rH2do_Pasted Graphic 2.png | 202]]

由于 $\vec{v} \cdot \vec{r} < 0$ ，因此 specular 项是 $0$ 。

Blinn-Phong 和 Phong 着色的区别在于 specular 的计算：

$$L_s = k_s(I/r^2)\max(0,\ \vec{n}\cdot \vec{h})^p$$

其中：$\vec{h}$ 是半程向量（是 $\vec{l}$ 和 $\vec{v}$ 的中线）

这样，specular 项就始终不会为 $0$ 了。

![[图形学/表面模型/_attachments/u41c13156_image.png | 492]]
