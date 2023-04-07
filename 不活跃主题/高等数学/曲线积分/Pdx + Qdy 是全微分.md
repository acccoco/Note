
## Pdx + Qdy 是全微分的条件
$Pdx + Qdy$  看起来是一个函数的全微分。
是否存在这样一个函数 $u(x,\, y)$ ，使得 $Pdx + Qdy$  是其全微分？为了达成这个性质，$P(x,y)$  和 $Q(x, y)$  应该满足什么条件？

$Pdx + Qdy$  是 $u(x,\, y)$  的全微分，其充分必要条件为：
$$\frac{\partial P}{\partial y} = \frac{\partial Q}{\partial x}$$

$u(x,\, y)$  的表达式为：
$$u(x,\, y) = \int_{(x_0,\, y_0)}^{(x, \, y)} P(s, \, t)ds + Q(s,\, t)dt$$

由于满足「积分与路径无关」的条件，因此可以有：
![[不活跃主题/高等数学/曲线积分/_attachments/1637134121100-ad20a4bf-e14c-4762-a0b8-d187329e8a89.png | 193]]
$$u(x, \, y) = \int_{x_0,\, y_0}^{x,\, y_0}P(s,\, t)ds + \int_{x,\,y_0}^{x,\, y} Q(s,t)dt$$
$$u(x, \, y) = \int_{x_0,\, y_0}^{x_0,\, y}Q(s,\, t)dt + \int_{x_0,\,y}^{x,\, y} P(s,t)ds$$ 

**存在如下三者的关系**：
![[不活跃主题/高等数学/曲线积分/_attachments/1637134617345-9126cad9-8904-46d0-8383-4a3f3e8ef615.png | 340]]


## 推导
证明使得 $Pdx + Qdy$  是 $u(x,\, y)$  的全微分的充要条件是：
$$\frac{\partial P}{\partial y} = \frac{\partial Q}{\partial x}$$

**证明必要条件**：
如果 $du = P(x,\, y)dx + Q(x,\, y)dy$ ，那么可以推论出：
$$\frac{\partial u}{\partial x} = P(x,\, y),
\quad
\frac{\partial u}{\partial y} = Q(x,\, y)$$
二阶偏导：
$$\frac{\partial^2 u}{\partial x \partial y} = \frac{\partial P}{\partial y}, \quad
\frac{\partial^2 u}{\partial y \partial x} = \frac{\partial Q}{\partial x}$$
由二阶混合偏导相等可得：
$$\frac{\partial P}{\partial y} = \frac{\partial Q}{\partial x}$$

**证明充分条件**：
给出 $u(x,\, y)$  的表达式：
$$u(x,\, y) = \int_{(x_0,\, y_0)}^{(x, \, y)} P(s, \, t)ds + Q(s,\, t)dt$$

按照偏导数的定义，可以写出：
$$\frac{\partial u}{\partial x} = \lim_{\Delta x \to 0} \frac{u(x + \Delta x,\, y) - u(x,\, y)}{\Delta x}$$

由于已经有 $\frac{\partial P}{\partial y} = \frac{\partial Q}{\partial x}$ ，因此积分与路径无关：
![[不活跃主题/高等数学/曲线积分/_attachments/1637133057237-9a664ad1-adca-4f50-b629-4a3d9f571f2c.png | 215]]

可以将 $u(x+\Delta x,\, y)$  对应的路径从 $M_0N$  换成 $M_0M + MN$ ，因此有：
$$\begin{aligned}
u(x+\Delta x, y) &=\int_{\left(x_{0}, y_{0}\right)}^{(x+\Delta x, y)} P d x+Q d y \\
&=\int_{\left(x_{0}, y_{0}\right)}^{(x, y)} P d x+Q d y+\int_{(x, y)}^{(x+\Delta x, y)} P d x+Q d y \\
&=u(x, y)+\int_{(x, y)}^{(x+\Delta x, y)} P d x
\end{aligned}$$

再做如下变换（中间用了积分中值定理）：
$$\begin{aligned}
u(x+\Delta x, y)-u(x, y) &=\int_{(x, y)}^{(x+\Delta x, y)} P d x \\
&=P(x+\theta \Delta x, y) \cdot \Delta x \\
\lim _{\Delta x \rightarrow 0} \frac{u(x+\Delta x, y)-u(x, y)}{\Delta x} &=\lim _{\Delta x \rightarrow 0} P(x+\theta \Delta x, y) 
\quad (0 \le \theta \le 1)
\\
\frac{\partial u}{\partial x} &=P(x, y)
\end{aligned}$$

同理，还可以证明 $\frac{\partial u}{\partial y} = Q(x,\, y)$ 
















