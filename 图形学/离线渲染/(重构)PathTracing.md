## 基本思路

$$
L_o = \int_{H^2} fr\; L_i\; \cos\theta_i\; d\omega_i
$$

![[图形学/离线渲染/_attachments/1667212802.282826_image.png | 400]]

## Shadow Ray

将渲染方程拆分为直接光照和间接光照两项，每次反射时发射两根光线：

- scatter ray ：朝非光源发射
- shadow ray：朝光源发射

对应的渲染方程如下：

$$
L_o 
= \int_{H^2}g_{Direct}(\omega_i)\; fr\; L_i\; \cos\theta_i\; d\omega_i 
+ \int_{H^2}g_{Indirect}(\omega_i)\; fr\; L_i\; \cos\theta_i\; d\omega_i 
$$

其中

* $g_{Direct}(\omega_i)$ ：如果入射光直接来自光源，那么函数值为 1，否则为 0；$g_{Indirect}(\omega_i)$ 相反。

使用 Monte Carlo 方法来计算两个积分即可。

### 关于面光源积分

渲染方程来自直接光照的贡献可以进一步细化，按照光源进行拆分：

$$
L_{Direct} 
= \int_{H^2}g_{D_1}(\omega_i)\; fr\; L_i\; \cos\theta_i\; d\omega_i 
+ \int_{H^2}g_{D_2}(\omega_i)\; fr\; L_i\; \cos\theta_i\; d\omega_i 
+ \cdots
$$

如果某个光源是面光源，则可以将半球上的立体角积分转换为关于光源面积的积分：

$$
\int_{H^2}g_{D_1}(\omega_i)\ f_r\ L_i\ \cos\theta_i\ d\omega_i
= \int_{A_1} g_{D_1}(\omega_i)\ f_r\ L_i\ \cos\theta_i \frac{ds\ \cos\alpha_i}{||x' - x||^2}
$$

其中：

* $g_{D_1}(\omega_i)$ 如果入射光线来自于面光源 1，则函数值为 1，否则为 0
* $\alpha_i$ 入射光线与面光源法线的夹角
* $||x'-x||$ 着色点到面光源的距离

积分变量的替换是根据几何关系得出的：

![[图形学/离线渲染/_attachments/Pasted image 20221205180212.png | 500]]

使用蒙特卡洛方法进行数值积分（采样方法为：在面光源上随机采样）：

$$
L_{D_1} 
= \frac{1}{n}\sum_{k=1}^n g_{D_1}(\omega_i)\; f_r\; L_i\; \cos\theta_{ik}
\; \frac{A_1\; \cos\alpha}{||x' - x||^2}
$$

注：上述积分的积分变量是 $dA$，因此 MonteCarlo 方法使用的概率密度函数为 $pdf(A) = \frac{1}{A_1}$ 

