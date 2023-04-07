对于不同的光源类型，Unity 使用不同的渲染路径

### directional light

场景如下：
![[Unity/Unity 渲染/_attachments/image.png | 300]]

渲染流程：
![[Unity/Unity 渲染/_attachments/Caweia_Depth_Texture.png | 400]]
说明：

- 首先得到 `Camera DepthTexture`，该 texture 用于得到 `Screenspace Shadowmap`
- 然后得到 `cascaded Shadowmap`（**注：只有 directional light 才有 CSM**）
- cellect shadow：综合`Camera DepthTexture`和`cascaded Shadowmap`，得到`Screenspace Shadowmap`。这个 pass 中可以应用例如 PCF 这样的 filter。

`Screenspace Shadowmap`的好处：

- 如果在 fragment shader 中直接查询「shadow map」，那么每次查询都需要从遍历各个 level，这里面会有重复查询。「screen space shadow map」可以有效剔除重复的查询。
- 可以使用各种 post process 方法来软化阴影。

### spot light
场景如下：
![[Unity/Unity 渲染/_attachments/image-2.png | 400]]

渲染流程：
![[Unity/Unity 渲染/_attachments/y_Drawing.png | 400]]
说明：

- 由于 spot light 是透视投影，因此并不使用 cascaded shadow map
- `forward_pass`是使用环境光来照射场景
- `forward_add`是使用直接光源，也就是 spot light 来照亮场景。查询 shadowmap 可知哪些 fragment 是被照亮的。

### point light
场景如下：
![[Unity/Unity 渲染/_attachments/image-1.png | 300]]

渲染流程：
![[Unity/Unity 渲染/_attachments/cue_Shadowmap.png | 400]]

说明：

- point light 的 shadow map 是透视投影，无 cascaded；shadow map 时 cube 类型的。
- `forward_base`仅考虑环境光
- `forward_add`仅考虑直接光照，需要查询 shadow map 判断一个 fragment 是否被照亮。
