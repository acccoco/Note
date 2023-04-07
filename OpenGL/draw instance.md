### DrawCall
考虑这样一个场景：小行星带，每个小行星的模型是一样的，不一样的是位置，角度以及尺寸。场景中有数万个小行星。
如果使用这样的方式来绘制：
```cpp
shader.use();
for (unsigned int i = 0; i < amount; ++i) {
	shader.setUniformMat4("model", model[i].model_matrix);
    glDrawArray(GL_TRIANGLE, 0, model[i].mesh.size);
}
```
由于每次调用 `glDrawArray` 绘制时，cpu 都会向 gpu 传递很多状态，cpu 处于忙碌状态，显卡处于空闲状态

### DrawInstance
绘制大量物体是，可以一次性将所有数据传给显卡，有两种方法：

#### 方法1：通过 uniform 变量传递
在着色器里面可以通过 `gl_InstanceID` 知道当前正在绘制第几个实例
着色器的代码：
```cpp
// 顶点着色器
uniform mat4 models[100];
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * models[gl_InstanceID] * aPos;
}
```
应用的代码：
```cpp
vector<mat4> model_matrices;
for (unsigned int i = 0; i < amount; ++i) {
	shader.setUniformMat4("models[%d]".format(i), model_matrices[i]);
}
glDrawArrayInstanced(GL_TRIANGLE, 0, model.mesh.size, amount);
```

这种方法受限于 uniform 变量所能传递的数据大小

#### 方法2：使用实例化数组
以顶点属性的形式传递每个实例的位姿
着色器的代码：
```cpp
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 instanceModel;
```
应用的代码：
这里很关键的代码是 `glVertexAttribDivisor(index, divisor)` 

- index 表示影响的顶点属性；
- divisor 为 0 ，表示每绘制一个顶点，就会更新该顶点属性；divisor 为 n，表示每绘制完 n 个实例，才会更新该顶点属性
```cpp
vector<mat4> model_matrices;
glBindVertexArray(model.VAO);

glEnableVertexAttribArray(3);
glEnableVertexAttribArray(4);
glEnableVertexAttribArray(5);
glEnableVertexAttribArray(6);
glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(0 * sizeof(mat4)));
glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(1 * sizeof(mat4)));
glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(2 * sizeof(mat4)));
glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(3 * sizeof(mat4)));
glVertexAttriDivisor(3, 1);
glVertexAttriDivisor(4, 1);
glVertexAttriDivisor(5, 1);
glVertexAttriDivisor(6, 1);
```
