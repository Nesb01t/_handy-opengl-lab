#include "timed-triangle.h"

#include <cmath>
#include "data.h"
#include "glsl-reader.h"
#include "log.h"
#include "setup.h"
//
// Created by nes on 2024/2/26.
//
void TimedTriangle::triangleMainLoop(GLFWwindow* window)
{
    auto VAO = createVAO();
    auto shaderProgram = createShaderProgram();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // main
        glUseProgram(shaderProgram);

        // update the uniform color
        float timeValue = glfwGetTime();
        float greenValue = std::sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 1.0f - greenValue, greenValue, 0.5f * greenValue, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

unsigned int TimedTriangle::createVBO()
{
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    return VBO;
}

unsigned int TimedTriangle::createVAO()
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = createVBO();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return VAO;
}

unsigned int TimedTriangle::createVertexShader()
{
    const std::string vertexShaderSource = readShader(
        R"(C:\Users\nes\_handy-opengl-lab\shader\vertex-shader__uniform.glsl)");
    const char* sourcePtr = vertexShaderSource.c_str();

    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &sourcePtr, nullptr);
    glCompileShader(vertexShader);

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

unsigned int TimedTriangle::createFragmentShader()
{
    const std::string fragmentShaderSource = readShader(
        R"(C:\Users\nes\_handy-opengl-lab\shader\fragment-shader__uniform.glsl)");
    const char* sourcePtr = fragmentShaderSource.c_str();

    const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &sourcePtr, nullptr);
    glCompileShader(fragmentShader);

    return fragmentShader;
}


unsigned int TimedTriangle::createShaderProgram()
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
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void TimedTriangle::run()
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
