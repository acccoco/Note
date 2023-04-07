### 使用 CubeMap
cube map 纹理的示意图：
![[OpenGL/_attachments/Fyont.png | 500]]

6 张 texture 如上图所示围成一个正方体，摄像机位于正方体的中心，纹理是正方体的外表面。

将纹理传给 OpenGL 时，需要注意：

纹理的起点是哪里：

- 正常情况下的 `Texture2D` 纹理起点是左下角
- cubemap 的纹理起点是左上角（历史原因，似乎是 Render Man 的标准）

如果使用 `stb_image`读取纹理：
```cpp
// 读取普通的 Texture2D 纹理
stbi_set_flip_vertically_on_load(true);

// 读取 CubeMap 的某一个面的纹理
stbi_set_flip_vertically_on_load(false);
```

`CubeMap` 的每个面和纹理的对应关系：
![[OpenGL/_attachments/Pasted_Graphic_4-1.png | 400]]

注：使用如果制定了线性插值，使用 `glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS)`可以在两个面之间进行插值。

### skybox
天空盒的实质：一个 1x1x1 的立方体盒子，和摄像机重合，不会旋转
实现要点：

- 绘制之前不允许写入深度缓冲
- 先绘制天空盒，然后再绘制场景。在顶点着色器中设置天空和的深度始终为最大（1.0f），并且设置深度测试函数为 `GL_LEQUAL` ，**否则会出现闪烁和条纹**。
- 传给天空和的 `view` 矩阵应该只有旋转部分： `mat4(mat3(view_matrix))`（这并不是让 cube 随着摄像机旋转，而是将 cube 变换到摄像机的坐标系中）
- 关闭背面剔除，因为摄像机位于 cube 内部

创建立方体贴图：
![[OpenGL/_attachments/image-30.png | 600]]

顶点着色器：
![[OpenGL/_attachments/image-28.png | 500]]

片段着色器：
![[OpenGL/_attachments/image-29.png | 500]]

### 绘制到 CubeMap
由于 `CubeMap`纹理起点比较特殊，因此在将场景信息绘制到 `CubeMap`时，需要使用如下的设置：

透视投影矩阵只要确保 `fov = 90`以及 `aspect = 1.0`即可
View 矩阵如下：
![[OpenGL/_attachments/image-27.png | 600]]

注：CubeMap 的几个面是按顺序的，例如：（`glad.h`）
![[OpenGL/_attachments/Pasted image 20221029222908.png | 400]]
首先要创建一个 framebuffer：

- 为 framebuffer 绑定颜色纹理
- 为了开启深度缓冲，需要为 framebuffer 绑定深度附件。由于不需要对深度的结果进行采样，因此使用 render buffer 要好于纹理
- 注：render buffer 作用和纹理一样。区别在于，纹理可以直接用来采样，而 render buffer 无法；render buffer 的处理速度较快。
```cpp
// 创建 framebuffer
GLuint frame_buffer, render_buffer;
glGenFramebuffers(1, &frame_buffer);
glGenRenderbuffers(1, &render_buffer);
glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
glBindRenderbuffer(GL_RENDERBUFFER, render_buffer);

// 绑定深度附件
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 
                          render_buffer);

// 绑定颜色附件
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                       GL_TEXTURE_CUBE_MAP_POSITIVE_X, tex_id, 0);

// 进行 draw
...
```
