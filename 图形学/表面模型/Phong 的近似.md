
### Lambert 着色的材质模型
直接光照中，Lambertian 的着色模型为：

$$L_d = k_d(I/r^2)max(0, \vec{n}\cdot\vec{l})$$

将其与反射方程对应起来，可以得到：$f_r = \frac{k_d}{\pi}$ 

漫反射材质的示意图为：

![[图形学/表面模型/_attachments/lWnBa_image.png | 268]]

> 为什么这里的 $k_d$  需要除以 $\pi$ ：
> 因为从能量守恒的角度来说，当 $L_i = 1$  时，有：$L_o = \pi f_r L_i$ ；为了让 $k_d$  比较直观，让其取之范围为 $[0,1]$ 



### phong 着色模型

phong模型的高光项：$L_s = k_s(I/r^2)max(0, \vec{n}, \vec{h})^{p}$  

该着色模型可以近似地表现glossy的材质

![[图形学/表面模型/_attachments/Wg9Mu_image.png | 272]]

