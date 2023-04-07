回顾 PCSS 的计算步骤：

1. 在 shadow map 的一定区域内进行 blocker search
2. 计算半影尺寸，确定 filter 尺寸
3. 在 shadow map 中进行 pcf

上面的步骤 1 和步骤 3 都需要多次对 shadow map 进行采样，是性能瓶颈。


### VSSM 对 PCF 的简化
PCF 的实质是确定 frag 的深度在 filter 区域内能排到第几，这也是其名称中 percentage 的来源。为了确定 frag 深度的排名，需要遍历 filter 区域内的所有像素。如果能够知道 shadow map 上任意区域中 depth 的分布情况，就不用再遍历了。

chebyshev 不等式可以根据深度的均值和方差估算出某个深度的排名情况：

![[图形学/阴影/_attachments/iU955_PCXt) ≤.png | 338]]


> 上面不等式的成立条件是：$t > \mu$ ，且随机变量的分布函数 $PDF(X)$  是单峰的。

上面的不等式可以直接当成约等式来用。

**如何计算均值 **$\mu$ ：
有两个实现方法：

1. Mipmap 可以自动计算纹理的某个区域内像素值的均值，例如 `glsl`的 `textureLod()`函数
2. 建立 SAT 数据结构，该数据结构可以在 `O(1)`内得到纹理的某个区域内像素的均值

> SAT：(Summed Area Table)
> ![[图形学/阴影/_attachments/uc8f8b84b_SATER,D=方. 5o.png | 420]]


**如何计算方差 **$\sigma^2$ ：
利用下面的公式计算方差：
$$var(X) = E(X^2) - E^2(X)$$

实现起来也很简单。在生成 shadow map 时，红色通道记录 depth，绿色通道记录 depth 的平方。然后利用 mipmap，或者建立 SAT 的结构即可。


### VSSM 对 blocker search 的简化
blocker 是计算区域内所有 blocker 的深度的均值。
假设：
![[图形学/阴影/_attachments/u8e64d724_blocker.png | 225]]

那么有以下关系式：
![[图形学/阴影/_attachments/u94a47d6b_clebyshev7等试可得.png | 436]]


这样就能算出 blocker 的平均深度 $Z_{occ}$  了。


### Moment Shadow Mapping
VSSM 是利用 chebyshev 不等式来估计 fragment 深度在 shadow map 一定范围内的深度位次 percentage 的。
chebyshev 不等式要求随机变量的概率密度函数 PDF(X) 应该是单峰的，很多情况并不满足这个假设。

使用更高阶的矩可以还原出具有更多阶梯数的累积分布函数。
> $X$  叫做一阶矩，$X^2$  叫做二阶矩。
> 使用 $m$  阶的矩，可以得到具有 $\frac{m}{2}$  个台阶的 CDF。例如：
> - 只要知道了 $\mu$ 和 $\sigma^2$ ，就知道了正态分布的全部细节。正态分布的 CDF 只有一个台阶。
> 
![[图形学/阴影/_attachments/ua7cab38d_CDFCX).png | 252]]


通常来说，使用四阶的矩就够了。恢复出 CDF 的过程过于复杂。
