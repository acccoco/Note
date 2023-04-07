### Uniform 缓冲对象
uniform 缓冲对象的好处：多个着色器可能有相同的 uniform 变量，比如 view 矩阵和 projection 矩阵

使用示意图：
![[OpenGL/_attachments/image-39.png | 500]]

### Uniform 块布局
`**shared**`**布局**
默认使用的是 `shared`布局，需要调用 `glGetUniformIndices()`获取某个 `uniform`变量的位置。

`**std140**`**布局**
布局规则：

- 每个变量都有一个「基准偏移量（Base Alignment）」，它等于变量的实际大小 + 填充量（Padding）。
- 每个变量还有「对齐偏移量（Aligned Offset）」，它表示变量的偏移地址。「Aligned Offset」应该是这个变量「Base Alignment」的整数倍。

常见变量的「Base Alignment」大小：（N 表示 4 字节）

- 标量 `int`或 `float`：N
- 向量：2N 或 4N。（例如：`vec3`的 Base Alignment 应该是 4N）
- 标量或向量的数组：每个元素的 Base Alignment 都是 4N
- 矩阵：视为列向量的数组。
- 结构体：填充到 4N 的整数倍。

注：`bool`类型默认大小为 `4bytes`。

`std140`内存布局示意图：
![[OpenGL/_attachments/image-40.png | 600]]

### 参考

- [高级GLSL](https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/08%20Advanced%20GLSL/)
