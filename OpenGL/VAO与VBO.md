
![[OpenGL/_attachments/image-37.png | 400]]
VBO（`GL_ARRAY_BUFFER`）表示模型的定点数据，例如定点的位置，法线，贴图坐标等
EBO（`GL_ELEMENT_ARRAY_BUFFER`）表示图元的装配信息，例如哪几个顶点可以装配成一个三角形
VAO（`VertexArray`）表示顶点属性的配置情况，例如如何从 VBO 中识别出顶点位置，法线坐标等

基本用法：
```cpp
vector<float> vertices;		// vertices data
vector<GLuint> indices;		// indices data

// create buffers
GLuint VAO, VBO, EBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

// bind VAO
glBindVertexArray(VAO);

// set VBO
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, vretices.size() * sizeof(float), 
             &vertices[0], GL_STATIC_DRAW);

// set EBO
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBUfferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), 
             &indices[0], GL_STATIC_DRAW);

// configure vertex attribute
// params: index, size, type, normalized, stride, pointer
// 0-position, 1-normal, 2-uv
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
glEnableVertexAttribArray(1);
glVertexAttribPointer(1, 3, GL_FLAOT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(flaot)));
glEnableVertexAttribArray(2);
glVertexArraybPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(flaot), (void*)(6 * sizeof(float)));
```

上面的三个顶点属性对应着顶点着色器中的：
```cpp
// in vertex shader
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 nv;
```

更新缓冲对象的部分数据
```cpp
void glBufferSubData(GLenum  			target,
 					 GLintptr  			offset,
 					 GLsizeiptr  		size,
 					 const GLvoid*  	data);
```
![[OpenGL/_attachments/image-38.png | 400]]

