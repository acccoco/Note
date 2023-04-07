
### Axis-angle 旋转
如下图所示：

旋转轴是 $\vec{a}$，旋转前的向量是 $\vec{x}$，旋转后的向量是 $\vec{x}_{rotated}$ 
![[图形学/misc/_attachments/Pasted image 20221104190022.png | 300]]

这个问题的关键在于，向量 $\vec{x}$ 可以分解为平行于 $\vec{a}$ 的 $\vec{x}_{\parallel}$ 以及垂直于 $\vec{a}$ 的向量 $\vec{x}_{\perp}$  

旋转后的向量为：

$$
\begin{array}{rcl}
    \vec{x}_{rotated} && = && \vec{x}_{\parallel} + \vec{v} \\
    &&= && \vec{x}_{\parallel} + (\cos\theta\ \vec{x}_{\perp} + \sin\theta\ \vec{a} \times \vec{x}) \\
    &&= && (\vec{a} \cdot \vec{x})(1 - \cos\theta) \vec{a} + \cos\theta\ \vec{x} + \sin\theta\ \vec{a} \times \vec{x}
\end{array}
$$


### 矩阵形式

上述旋转公式用矩阵乘法表示为：

$$
\vec{x}_{rotated} = (Sym(\vec{a})(1-\cos\theta) + I\cos\theta + Skew(\vec{a})\sin\theta)\ \vec{x}
$$

其中：
$$
Sym(\vec{a}) = 
\begin{bmatrix} a_x \\ a_y \\ a_z \end{bmatrix}
\begin{bmatrix} a_x && a_y && a_z \end{bmatrix}
=
\begin{bmatrix}
    a_x^2 && a_x a_y && a_x a_z \\
    a_x a_y && a_y^2 && a_y a_z \\
    a_x a_z && a_y a_z && a_z^2
\end{bmatrix}
$$

$$
Skew(\vec{a}) = 
\begin{bmatrix}
    0 && -a_z && z_y \\
    a_z && 0 && -a_x \\
    -a_y && a_x && 0
\end{bmatrix}
$$
> $Skew$ 具有 $Skew(\vec{a})\vec{x} = \vec{a}\times\vec{x}$ 的性质

