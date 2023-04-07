
### Cook-Torrance 模型
实时渲染管线使用的一种 BRDF 模型
![[图形学/表面模型/_attachments/1619508092032-9054d2df-d6c4-4b55-aafe-153377f02491.png | 300]]
$$f_r = k_df_{lambert} + k_sf_{cook-torrance}$$

其中：

- $k_d$  和 $k_s$  分别表示入射光线被折射和被反射能量所占的比率（折射部分贡献的是漫反射；根据 Fresnel 计算得到）
- $f_{lambert}$  是 Lambertian 漫反射，$f_{lambert} = \frac{c}{\pi}$  
- 镜面反射的双向反射分布函数为：$f_{cook-torrance} = \frac{DFG}{4(\omega_o \cdot n)(\omega_i \cdot n)}$ 

最终的渲染方程为：

$$
L_o(p, \omega_o) 
= \int_{\Omega}[k_d \frac{c}{\pi} + \frac{DFG}{4(\omega_o\cdot n)(\omega_i\cdot n)}]L_i(p, \omega_i)(n\cdot \omega_i) d\omega
$$


### 法线分布函数
使用 Trowbridge-Reitz GGX
$$D(h)
= \frac{\alpha^2}
{\pi((n\cdot h)^2(\alpha^2 - 1) + 1)^2} $$
![[图形学/表面模型/_attachments/u5edd5625_image.png | 318]]
注：NDF 是一个密度函数，因此函数值可以超过 1


### 几何函数
几何函数描述了微平面相互遮蔽的情况：
![[图形学/表面模型/_attachments/1619522371165-09161238-15e1-4d0c-909c-5da9dff4382a.png | 400]]

几何函数使用 GGX 和 Schlick-Beckmann 的结合体 Schlick-GGX，其中，$k = \frac{\alpha}{2}$ ：
$$G(n, v, k) = \frac{n\cdot v}{(n\cdot v)(1-k) + k}$$

再通过 Smith 的模型得到完整的表达式：
$$G(n,v,l,k) = G_{sub}(n,v,k)G_{sub}(n,l,k)$$

下图给出了 $G$ 在不同的观察角度 $\theta_v$ 和粗糙度相关系数 $\alpha$ 下的变化：
![[图形学/表面模型/_attachments/u8719f745_image.png | 569]]

### Fresnel
Fresnel 使用 Schlick 的近似，表达式为：
$$F(v,\ h) = F_0 + (1 - F_0)(1 - (v \cdot h))^5$$

图标如下：

![[图形学/表面模型/_attachments/uf5c1ae22_image.png | 319]]


### BRDF 的形状
绘制出 $DFG$  的图标：（观察方向 $v$ 和法线 $n$ 的夹角为 $40$ 度）
![[图形学/表面模型/_attachments/ue98aacbf_image.png | 498]]

其中：横轴表示光线方向 $l$ 和观察方向的反射方向 $r$ 之间的夹角。

可以看出：DFG 的形状主要和


### 反射波瓣的形状
GGX 形式的反射方程的高光部分可以化简为以下形式：
$$L_o(v) = \frac{1}{4|n \cdot v|} \int_{\Omega} L_i(l)\ D(h)\ F(v,\ h)\ G(v,\ l) d\omega_l$$

将其中的 $DFG$  部分绘制出来，根据粗糙度的不同，得到如下的图像（观察角度固定为 $\$ $\phi=180,\ \varphi=45$ ）：
![[图形学/表面模型/_attachments/u19f33a67_Xnip2022-04-30_16-10-28.jpg | 220]]

注：波瓣上任意一个点与原点的连线构成的向量，其方向表示光线 $l$ 的方向，其大小表示 $DFG$  的大小。

反射波瓣的绘制代码：[https://github.com/acccoco/jupyter](https://github.com/acccoco/jupyter)


### 参考：

- https://graphicrants.blogspot.com/2013/08/specular-brdf-reference.html
