#### `gl_FragCoord`
`x, y`是当前 fragment 在 framebuffer 中的坐标，默认以左下角为原点，坐标值取像素中心点的：
![[OpenGL/_attachments/Pasted_Graphic_9.png | 400]]

`z`是当前的深度信息，对于 OpenGL 来说，深度范围是 $[0,\ 1]$
`w`等于 $-1/z_e$，其中 $z_e$是「view space」中坐标的 $z$分量。由于摄像机朝向是 $-z$，因此 `gl_FragCoord`的 `w`分量就是「view space」内一点到摄像机所在平面的距离：
![[OpenGL/_attachments/Pasted_Graphic_10.png | 400]] 