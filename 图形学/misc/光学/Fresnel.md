### 光的极化
**光的极化**：横波的振荡方向始终与传播方向垂直，振荡方向用「偏振」来描述。光是电磁波，将电场方向视为其振荡方向，用「极化」来描述其电场方向。

任何极化状态都可以由两个正交的极化正态线性组合而得到，可以类比「基向量」来理解这一概念。

**S 极化和 P 极化**：
首先定义「入射平面」，由「入射光线」和「反射光线」组成的平面叫做「入射平面」，「法线」和「折射光线」也位于「入射平面」内。
「S 极化」是指电场方向垂直于入射平面；「P 极化」是指电场方向平行于入射平面。
![Pasted Graphic.png](图形学/misc/_attachments/Pasted_Graphic%201.png)

### Snell 定律
Snell 定律给出了「入射角度」，「反射角度」，「折射角度」应该满足的关系。
![M2 1.png](图形学/misc/_attachments/M2%201.png)

**全反射**：根据 Snell 定律，光从折射率较大的介质向折射率较小的介质传播时（从水到空气），存在一个临界角度，当入射角度大于该临界角度时，只发生反射，不发生折射。
![M2.png](图形学/misc/_attachments/M2-1%201.png)
### 菲涅尔方程
菲涅尔方程给出了「反射能量」和「折射能量」的占比。
$R$是反射系数，$T$是透射系数，两者之间存在如下关系：
$R + T = 1$

菲涅尔方程如下：
![Zaco30i 一 2i ros 8t.png](图形学/misc/_attachments/Zaco30i_一_2i_ros_8t%201.png)

假设波阻抗仅由折射率确定，可以得到如下的表达式：
![Ir.cos 0i -M2.png](图形学/misc/_attachments/Ir.cos_0i_-M2%201.png)
**自然光是「非极化」的**：
图形学处理的是自然光照，可以认为是「非极化」的，也就是：
$R = \frac{1}{2}(R_s + R_p)$

从空气到水中；从水中到空气中的「反射系数」：（从水中到空气会发生「**全反射**」）
![image.png](图形学/misc/_attachments/image-1%202.png)![image.png](图形学/misc/_attachments/image-3%202.png)

**金属和绝缘体的折射率**：

- 绝缘体（电介质）：可以认为对于不同波长的可见光折射率是相同的
- 金属：对于不同波长的可见光折射率是**不同的**

### 图形学中的菲涅尔方程
**Schlick 近似**：
Schilick 给出了 Fresnel 方程的近似表达式：
$R = R_0 + (1-R_0)(1-\cos\theta_i)^5$
其中：$$
R_0=\left(
\frac{n_1 - n_2}{n_1 + n_2}
\right)^2
$$是「基础反射系数」。也就是入射角 $\theta_i = 0$，光从法线入射的反射系数。

> 在使用 $R_0$时，默认光从空气入射到其他介质中。
> 如果光从其他介质入射到空气中，在计算「反射系数」时，$\theta_i$应该带入实际的「**折射角**」。
> ![water 1.png](图形学/misc/_attachments/water%201.png)


**绝缘体的反射系数**：
绝缘体的基础反射系数一般很低，常见的绝缘体（电介质）的反射系数：
![image.png](图形学/misc/_attachments/image-4%201.png)

**金属的反射系数**：
金属的基础反射系数较高，且对于不同波长的光具有不同的反射系数。以铜 Cu 和金 Au 为例：
![image.png](图形学/misc/_attachments/image-2%202.png)
注：金的 Red 通道的基础反射率 $1.022 > 1$。

**反照率贴图：Albedo**
Albedo 贴图记录的是物体的基础反射系数，可以简单理解为物体的颜色。
和漫反射贴图的区别在于，对于表面的细小裂痕，漫反射贴图会给出阴影的颜色，而反照率贴图给出的是材质「真实」的颜色。

### 一个现象
在观看水面时，近处能看到水底，远处却只能看见倒影。

在看近处时：
![[图形学/misc/_attachments/Pasted_Graphic-1 1.png]]

看远处时：
![[图形学/misc/_attachments/air 1.png]]
### 资源

- wiki：[https://en.wikipedia.org/wiki/Fresnel_equations](https://en.wikipedia.org/wiki/Fresnel_equations)
- 知乎专栏：[https://zhuanlan.zhihu.com/p/303168568](https://zhuanlan.zhihu.com/p/303168568)
- 绘图代码：[[图形学/misc/_attachments/fresnel.py]]
