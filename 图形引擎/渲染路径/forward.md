---
tags:
    - 渲染路径
---


### forward
分为两个阶段：

- 不透明物体
- 透明物体：关闭深度写入，开启 alpha blend

```python
# 总复杂度为 O(m*n)
for object(n):
	for light(m):
    	shading
```
有大量的 overdraw：

- 同一个 pixel 可能渲染多次，大部分都被丢弃了（early-z 可以缓解，还是需要 CPU 进行排序，从前到后绘制，减少 overdraw）
- 对一个 pixel 进行着色时，有些贡献非常小的光源也考虑进去了

优化：

- frustum culling，light volume culling
- 限制着色频率：主光源 per pixel 着色；次要光源 per vertex