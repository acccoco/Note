
### HDR

- 更宽的色域：覆盖更广泛的颜色空间
- 更高的位深：image 存储可以选择更多的 bytes（可以提供更平滑的颜色过渡）
- 高动态范围：shader 可以输出大于 1 的值

> [!note] 颜色空间与位深
> - [stackexchange - What's the difference between colour space and bit depth?](https://photo.stackexchange.com/questions/50536/whats-the-difference-between-colour-space-and-bit-depth)
> - [stackoverflow - How does HDR relate to color space and bit depth?](https://video.stackexchange.com/questions/21676/how-does-hdr-relate-to-color-space-and-bit-depth)


### HDR 映射到 SDR

ACES 曲线是一种 tone mapping 的方法

使用 ACES 曲线可以将 HDR 的颜色值映射到 SDR 的范围：

![[图形引擎/颜色格式与颜色空间/_attachments/Pasted image 20221106155747.png|300]]


参考：[ACES filmic tone mapping curve](https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/) 

### transfer function

OETF: opto-electronic transfer function：将光信号值转换为 image 中记录的数值。例如：fragment shader 输出的是线性的颜色值（光信号），会被引擎转换为非线性的颜色值，并存放在图片中。

EOTF：electro-optical transfer function：与上面的相反。

参考：[wiki-Transfer functions in imaging](https://en.wikipedia.org/wiki/Transfer_functions_in_imaging) 


HDR 使用不同的 transfer function：

- sRGB 使用的 transfer function 叫做 Gamma
- HDR 使用的就叫做 HDR
