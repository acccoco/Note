![[图形学/表面模型/_attachments/ud0905483_Lo(o).png | 152]]
如果不考虑损耗，根据直觉，镜面反射应该符合：
$$L_i(\textbf{i}) = L_o(\textbf{o})$$

且光线出射的方向 $\textbf{o}$ ，入射方向 $\textbf{i}$ 以及表面的法线 $\textbf{n}$ 应该存在如下的关系：
$$\frac{\textbf{i} + \textbf{o}}{|\textbf{i} + \textbf{o}|}
 = \textbf{n}$$

反射的 Radiance $L_o(\textbf{o})$ 仅仅和入射的 Radiance $L_i(\textbf{i})$ 有关。

**现在考虑双向反射分布函数 $f_r(\textbf{i},\ \textbf{o},\ \textbf{n})$ ，为了表示入射方向和出射方向的内在关系，并且确保积分是有效的，可以使用 Dirac delta 函数**。

根据上面的推理写出反射 Radiance 的表达式：
$$L_o(\textbf{o}) 
= \int_{\Omega}L_i(\textbf{i})  \delta_{\textbf{s}}(\textbf{i}) d\omega_i$$
> 根据 Dirac delta 函数的定义，上面积分结果为：
> $$L_o(\textbf{o}) = L_i(\textbf{s})$$

其中：$\textbf{s}$ 表示与反射方向关于法线对称的方向。

根据 BRDF 的定义，可以得到镜面反射的 BRDF：
$$f_r(\textbf{i},\ \textbf{o},\ \textbf{n})
= \frac{dL_o(\textbf{o})}{L_i(\textbf{i})(\textbf{i} \cdot \textbf{n})d\omega_i}
= \frac{\delta_{\textbf{s}}(\textbf{i})}{\textbf{i} \cdot \textbf{n}}$$

如果考虑 Fresnel，那么可以得到如下形式的 BRDF：
$$f_r(\textbf{i},\ \textbf{o},\ \textbf{n})
= \frac{F(\textbf{i},\ \textbf{n}) \delta_{\textbf{s}}(\textbf{i})}{\textbf{i} \cdot \textbf{n}}$$

其中：$F(\textbf{i},\ \textbf{n})$ 是 Fresnel 项
