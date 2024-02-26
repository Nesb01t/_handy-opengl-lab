#include "triangle.h"
#include "data.h"
#include "log.h"
#include "setup.h"
//
// Created by nes on 2024/2/26.
//
void Triangle::triangleMainLoop(GLFWwindow* window)
{
    auto VAO = createVAO();
    auto shaderProgram = createShaderProgram();

    while (!glfwWindowShouldClose(window))
    {
        // rendering command here. main loop
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // main loop
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

unsigned int Triangle::createVBO()
{
    // 生成一个 unique id 的 VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // VBO 的类型是 array buffer, OpenGL 允许我们同时绑定到多个缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 从现在开始，我们在 array buffer 上的操作都会影响到 VBO
    // glBufferData 专门将用户定义的数据复制到当前绑定缓冲对象
    // 第一个参数是目标缓冲的类型
    // 第二个参数是传输的数据大小
    // 第三个参数是传输的数据
    // 第四个参数是指定了我们希望显卡如何管理给定的数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    // 三角形的位置不太会变，但会大量使用，因此用 GL_STATIC_DRAW
    // 如果是动态变化的数据，可以用 GL_DYNAMIC_DRAW

    return VBO;
}

unsigned int Triangle::createVAO()
{
    // 第一个参数是顶点属性的位置值
    // 第二个参数是顶点属性的大小
    // 第三个参数是顶点属性的类型
    // 第四个参数是是否希望数据被标准化
    // 第五个参数是步长
    // 第六个参数是偏移量
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // 现在我们绘制一个对象要经过这样的过程，如果我们要绘制多个对象，我们需要重复这个过程，这样会很麻烦
    // 1. 绑定顶点数组对象
    // 2. 复制顶点数组到缓冲中供 OpenGL 使用
    // 3. 设置顶点属性指针
    // 4. 绘制物体
    // 5. 释放顶点数组对象

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // 一个 VAO 存储了我们的顶点属性以及使用他的 VBO
    // 当你想要绘制多个对象，先生成/配置所有 VAO 并存储他们
    // 当我们想要绘制一个对象的时候，我们只需要绑定合适的 VAO 绘制之后再解绑它就好了

    unsigned int VBO = createVBO();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return VAO;
}

unsigned int Triangle::createVertexShader()
{
    // 暂时将 vertex shader 写在这里
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    // 创建一个 shader 对象
    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // 接下来，我们将 shader 源码附加到 shader 对象上，然后编译它
    // 第一个参数是 shader 对象
    // 第二个参数是我们传递的 shader 源码数量
    // 第三个参数是我们传递的真正的 shader 源码
    // 第四个参数是一个数组，用来指定每个传递的 shader 源码的长度
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // 可能需要检查 shader 是否编译成功
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        log("vertex shader compile failed");
    }

    return vertexShader;
}

unsigned int Triangle::createFragmentShader()
{
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    // 创建段着色器的过程和顶点着色器类似
    const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    return fragmentShader;
}


unsigned int Triangle::createShaderProgram()
{
    const unsigned int shaderProgram = glCreateProgram();
    const unsigned int vertexShader = createVertexShader();
    const unsigned int fragmentShader = createFragmentShader();

    // glUseProgram 之后的每个着色器和渲染调用都会使用这个程序对象
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        log("failed to link shader program");
    }
    // 删除着色器对象，因为它们已经链接到程序对象并不再需要
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void Triangle::run()
{
    handy_initGlfw();
    GLFWwindow* window = handy_createWindow(800, 600, "triangle");
    if (window == nullptr)
    {
        return;
    }

    handy_loadGlad();
    handy_loadViewport(window);
    triangleMainLoop(window);
}
