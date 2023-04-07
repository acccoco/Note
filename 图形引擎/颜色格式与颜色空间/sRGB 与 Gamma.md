---
tags:
    - 颜色空间
---

### sRGB

sRGB 颜色空间的起源是：CRT 显示器的电压和亮度之间的非线性关系。

sRGB 空间中存放的并不是实际亮度的线性值，而是经过 Gamma 矫正后的值。

> [!info] 
> 这种非线性关系==恰好==是人眼对亮度感知的良好近似。图片的暗部相比于亮部拥有更高的精度。
> 
> wiki 里说 Gamma 是一个转换函数，根据人眼的感知特性，存储图形时需要进行 Gamma 转换；使用 CRT 显示图形时也要进行 Gamma 转换。两者虽然都叫做 Gamma transfer function，但数值不同。[wiki - Gamma correction](https://en.wikipedia.org/wiki/Gamma_correction)





以 OpenGL 的文档为参考，从 sRGB 到 RGB 的转换公式（transfer function, OETF）为：

![[OpenGL/_attachments/Cs.png | 300]]

![[OpenGL/_attachments/10.png | 300]]

> [!note] 参考
> [stackoverflow-What are the practical differences when working with colors in a linear vs. a non-linear RGB space?](https://stackoverflow.com/questions/12524623/what-are-the-practical-differences-when-working-with-colors-in-a-linear-vs-a-no)


### 感知量和物理量

实验证明，人的感知等级和物理刺激并不是线性的关系，而是呈对数关系。

- 以亮度为例，人能够很容易感受到一根蜡烛和两根蜡烛的亮度差别，但是几乎感受不到 100 根和 101 根蜡烛的亮度区别
- 以声音频率为例，十二平均律是一个等比数列，比例约为 1.059 

下图是人感受到的亮度（Birghtness，感知量）和发光亮度（Luminance，流明，物理量，单位 $cd/m^2$ 或 $nits$）之间的关系：

![[图形学/misc/_attachments/v2-e3f307e8cefc4c1117c6afe78250bfa6_1440w 1.jpg |300]]

> [!note] 人的感知和 sRGB 之间的关系
> [quora-Is it evolutionary that human eyes see in sRGB, as opposed to linear RGB, sRGBU (U is ultraviolet), sIRGB (I is infrared), or sRG?](https://www.quora.com/Is-it-evolutionary-that-human-eyes-see-in-sRGB-as-opposed-to-linear-RGB-sRGBU-U-is-ultraviolet-sIRGB-I-is-infrared-or-sRG)

