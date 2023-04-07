
### Buffen 投针试验
问题背景：
> 区域内有两条平行直线，随机向区域内投针，求针与直线相交的概率。

首先确定这个模型，决定出样本空间：
![[不活跃主题/概率论/连续随机变量/_attachments/1643033090722-36674231-b2f6-4b3d-9d36-2b94031c3ec0.png | 186]]

- 针的中心位置到最近的线的距离是 $X$ 
- 针的角度记为 $\Theta$ 
- 随机变量的取值范围是：$X\in [0,\ d/2]$ ，$\Theta \in [0,\ \pi/2]$ 

根据直觉，两个随机变量都是均匀分布的，且两个随机变量是独立的，因此：
$$f_{X,\ \Theta}(x,\ \theta) = f_X(x) \cdot f_\Theta(\theta) = \frac{2}{d} \cdot \frac{2}{\pi}
$$
针与线相交这个事件如何用随机变量描述：
![[不活跃主题/概率论/连续随机变量/_attachments/1643033090812-69844c5b-0c84-4c81-82c9-27c6f9b74292.png | 263]]

$$P(A) = P(X \le \frac{l}{2}\sin \Theta)$$

计算这个事件的概率： 
$$P(X\le \frac{l}{2}\sin\Theta) = \iint_{x\le \frac{l}{2}\sin\theta} f_{X,\ \Theta}(x,\ \theta)\ dxd\theta = \frac{2l}{\pi d}$$
