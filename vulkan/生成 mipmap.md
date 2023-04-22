如何从图片导入纹理数据，并生成 mipmap
分为两个步骤：

1. 导入纹理数据
2. 生成 mipmap

**导入纹理数据**：

- 从图片中读取到的数据为 `void * data`
- 将数据放入 `stage buffer`中（`TransferSrc, HostVisible, HostCoherent`)
- 根据图片的尺寸计算 `mipmap` 的级别，创建 `Image`对象(`TransferSrc, TransferDst, Sampled, DeviceLocal`），`image` 所有 level 的 `layout` 应该是 `transferDst` 的
- 将 `stage buffer` 的数据放入 image 的 level 0

![[_attachments/image-24.png | 600]]

**生成 **`**mipmap**`：

- `level i` 和 `level i+1` 的当前 layout 都是 `transfer_dst`
   - 将 level i 的 layout 转换为 `transfer_src`
   - 基于 level i，通过 blit 生成 level i+1
   - 将 level i 的 layout 转换为 `shader readonly`
   
- 重复以上步骤
- 最后，将最后一个 level 的 layout 从 transfer_dst 转换为 shader_readonly

![[_attachments/image-25.png | 500]]


> 绘图数据 drawio.svg：
> ![[_attachments/mipmap.drawio.svg | 600]]


