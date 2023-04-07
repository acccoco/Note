### 纹理使用
纹理使用的示意图：
![[OpenGL/_attachments/image-26.png | 500]]


### filter
`GL_TEXTURE_MIN_FLITER`：纹理采样时，如果确定纹理应该缩小，就用这个参数指定的缩小方法。

- 其中 `NEAREST, LINEAR`不使用 mipmap
- `GL_NEAREST_MIPMAP_NEAREST`表示要使用 mipmap。第一个 `NEAREST`表示在一个 `level`内使用 `NEAREST`，第二个 `NEAREST`表示在 `level`之间使用 `NEAREST`，也就是选择最近的一个 `level`
- 按照上面的解释，`GL_LINEAR_MIPMAP_LINEAR`表示三线性插值

`GL_TEXTURE_MAG_FILTER`指定纹理放大时的采样方法。放大无法使用 mipmap，因为 mipmap 是根据原 texture 生成的更小的 texture。

`glGenerateMipmap()`：

- 如果纹理内的数据是空的，那么可以预留出足够的内存，稍后可以手动产生各个 `level`
- 如果纹理内已经有数据，那么可以自动生成多级更小的texture

在 `glsl`中，使用 `textureLod()`来读取某个 `level `的纹理，`level=0`表示原始纹理。
