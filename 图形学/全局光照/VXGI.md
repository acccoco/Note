key idea：

- 建立 voxel（体素）的层次结构以快速求交，voxel 内存放的是「次级光源的颜色」
- 对每个 shading point，按照其 BRDF lobe 进行 cone tracing（圆锥）
- 找到符合圆锥大小的某个层级的 voxel，进行 shading

![[图形学/_attachments/u749b42dc_VXGI-1.jpg ]]
