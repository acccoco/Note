view 变换将「世界空间的坐标（右手系）」变换到「视空间（右手系）」中。

注：视空间是固定与摄像机上的，且摄像机朝向为 $-z$  

摄像机的方向可以表示为（都是单位向量）：

![[图形学/光栅化/_attachments/uc86c9e22_Pasted Graphic 5.png | 412]]


摄像机的位置为点 $E$ ，在「world space」中的坐标为 $(e_x,\ e_y,\ e_z)$ 

从「world space」到「view space」的变换矩阵为（注意乘积顺序）：

$$
M_{view} =
\begin{bmatrix}
    right && 0 \\ top && 0 \\ back && 0 \\ 0 && 1
\end{bmatrix}
\begin{bmatrix}
    1 && 0 && 0 && -e_x \\
    0 && 1 && 0 && -e_y \\
    0 && 0 && 1 && -e_z \\
    0 && 0 && 0 && 1
\end{bmatrix}
= \begin{bmatrix}
    right && -right \cdot e \\
    top && -top \cdot e \\
    back && -back \cdot e \\
    0 && 1
\end{bmatrix}
$$

---

### 推导的过程

坐标系变换的本质为：同一向量使用不同的基向量来表示。

设摄像机位置 $E$ 在「world space」中的坐标为 $(e_x,\ e_y,\ e_z)$ ；

空间中一点 $P$ 在「world space」中的坐标为 $(x,\ y,\ z)$ ，在「view space」中的坐标为 $(x',\ y',\ z')$ 。

![[图形学/光栅化/_attachments/u7d4032fe_back E riqht.png | 281]]

存在以下的向量等式：

$$\overrightarrow{EP} = \overrightarrow{EO} + \overrightarrow{OP}$$

**等式左边的向量用「view space」的基向量来表示，等式右边的向量用「world space」的基向量表示**：

$$\begin{pmatrix}
\overrightarrow{right} && \overrightarrow{top} && \overrightarrow{back}
\end{pmatrix}
\begin{pmatrix}
x' \\ y' \\ z'
\end{pmatrix}
=
\begin{pmatrix}
\vec{i} && \vec{j} && \vec{k}
\end{pmatrix}
\begin{pmatrix}
x - e_x \\ y - e_y \\ z - e_z
\end{pmatrix}
$$

由于「view space」的基向量是相互正交的单位向量（逆矩阵 = 转置矩阵），「world space」的基向量构成单位矩阵，因此有：

$$\begin{pmatrix}
x' \\ y' \\ z'
\end{pmatrix}
=
\begin{pmatrix}
\overrightarrow{right} \\ \overrightarrow{top} \\ \overrightarrow{back}
\end{pmatrix}
\begin{pmatrix}
x - e_x \\ y - e_y \\ z - e_z
\end{pmatrix}
$$

最后，使用齐次坐标来表示整个变换过程：

$$M_{view}
=
\begin{pmatrix}
right && 0 \\ top && 0 \\ back && 0 \\ 0 && 1
\end{pmatrix}
\begin{pmatrix}
1 && 0 && 0 && -e_x \\
0 && 1 && 0 && -e_y \\
0 && 0 && 1 && -e_z \\
0 && 0 && 0 && 1
\end{pmatrix}$$

