## forward 渲染路径

不擅长应对大量的光照

farword 的 fragment 开销为：

对应的伪代码为：

![[Unity/Unity 渲染/_attachments/Pasted image 20221103013946.png|400]]

## deferred 渲染路径

开销分析：

![[-最近/_attachments/Pasted image 20221103013957.png|400]]

局限性：

半透明物体：

-   deferred 方法，在同一个位置，只需要运行一次 fragment shader。但是半透明要求同一个位置运行多次：半透明的 fragment，不透明的物体
-   解决办法是：对于半透明物体，最后单独使用 forward 方法渲染

正交投影：why？

硬件抗锯齿：目前能够想到的原因：

-   如果 g_buffer 的分辨率是原始分辨率，那么如何通过多个 normal 生成一个 normal，对normal 平均是没有意义的
-   如果 g_buffer 的分辨率等于 sample，那么同一个 pixel 的多个 sample 的 normal 应该是不一样的。

![[-最近/_attachments/Pasted image 20221103014012.png|400]]

## deferrd 的 framebuffer

RT0: RGB - diffuse, A - occlusion

RT1: RGB - specular color, A - smoothness

RT2: RGB - world normal

RT3: 光照贴图，反射探针

深度缓冲区，模版缓冲区