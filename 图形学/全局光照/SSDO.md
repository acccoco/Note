---
tags:
- 全局光照/AO
---


SSDO：Screen Space Directional Occlusion
key idea：

- 认为环境光照就来自周围物体，周围物体就是「次级光源」
- 没有被物体挡住的地方提供「直接光照」，遮挡的物体可以提供「间接光照」。
- 关键的操作就是进行 occluder 的查询

![[图形学/_attachments/u2a44c4a4_SSDO-1.jpg ]]![[图形学/_attachments/uba5b1d4b_SSDO-2.jpg ]]
![[图形学/_attachments/u84ffcd7e_论文·SSDO-1.jpg ]]![[图形学/_attachments/u832629e4_论文·SSDO-2.jpg ]]![[图形学/_attachments/ud80c729a_论文·SSDO-3.jpg ]]![[图形学/_attachments/u6c0af9c2_论文·SSDO-4.jpg ]]![[图形学/_attachments/u2de1ee92_论文·SSDO-5.jpg ]]
