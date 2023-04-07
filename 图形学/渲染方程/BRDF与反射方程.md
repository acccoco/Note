
## BRDF

BRDF 是出射 Radiance 和入射 Irradiance 的比值。

以 $\omega_i$ 方向入射的光线，经过反射，可以从半球空间中任何方向射出；入射的能量 Irradiance 为：

$$
dE(p,\ \omega_i) = L_i(p,\ \omega_i) \cos \theta_i d\omega_i
$$

从 $\omega_o$ 方向出射的光线，其能量来源是半球空间所有方向的入射光线。现在仅考虑从 $\omega_i$ 入射的光线，它对从 $\omega_o$ 方向出射光线的能量贡献，这就是 BRDF。

$$
f_r(p,\ \omega_o,\ \omega_i) 
= \frac{dL_o(p,\ \omega_o)}{dE(p,\ \omega_i)}
= \frac{dL_o(p,\ \omega_o)}{L_i(p,\ \omega_i)\cos\theta_id\omega_i}
$$

基于物理的双向反射分布函数具有以下两个特性：

1. $f_r(p,\ \omega_o,\ \omega_i) = f_r(p,\ \omega_i,\ \omega_o)$ 
2. 能量守恒：$\int_{H^2}f_r(p,\ \omega_o,\ \omega_i)\cos\theta_i d\omega_i \le 1$ 。也就是出射能量不能超过入射能量。

> 其他的类似的函数：
> - BRDF：reflectance，入射光线和出射光线都位于一个像素的范围内。
> - BSDF：scatter，出射光线距离入射光线可以较远。


## 渲染方程

根据 BRDF 的定义很容易得到反射方程：（反射光线的能量来自于各个方向的入射光线）

$$
L_o(p,\ \omega_o) 
= \int_{H^2}f_r(p,\ \omega_o,\ \omega_i) L_i(p,\ \omega_i)\cos\theta_i d\omega_i
$$

其中：$L_i(p,\ \omega_i)\cos\theta_i d\omega_i$ 表示某个方向的入射光线的能量贡献 $E(p,\ \omega_i)$ 

在反射方程的基础上加上自发光项，就得到了渲染方程：

$$
\underset{\color{red}{出射光}}{\underline{L_o(p,\omega_o)}}
= \underset{\color{red}{自发光项}}{\underline{L_e(p, \omega_o)}} 
+ 
\underset{\color{red}{反射项}}{\underline{\int_{\Omega^+}L_i(p, \omega_i)f_r(p, \omega_i, \omega_o)(n\cdot \omega_i)d\omega_i}}
$$

## 渲染方程的求解

按照能量来源的不同，渲染方程可以写作如下形式：

$$
L_o = 自发光 + 直接光项 + 间接光项
$$

![[图形学/渲染方程/_attachments/Pasted image 20230402165316.png | 300]]

在上图中，$L_1$ 就是自发光项；$L_2$ 对应直接光照；$L_3$ 对应间接光照

光栅化方法可以处理「自发光项」和「直接光照」，不好处理「间接光照」。


## 参考

- pbr-book: surface reflection. [https://www.pbr-book.org/3ed-2018/Color_and_Radiometry/Surface_Reflection](https://www.pbr-book.org/3ed-2018/Color_and_Radiometry/Surface_Reflection)

