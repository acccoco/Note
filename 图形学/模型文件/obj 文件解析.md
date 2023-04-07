
主要定义了顶点和面

obj 使用的关键字：

- v：顶点
- vt：纹理坐标
- vn：法线
- g：组，从此行到下一行是一个组
- f：表面
- usemtl：从慈航到下一个 usemtl 的所有表面使用的材质名称
- mtllib：指定的材质库的名称
- \#：注释

每个顶点都有 **模型坐标系中的坐标值**，**UV坐标值**，**模型坐标系中的法线值**

```powershell
# 顶点单元
# 形式是 (x, y, z [, w])
# x, y, z 取值范围是：[-1, 1]
# w 是可选的，默认为 1.0
v 0.172833 0.300014 0.41564

# 纹理单元，形式为：(u, v [, w])
# u, v 的取值范围是：[0, 1]
# w 是可选的，默认是 0
vt  0.542 0.923 0.000

# 法线单元
# 形式是：(x, y, z)
vn  -0.092 0.474 0.876

# 表面单元
# 形式是 v1/t1/n1 v2/t2/n2 v3/t3/n3
# 分别是顶点索引/纹理索引/法线索引
# 正向索引从 1 开始，反向索引从 -1 开始
f 32/9/32 34/11/34 31/12/31
```


#### mtl 文件
obj 文件会在一开始的地方引用 .mtl 文件
.mtl 文件存放模型的各种 texture

### 参考

- [http://paulbourke.net/dataformats/obj/](http://paulbourke.net/dataformats/obj/)
- [https://www.cs.cmu.edu/~mbz/personal/graphics/obj.html](https://www.cs.cmu.edu/~mbz/personal/graphics/obj.html)
