---
tags:
    - 渲染路径
---


### deferred
分为：

- 不透明
   - 几何处理：记录 normal，albedo，specular，depth 等信息
   - 光照着色
- 透明物体使用 forward 方法渲染

```python
# 总复杂度 O(m + n)
for light(m):
	for pixel in framebuffer:
        shadding
```

优点：

- 可以减轻光照计算的压力

缺点：

- deferred 方法减少了 object 的 overdraw，但是光源仍然是 overdraw 的
- 占用显存和带宽，使用了 multi sample 后，开销更是巨大
- 只能使用一种 shading model
- 对于透明物体没有办法