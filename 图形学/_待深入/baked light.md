以 Unity 为例
Unity 使用离线的方法（例如路径追踪）得到场景中静态物体的 Irradiance （$W/m^2$ ）信息，存放在「light map」中：

![[图形学/阴影/_attachments/uf1b11bbe_image.png | 455]]
如果要使用 baked light 的方法照亮动态的物体，可以使用「light probe」。
由于「light map」中存放的是 Irradiance 信息，光照的方向信息已经丢失了，因此无法用来计算 specular 或者 glossy 的发射。这两种反射需要借助「reflection probe」来计算。
