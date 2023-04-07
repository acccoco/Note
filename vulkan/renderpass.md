
- `vk::DependencyFlags::BY_REGION`：表示 framebuffer 内部的 dependency。
  对于 tile-based 架构来说，有了这个 flags，它可以让指定的 framebuffer-region 都位于 tile 上，从而避免了在 tile 和 memory
  之间的内存操作。
  
- 如果是 framebuffer-globa dependency，就免不了要将数据从 tile 上 flush 到 memory
