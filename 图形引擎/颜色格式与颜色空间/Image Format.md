---
tags:
    - 颜色空间
---


### Image Format

为纹理填充数据的 API：
![[OpenGL/_attachments/Pasted_Graphic_10-1.png | 500]]
其中：

- `internal format`可以理解为显存中数据的格式
- `external format`可以理解为内存中数据的格式

各个参数的可能的取值：

- `internal format`的取值一定是类似于这种形式：`GL_RGB8`
- `format`的取值只能是 `GL_RED, GL_RG, GL_RGB, ...`之类的
- `type`的取值是 `GL_UNSIGNED_BYTE, GL_INT, GL_FLOAT`之类的形式

> [!note] 
> `internal format`为了兼容，可以取 `GL_RGBA`这样的值，但是不推荐这样写。


### Internal Format

Internal format 的格式如下：`GL[components][size][type]` 

其中，`[type]` 主要影响数值的存储方式和解释方式：

| type    | 存储形式    | 被解释为                          |
| ------- | ----------- | --------------------------------- |
| `""`    | 无符号整数  | `[0, 1]` 之间的浮点数（线性映射） |
| `SNORM` | 无符号整数  | `[-1, 1]` 之间的浮点数            |
| `F`     | IEEE 浮点数 | 浮点数                            |
| `I`     | 有符号整数  | 有符号整数                        |
| `UI`    | 无符号整数  | 无符号整数                        |

关于 normalized format，可以参考  [github-SNormTest](https://github.com/nlguillemot/SNormTest) 


以 `VK_FORMAT_R8` 为例：

- 在内存中的内容为 `0x56` ，（对应无符号整数 `86` ）
- 在读取到 `shader` 时，会被解释为浮点数 `86/255 = 0.337` 



**采样**：

应该确保 format 与采样器是一致的：

- 如果 `internal format` 使用「归一化整数」或者「浮点数」，那么需要用浮点数采样器 `sampler2D` 
- 如果 `internal format` 使用「整数」，则需要使用整数采样器 `isampler2D` 和 `usampler2D` 

> [!note] 参考
> - [khronos opengl image format](https://www.khronos.org/opengl/wiki/Image_Format)
> - [github sNormTest](https://github.com/nlguillemot/SNormTest)


### OpenGL 的使用示例

**从普通的 8 通道 sRGB 图片读取数据为纹理**：

```cpp
glTexImage2D(GL_TEXTURE_2D, 0, GL_SRBG8, width, height, 0, 
             GL_RGB, GL_UNSIGNED_BYTE, data);
```

解释：

- `internal format = GL_SRGB8`表示每个通道有 8 位，使用 `unsigned normalized`的形式表示数据，且自动将颜色值从 `sRGB`空间转换到 `RGB`空间。（也可以用 `GL_RGB8`，然后在 `fragment shader`中手动进行转换）
- `type`的 `GL_UNSIGNED_BYTE`表示内存中颜色数据每一个通道是 8 位，表示的值范围位 `[0, 255]`

**如果要将场景的数据绘制到纹理中，且数据的范围在 `[0.0, 1.0]`范围之外，可以如下**：

```cpp
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, 
             GL_RGB, GL_FLOAT, nullptr);
```


### vulkan 中的 image format

`vulkan` 的 `image format` 只是数据的编码方式：

- `B8G8R8A8Srgb` 格式的 `image`，里面的颜色值是以非线性的形式**存储的**；在 `fragment shader` 中采样该纹理，会得到**线性值**，转换会自动发生。
- `fragment shader` 默认的输出值是**线性**的颜色值，如果输出到 `B8G8R8A8Srgb` 格式的 `image`，那么会自动将线性值转换为非线性的值。

`swapchain` 有个字段叫做 `imageColorSpace`，它表示 `presentation engine` 应该如何**处理**线性颜色值（会执行对应的 EOTF 转换函数）。 shader 只需要负责输出线性颜色值即可，swapchain 会自动处理好一切。

**正确的做法**：

- 读取纹理时（图片文件绝大多数情况是 `sRGB`编码的，性价比最高），直接将图片的 `void* data`写入到 `B8G8R8A8Srgb`格式的 `image`中
- 采样纹理时，不用关心 image format，什么都不用做，得到的就是线性值
- `fragment shader` 应该输出线性值
- 确保 `swapchain` 的 `image format` 和 `color space`是一致的，例如：
   - `image format = B8G8R8A8Srgb`，`color space = SrgbNonlinear`

> [!note] khronos 的说法
> 从 sRGB image 中读取时，会自动将值从 sRGB 空间转化到线性颜色空间，因此，着色器看到的始终是「线性空间的颜色值」。
> 
> [khronos Image Format](https://www.khronos.org/opengl/wiki/Image_Format)

> [!note] 参考
> - [Vulkan swapchain format UNORM vs SRGB?](https://stackoverflow.com/questions/66401081/vulkan-swapchain-format-unorm-vs-srgb)

