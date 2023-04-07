渲染可以分为 3 个阶段：
![[-最近/_attachments/Pasted image 20221103013850.png|400]]
culling：摄像机视锥体之外的物体，被遮挡的物体

Tile and Cluster Rendering
![[Unity/Unity 渲染/_attachments/Pasted image 20221103013910.png|400]]

Tile Rendering:

一般用于渲染不透明物体，deferred 和 forward 都可以使用

Culster Rendering：一般用于透明的物体

Tile Rendering 的流程是怎样的？

cluster rendering 的流程是怎样的？