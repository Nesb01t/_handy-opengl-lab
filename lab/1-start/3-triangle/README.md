## 了解 shader

### (handy) 模块化

lab 中有很多重复的代码，我们把他整理到 common 中进行复用

查看 triangle.cpp 中的代码

1. 加载 glfw
2. 创建 window
3. 加载 glad
4. 加载 viewport
5. 进入 triangle main loop

### 运行 triangle

Triangle 是一个只有静态工具方法的类

在 intro 中执行 Triangle::run() 即可看到一个三角形

### 你好 triangle

我们需要 graphics pipeline 将 3D 转化为 2D

它可以分为几个步骤，每一步都需要前一步的输入作为其输出，每一步都是专业且特定的

由于他是并行的，每个步骤运行小程序都被称为着色器

其中一些着色器是可以被开发人员配置或替换的，使得我们可以对 pipeline 中的特定部分进行定制

着色器是用 GLSL 编写的，是一种专门为图形编程设计的语言

### vertex shader

作为最开始的输入，传入 3D 坐标列表，顶点的数据使用顶点属性显示

### geometry shader

顶点着色器的输出可以传递到几何着色器，可以形成新的图元，比如三角形

### rasterization

随后开始光栅化，将生成的图元映射到屏幕像素上，产生供 fragment shader 使用的片段

在段着色器执行之前会丢弃屏幕外面的内容，提高性能

### fragment shader

段着色器计算像素的最终颜色，可以使用纹理和光照等技术

### alpha test & blending

最后，检查段的深度和模板值，检查段是否位于其他段的后面或者前面，并相应地丢弃

此时还会检查 alpha(透明度) 等等

### 现代 OpenGL

我们需要定义自己的顶点和段着色器，因此渲染一个三角形亦非易事

## vertex input

绘制一些东西的起点是一些 vertex 数据，渲染一个三角形需要 3 个点

这里我们以 float 数组，以 '标准化设备坐标' 的模式传入，查看 data.h 中的内容

定义了顶点数据之后，我们将其输入 vertex shader，通过在 GPU 上创建内存、配置 OpenGL、并告诉内存如何将数据发送到 GPU 上

我们通过所谓的 VBO 来管理该内存，即 vertex buffer object

这是我们第一次遇到的 OpenGL 对象，详细可以查看 triangle.cpp 中的 createVBO() 注解

到目前位置，我们把顶点数据存在 gpu memory 中，由名为 VBO 的对象管理，接下来我们创建一个处理这些数据的 vertex shader 和
fragment shader

## vertex shader

如果我们要进行渲染，至少需要一个 vertex shader 和一个 fragment shader

我们首先通过 GLSL 语言 (看起来和 C 类似) 编写顶点着色器，然后编译该着色器

1. 通过 in 关键字声明顶点着色器中所有的输入顶点的属性
2. GLSL 内置的矢量数据类型，根据后缀数字包含 1-4 个 float
3. 命名该 vec3 为 aPos
4. 通过 layout (location = 0) 告诉 OpenGL 该属性的位置

## fragment shader

最后一个着色器，用于计算像素的颜色输出

查看 triangle.cpp 中的代码，现在我们创建了一个 shaderProgram，还需要将顶点数据发送到 GPU

并告诉 GPU 如何在顶点和段着色器中处理顶点数据，OpenGL 还不知道如何处理这些数据以及将顶点链接到顶点着色器的属性

### linking vertex attributes

顶点着色器允许我们以顶点属性的形式指定任意输入，我们可以在顶点着色器中定义任意数量的输入，只要我们指定了正确的顶点属性

我们的 vertex buffer data 按照一个特定格式排列

按照这个格式我们就可以告诉 OpenGL 如何解释这些数据