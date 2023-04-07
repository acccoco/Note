---
tags:
    - vulkan
---


使用 memory barrier 可以实现 layout 的转换

-   转换发生在 memory barrier 的 available 和 visible 之间
-   转换可能涉及到读写操作，因此需要保证此前的所有 write 都是 available 的，否则会产生 write-write hazard。
-   layout 产生的 write 会自动 available 的。