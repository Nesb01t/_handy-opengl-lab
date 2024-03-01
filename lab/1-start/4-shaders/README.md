### Shader

Shader 是驻留在 GPU 上面的一个个小程序单元，只是将输入转换成输出的程序

### GLSL 语言

GLSL 类似 C 语言，专门为图形定制

开头是版本声明，输入和输出，uniform 以及主要功能的列表

```c++
#version version_number
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;
  
uniform type uniform_name;
  
void main()
{
  // process input(s) and do some weird graphics stuff
  ...
  // output processed stuff to output variable
  out_variable_name = weird_stuff_we_processed;
}
```

### Uniform

Uniform 是一种从 CPU 中的应用向 GPU 中的着色器发送数据的方式

然而 Uniform 和顶点属性不同，Uniform 是全局的

```c++
#version 330 core
out vec4 FragColor;
  
uniform vec4 ourColor; // we set this variable in the OpenGL code.

void main()
{
    FragColor = ourColor;
}   
```

尝试一下随着时间的推移改变颜色

1. 通过 glfwGetTime() 获得时间
2. 使用 sin 函数改变颜色
3. 使用 glGetUniformLocation 函数获得 uniform 的 offset
4. 使用 glUniform4f 函数设置 uniform 的值

```c++
float timeValue = glfwGetTime();
float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
glUseProgram(shaderProgram);
glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
```