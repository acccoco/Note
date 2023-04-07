
### IBL
考虑 GGX 形式的反射方程：
![[图形学/_attachments/ud5955f27_Pasted Graphic 5.png | 463]]

如果 $L_i$ 是由图片提供的，那么就称这种环境光照是基于图片的环境光照 IBL。


### diffuse 部分
从上面的表达式可以看出，漫反射部分就是对 $L_i$ 在整个半球上进行平均。
$k_d$ 这个系数可以根据 Fresnel 方程计算得到。
> 微表面模型只考虑 specular 反射，因此只和 Fresnel 中反射的能量有关。
> 折射的能量可以视为 diffuse 的能量来源。



### specular：split sum approximate
光源是使用「立方体贴图」描述的环境光照，如何计算反射方程。
先只考虑反射方程中的 shading 部分，不考虑 shadow 部分：
![[图形学/_attachments/uca17c7b3_Pasted Graphic.png | 479]]
可以用「Monte Carlo」方法来计算这个积分，不过仍然需要大量的样本。

现在考虑反射方程中的 DFG 项：
![[图形学/_attachments/u1932b43e_限smooth.png | 430]]

可以使用约等式，得到：
![[图形学/_attachments/ue46409b3_J Lifr tocei dlul ＞.png | 345]]

根据上述表达式，反射方程由两部分组成：

1. 在 BRDF 的 support 范围内对入射 Radiance 进行平均，根据不同的「粗糙度」，在不同模糊程度的 Radiance 图之间进行插值即可。
2. 在整个半球上单独对 BRDF 进行积分

使用 Schlick 形式的 Fresnel 项，可以得到如下的 BRDF 积分项：
![[图形学/_attachments/ubf86e211_Fo.png | 541]]
注：上述积分的预计算在法线 $n$ 的 $tangent$ 空间中进行，只需要知道 $n\cdot v$ 即可。

预计算得到的 BRDF 积分图如下所示：
![[图形学/_attachments/u4d5aea5f_0.0.png | 237]]
其中：分别用 $R$ 通道和 $G$ 通道存储两个积分值。


### unreal4 的 split sum approximate
**对环境光照进行平均处理**：
根据反射波瓣的图可知，在计算 $L_o(v)$  的时候，需要的是以反射方向 $r$ （观察方向 $v$  和反射方向 $r$ 关于法线 $n$ 对称）为中心的光照信息。

Unreal 首先根据反射方向 $r$ 得到法线方向 $n$ 和观察方向 $v$ ，假定：
$$r = n = v$$

然后通过 GGX 重要性采样得到半程向量 $h$ ，再计算出光线方向$l$ ：
![[图形学/_attachments/u63ecdaaa_R=N=V.png | 246]]
计算过程如下：
![[图形学/_attachments/ue57dec2f_Jpfr Li dwi.png | 404]]
> 为什么要使用 GGX 重要性采样：这里的重要性采样并不是为了做「Monte Carlo」积分，而是为了得到以反射方向 $r$ 为中心的大小合适的 support（support 大小和粗糙度有关）。


在实际实现中，Unreal 还使用$n \cdot l$ 作为加权，原文说可以得到更好的效果：
![[图形学/_attachments/u656c53e7_Pasted Graphic 4.png | 284]]

具体的代码如下：
![[图形学/_attachments/uf643f0ac_image.png | 604]]

实现注意：

- 生成的结果是「立方体贴图」，使用反射方向$r$ 进行查询
- 不同的粗糙度对应不同的 mipmap 级别
- 查询时会根据粗糙度在不同 mipmap 之间进行插值，还会根据反射方向 $r$ 在 mipmap 内进行插值

**对 BRDF 进行积分**：
这个积分没什么好说的，重要性采样 + 拟蒙特卡洛方法（低差异序列）即可。
实现的代码为：（积分是在法线$n$ 的切线空间中进行的）
（代码中的表达式是经过 GGX 重要性采样的 pdf 约分的，所以没有 NDF 项了）
![[图形学/_attachments/u58820395_image.png | 430]]


### 附：GGX 重要性采样的代码
glsl 代码。
其中：`Xi`是均匀分布的随机变量或者低差异序列值；
![[图形学/_attachments/u36358d25_image.png | 506]]


### IBL 整体示意图
注：更正一下，下图的 Irradiance 应该用字母 E 来表示。
![[图形学/_attachments/u2584fffe_en wediance mop.png | 549]]


### 参考

- Learn OpenGL：[https://learnopengl.com/PBR/IBL/Specular-IBL](https://learnopengl.com/PBR/IBL/Specular-IBL)
- Real Shading in Unreal Engine 4

