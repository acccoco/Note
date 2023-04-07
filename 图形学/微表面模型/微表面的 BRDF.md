microfect：微表面模型中最小的几何单元，是一个很小的平面
microsurface：由 microfect 组成的表面


### 法线分布函数
从统计的角度来表述微表面的朝向情况。在面积为$d A$ 的宏观表面中，法线朝向在以 $\textbf{m}$ 为中心的立体角 $d\omega_m$ 之内的 microfect 的面积为：
$$D(\textbf{m}) dAd\omega_m $$

其中：$D(\textbf{m})$ 叫做法线分布函数，是一个密度函数，单位为 $1/sr$ 。
> 比较简单的法线分布函数是一个二维的各向同性的高斯分布函数。


法线分布函数需要满足以下的条件，这样才能确保能量守恒：
从方向 $\textbf{v}$ 看过去，所有 microfect 的投影面积应该等于宏观表面的投影面积，也就是：
$$\int_{\Omega} D(\textbf{m})(\textbf{m}\cdot \textbf{v})d\omega_m  = \textbf{n}\cdot \textbf{v}$$

其中：$\textbf{n}$ 是宏观表面的法线。注意，并没有限制 $\textbf{m}\cdot \textbf{v}$ 的正负，因为重复的投影可以正负抵消，如下图所示：
![[图形学/表面模型/_attachments/u41129f85_image.png | 278]]


### masking 与 shadowing

#### masking
masking 描述的现象如下：也就是反射光线相邻的 microfect 挡住了。
![[图形学/表面模型/_attachments/u40d82247_Pasted Graphic.png | 184]]

用 $G_1(\textbf{o},\ \textbf{m})$  来描述这种遮挡现象，其中 $\textbf{o}$ 是光线的出射方向。
> $G_1$ 这个函数同样是从统计的角度来描述 masking 关系的。

用于描述 masking 的因子应该满足以下的条件：
$$\int_{\Omega} D(\textbf{m}) \langle \textbf{m} \cdot \textbf{v} \rangle G_1(\textbf{v},\ \textbf{m}) d\omega_m = \textbf{n} \cdot \textbf{v}$$

其中，$\langle \textbf{m} \cdot \textbf{v} \rangle = \min(0,\ \textbf{m} \cdot \textbf{v})$ 。
这个表达式表示：去掉所有的背面，考虑 masking 的情况，所有 microfect 的投影面积应该等于宏观表面的投影面积：
![[图形学/表面模型/_attachments/u6e1019eb_image.png | 332]]


#### shadowing
shadowing 描述的现象如下图所示，也就是入射光线被邻近的 microfect 挡住了
![[图形学/表面模型/_attachments/u73fa577b_Pasted Graphic 2.png | 225]]

同样可以用函数 $G_2(\textbf{i},\ \textbf{m})$ 来从统计角度描述 shadowing 现象。


#### G 函数
一般将 masking 项和 shadowing 项合起来写：
$$G(\textbf{i},\ \textbf{o},\ \textbf{m})$$


### BRDF 的推导
涉及到的几何如下图：
![[图形学/表面模型/_attachments/u5b3040d7_macr Sur face.png | 278]]

考虑一个 microfect，根据 BRDF 的定义可以知道，从该微表面上反射出的 Radiance 为：
$$L_o^m 
= \int_{\Omega}L_i f_r^m(\textbf{i},\ \textbf{o},\ \textbf{m}) |\textbf{i} \cdot \textbf{m}| d\omega_i$$

然后考虑整个 macrosurface，从该表面上反射出的 Radiance 可以通过微表面的 Radiance 积分得到：
![[图形学/表面模型/_attachments/u83ab27b9_f Lo Dom) Gci,o, m) lo m dwm.png | 405]]

然后 BRDF 的定义如下：
$$f_r(\textbf{i},\ \textbf{o},\ \textbf{n}) 
= \frac{dL_o}{L_i |\textbf{i} \cdot \textbf{n}| d\omega_i} $$

联立上述的三个方程，可以得到 macrosurface 的 BRDF 表达式：
![[图形学/表面模型/_attachments/u69ca46a0_microfect SS ERDF.png | 507]]


### 基于镜面微表面的 BRDF
如果将 microfect 视为镜面，那么其 BRDF 为：
![[图形学/表面模型/_attachments/ub4e025ea_Pasted Graphic.png | 244]]
其中：$\textbf{s}$ 是指与向量 $\textbf{o}$ 关于法线 $\textbf{m}$ 镜面对称的向量。

**为了方便积分，想要把 Dirac delta 函数的变量从 **$\textbf{i}$ **变为 **$\textbf{h}$ 。
> $\textbf{h}$ 是半程向量，即 $\textbf{h} = \frac{\textbf{i} + \textbf{o}}{|\textbf{i} + \textbf{o}|}$ 


使用镜面反射的微表面 BRDF，得到微表面反射 Radiance $L_o^m$ 的表达式，然后根据 Dirac delta 函数的性质，变换得到具有 $\delta_m(h)$ 的项：
![[图形学/表面模型/_attachments/ub0451c71_片+ol.png | 346]]

可以看到，在 2 式中，Dirac delta 函数的变量是 $\textbf{h}$ ，正是我们想要的形式。剩下的，只需要找到 $d\omega_i$ 和 $d\omega_h$ 之间的关系，就能根据 BRDF 的定义导出微表面的 BRDF 了。

根据 $\textbf{i},\ \textbf{o},\ \textbf{h}$ 三者之间的关系，可以绘制出如下的图。且由于 $d\omega_h$ 是由 $d\omega_i$ 引起的，因此可以得到二者的关系式：
![[图形学/表面模型/_attachments/u3c51143b_dwh.png | 365]]

> 这个关系式 $$\left|\left|\frac{d\omega_h}{d\omega_i}\right|\right|$$ 其实就是雅各比行列式。

将雅各比行列式带入前面的表达式 2，根据 BRDF 的定义，可以得到镜面微表面的 BRDF：
![[图形学/表面模型/_attachments/u82be90bc_yfrGi.0rm) 一.png | 357]]

根据微表面的 BRDF 得到宏观表面的 BRDF：
![[图形学/表面模型/_attachments/uec578ced_Pasted Graphic 1.png | 451]]


### 参考

- Eric Heitz 2014, Unserstanding the Masking-Shadowing Function in Microfacet-Based BRDFs
   - 完整地推导了 BRDF，很适合建立起体系
- Bruce Walter 2007, Microfacet Models for Refraction through Rough Surfaces
   - 推导了一下 BRDF，提出了 GGX 的模型
- Cook & Torrance 1981, A Reflectance Model for Computer Graphics
   - 提出了 Cook Torrance 的模型
- Torrance & Sparrow 1967, Theory for Off-Specular Reflection From Roughened Surfaces
   - 详细介绍了 masking 和 shadowing，提出了微表面模型
- [https://zhuanlan.zhihu.com/p/69380665](https://zhuanlan.zhihu.com/p/69380665) 很适合入门
