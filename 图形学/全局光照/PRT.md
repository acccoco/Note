PRT：Precomputed Radiance Transfer


### 球谐函数

#### 函数投影
函数 $f(x)$  和 $g(x)$  「正交」是指，在某个定义域 $S$ 上，存在如下的表达式：
$$\langle f, g \rangle = \int_S f(x)\ g(x) dx = 0$$

函数 $h(x)$ 在 $f(x)$ 上的「投影」是指：
$$c = \int_S h(x)\ f(x) dx$$

> 如何理解上述概念：可以和线性代数中的向量来类比理解。
> - $\int_S f(x)\ g(x) dx$ 对应着向量的「点积」运算，这样正交就好理解了
> - 用基向量来表示任意一个向量就是投影，使用「点积」运算可以得到具体的投影系数。



#### 勒让德多项式
Legendre 多项式是一系列相互正交的多项式。

Legendre 多项式：（简单了解）
$$P_l^m(x) = (-1)^m(1-x^2)^{m/2} \frac{d^m}{dx^m}(P_l(x))$$

其中：$P_n(x) = \frac{1}{2^n \cdot n!} \frac{d^n}{dx^n}[(x^2-1)^n]$ 

其正交特性体现在：
![[图形学/_attachments/uab1f39ef_SC, Wiem 且l=.png | 375]]


#### 球谐函数
球谐函数是基于勒让德多项式的，一系列定义在球面上的函数，这些函数在球面上相互**正交**。
球谐函数的表达式如下：
![[图形学/_attachments/u358d4590_Pasted Graphic 1.png | 359]]

可以用球谐函数的线性组合来表示任意一个定义在球面上的函数。这实际上就是广义的「傅立叶级数」。
球面函数 $f(\theta,\ \varphi)$ 用球谐函数表示为：
![[图形学/_attachments/u86f36709_WS-L 為忘线地o.m.png | 326]]

系数可以通过以下表达式求解：（函数投影的操作）
![[图形学/_attachments/u0fcbd39f_Pasted Graphic 3.png | 401]]

球谐函数的可视化表示：
![[图形学/_attachments/ub93b3851_1-2.png | 496]]

使用球谐函数来近似球面函数的示意图：
![[图形学/_attachments/u822b53d3_page15image23205152.png | 435]]
可以看到：使用的阶数越高，近似就越精准。


#### 球谐系数的计算
球谐系数的计算难点在于获得某个球谐函数在某个方向的数值 $Y_i(\theta,\ \varphi)$ 。
前三阶的计算比较简答，可以直接 hardcode，后面的需要通过递推来计算。

Google 又一个开源库，直接给出了实现：google/spherical-harmonics
API 的形式大致如下：
```cpp
double sh::EvalSH(l, m, phi, theta);
```

接下来就是进行数值积分了。可以直接用黎曼积分，也可以用蒙特卡洛积分。


#### 球谐函数的使用
球谐函数是标准正交的，也就是：
![[图形学/_attachments/u662ce4bd_Pasted Graphic 6.png | 395]]

如果将函数 $f(\omega)$ 和 $g(\omega)$ 都用球谐函数表示，那么可以得到：
$$f = \sum_{i=0}^{\infty} c_i Y_i,\quad 
g = \sum_{i=0}^{\infty} d_i Y_i$$

使用这种表示来计算函数的乘积积分：
![[图形学/_attachments/uf31c3c6c_1Eo To.png | 419]]

使用球谐函数计算函数的乘积积分，可以将积分转化为向量的点积，这是球谐函数在图形学中的重要应用。


### Diffuse 情形的 PRT
考虑 Diffuse 情形的反射方程：
![[图形学/_attachments/uee29bcd2_Pasted Graphic 10.png | 434]]

这个反射方程就是「函数乘积积分」的形式，可以考虑使用球谐函数来简化计算。
其中：transport 需要逐顶点计算，因为每个顶点的 normal 都是不同的。最终得到的 SH 系数数据（3阶），光照只有 27 个数据；顶点数据非常大（顶点数 * 3）
> 注：
> - 光照是来自 cubemap 的环境光照，且光照的变换平缓，这样可以用较低的阶数（前 3 阶）来表示光照信息。
> - 反射方程是在半球上进行积分，可以将其扩展为在球面上进行积分，因为半球以下的部分 $\langle N_p,\ \omega_i \rangle = 0$ 。



#### unshadowed
不考虑 self shadow 自遮挡情形，也就是 $V(p,\ \omega_i) = 1$ 。在这种情况下：
![[图形学/_attachments/ud3881f89_Pasted Graphic 11.png | 426]]

分别对光照部分和 transport 部分计算对应的球谐系数即可。
光照部分只考虑**直接光照**。


#### shadowed
要考虑 self shadow 的情形。
![[图形学/_attachments/u1faddf27_L.tp wo)= Jo aLp. W).png | 500]]

如何计算出 $V(p,\ \omega_i)$ ，可以从 $p$ 点向 $\omega_i$ 方向发出射线，然后进行相交判断。
这种计算需要光线追踪框架的支持，GAMES202 选择的是 wjakob/nori 这个框架。


#### inter-reflect（迭代）
光照部分既要考虑直接光照，又要考虑间接光照。
![[图形学/_attachments/ufcc31579_Pasted Graphic 13.png | 286]]

可以这样来思考，入射到物体上某一点的光由以下几部分组成：

- 直接来自光源（cubemap）的光，记为 $L_0(\omega)$ 。例如上图中的 $L_0(\omega_1),\ L_0(\omega_2)$ 
- 来自光源，经过一次反射后到达物体的光。反射点为 $x$ ，那么这种光记为 $L_1(x)$ 。例如上图中的 $L_1(x_3)$ 
- 来自光源，经过两次反射后到达物体的光，最后的反射点为 $x$ ，那么这种光记为 $L_2(x)$ 。例如上图中的 $L_2(x_2)$ 
- 更多次反射的光。。。
> - 来自 cubemap 的光只考虑方向，不考虑物体的位置，因此记为 $L_0(\omega)$ 
> - 因为 Lambert 表面向各个方向反射的 Radiance 都相等，所以物体反射出的光只考虑位置，不考虑方向，记为 $L_k(x)$ 


一次反射的光其能量来源是直接源自光源（cubemap），因此有：
![[图形学/_attachments/u205bc776_L)Cx)= J. Loow 烧 VCX, Wi)Nx,wsolw.png | 422]]

第 $k$ 次反射的光根据定义其能量来源是第 $k-1$ 次反射的光，因此有：
![[图形学/_attachments/u6d156a40_LEKx)= Jn Lrs ()克 LL VExwal M,M di.png | 509]]

考虑使用球谐函数来简化上面的积分计算。
一次反射的光：（这和 shadowed 的情形一样）
![[图形学/_attachments/uea2bc79b_球谐系数记作ML.png | 379]]

二次反射的光：
![[图形学/_attachments/u33d809d1_一 ML•.png | 482]]

更多次反射的光：
![[图形学/_attachments/Pasted image 20221031183107.png | 400]]

从某个点反射出去的 Radiance 就是所有次数反射之和：
![[图形学/_attachments/ub32b469d_-Cx) 二.png | 356]]


#### inter-reflection（递归）
某个点反射出的 Radiance，一部分来自于直接光照，一部分来自间接光照：
![[图形学/_attachments/uf985d495_Lcx) = J.Lo(ws) Veous) &Nk,w dwi.png | 495]]

上面的表达式左边和右边都出现了 $L()$ ，因此这是一个递归的过程。

实际计算时，如果不使用「俄罗斯轮盘赌」，可以做出这样的近似：**递归深度为 0 时，只考虑直接光照，不考虑间接光照**：
![[图形学/_attachments/ue7db1db1_Pasted Graphic 28.png | 371]]

如果只考虑 k 层递归深度，从某个点反射出的 Radiance 为：
![[图形学/_attachments/Pasted image 20221031183127.png | 400]]

可以看出，上面的计算结果和从迭代的角度取考虑是完全相同的。
编码实现时，既可以用迭代的写法，也可以用递归的写法。


### 参考

- GAMES202，闫令琪
- Spherical Harmonic Lighting - the gritty details，Robin Green
