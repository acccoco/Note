## 参考

Unity Shader 的文档：

- https://docs.unity3d.com/Manual/Shaders.html
- https://docs.unity3d.com/Manual/SL-BuiltinIncludes.html
- https://docs.unity3d.com/Manual/SL-BuiltinMacros.html
- https://docs.unity3d.com/Manual/SL-BuiltinFunctions.html （坐标变换等）
- https://docs.unity3d.com/Manual/SL-UnityShaderVariables.html （时间，光照，MVP，fog）
- https://docs.unity3d.com/Manual/SL-DataTypesAndPrecision.html
- https://docs.unity3d.com/Manual/SL-Properties.html （properties 支持的类型）


# surface shader

适用于一些比较简单的情形，Unity 可以根据 `surface shader` 生成对应的 `vertex shader` 和 `fragment shader`。
`surface shader` 只能用于 built-in rendering pipeline


## 预处理命令

像`#pragma xxx`这样的就是预处理命令，Unity 会解析这些命令，提供各种扩展功能（相对于标准的 Shader）

常用的预处理命令如下：

- `#include_with_pragmas "include_file`：通过这种方式来引用其他 `shader`文件，可以将其内部的各种 `#pragma`预处理命令也包含进来
- `#pragma shader_feature xxx`：可以声明一系列的着色器关键字，外部可以控制关键字的开启和关闭，在 `shader`内部这些关键字就是宏定义。这相当于提供了 `shader`宏定义的外部接口。
- `#pragma require xxx`：指定各种 GPU features，例如 `2D texture array`，多目标渲染的数量
- `#pragma vertex name`：指定 `vertex shader`的入口函数

## properties

`properties` 是 `shader`和`editor`沟通的桥梁，对于 `shader`，可以理解为 `uniform`变量。

#### 使用示例

`properties`定义的方法（`shader`文件内）：
![[Unity/Unity 渲染/_attachments/image-50.png |400]]

在 `editor`中的显示：
![[Unity/Unity 渲染/_attachments/image-51.png | 400]]

在 `shader`的代码中使用 `properties`，需要确保变量名和 `properties`名相同：
![[Unity/Unity 渲染/_attachments/image-53.png | 400]]

#### 特殊的 `properties`
特殊的 `properties`，Unity 自动生成的：

- `{Texture}_ST`：纹理的 Tiling 和 Offset 信息
- `{Texture}_TexelSize`：纹理的尺寸信息


## `semantics`

用于指定 `vertex shader`和 `fragment shader`输入输出变量的作用。
在 `OpenGL`中，`vertex shader`会将 `clip position`写入 `gl_position`这个变量中；在 `Unity`中，没有这种特定名称的变量，开发者需要手动指定这样的变量，`semantics`机制就是为此而存在的。

例如：
![[Unity/Unity 渲染/_attachments/image-52.png | 400]]


#### `vertex shader` 相关的 `semantics`

为 `vertex shader`的输入参数指定的 `semantic`有：
`POSITION``NORMAL``TEXCOORD0, 1, 2, 3``TANGENT``COLOR`

在 `UnityCG.cginc`文件中，定义了一系列的结构体，给出了一般情况下 `vertex shader`需要的输入数据：

- `appdata_base`：包含 `position``normal``texcoord`
- `appdata_tan`：包含 `position``tangent``normal``texcoord`
- `appdata_full`：包含 `position``tangent``normal``texcoord``texcoord1-3``color`

如果 Unity 能够提供的数据比 `shader`要求的数据少，默认以 `0`填充，`w`分量以 `1`填充。
例如：Unity 只提供一个纹理，且纹理类型为 `float2`，然而 `vertex shader`需要一个 `float4`的纹理，那么最终得到的纹理为：`(uv, 0, 1)`

特殊的：

- `vertex shader`可以知道输入顶点的 ID，通过 `uint`类型的被标记为 `SV_VertexID`的输入变量知道。（需要平台支持）
- 指定为`COLOR`的输入变量会被自动转换到「线性颜色空间」。


#### `fragment shader`相关的 `semantics`

`vertex shader`可以向 `fragment shader`传递数据，这些数据中只有 `clip position`的 `semantic`需要正确标记，标记为 `SV_POSITION`；
其他的变量，都是开发者自定义的，Unity 要做的就是对这些变量进行三角形重心插值，因此 Unity 并不关心这些变量的用途，一般来说应该标记为 `TEXCOORD`。

`fragment shader`可以输出 `color`，这些输出值应该被标记为 `SV_Target`，如果有多个渲染目标，对应不同的 `SV_Targetn`

`VFACE`可以获得 `triangle`相对于 `camera`的朝向


#### `texture`与 `sampler`

一般情况下，`texture`与 `sampler`是合一的，不过也可以分开使用
例如：`D3D11`支持 128 个 `texture`，但只支持 `16`个 `sampler`

`inline sampler`：Unity 可以根据 `sampler`的名称自动生成 `sampler`，例如：`my_point_clamp_samper`。其中 `point`和 `clamp`是对应的关键字。
