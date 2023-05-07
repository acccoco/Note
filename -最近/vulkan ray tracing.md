
RayTracing 的特点：
* 加速结构
* SBT


RayTracing pipeline

SBT：
RayTracing 和光栅化的区别在于：光栅化是以 shader 来组织渲染顺序的，每一次绘制只需要关心一种材质；RayTracing 在绘制时，需要确保每种材质/shader 都是可用的，因此需要 SBT 来进行动态的材质/shader 查询。

- ray generation shader: per pixel call. generate ray.
- miss shader: does not intersect any geometry. maybe samlpe an env map.
- closest hit shader: 在光线前进的路径上，可能会命中多个 object，只有最接近起点的 hit 才会调用这个 shader。
- intersection shader: optional. 可以控制 intersection test.
- any shader: optinal. 可以用于实现 alpha 测试.

着色器之间交换数据：caller shader 产生 rayPayloadEXT，将其以 rayPayloadInEXT 的形式传给 callee shader.

着色器之间的关系：

![[_attachments/ShaderPipeline.svg | 400]]