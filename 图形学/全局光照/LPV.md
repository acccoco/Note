LPV：Light Propagation Volumes
key idea：

- 将场景划分为均匀的格子，统计每个格子的光照情况（用球谐光照表示），然后让光在格子直接传播。
- 对于一个 shading point，使用格子中的球谐光照来对齐进行照明，即间接光照着色

![[图形学/_attachments/u52b18e24_LPV-1.jpg ]]![[图形学/_attachments/uc90653bc_LPV-2.jpg ]]![[图形学/_attachments/uab2efbd9_LPV-3.jpg ]]![[图形学/_attachments/u6df71a1f_LPV-4.jpg ]]![[图形学/_attachments/uc95f59e4_LPV-5.jpg ]]![[图形学/_attachments/uf4977b27_LPV-6.jpg ]]![[图形学/_attachments/ua71a8034_LPV-7.jpg ]]![[图形学/_attachments/u7cef18f8_LPV-8.jpg ]]
