//
// Created by nes on 2024/2/26.
//
#include "glad/glad.c"
#include "GLFW/glfw3.h"
#include "log.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void handy_initGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

GLFWwindow* handy_createWindow()
{
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == nullptr)
    {
        log("glfw: window create failed");
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    return window;
}

int handy_loadGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log("glad: load failed");
        return -1;
    }
    return 0;
}

void handy_loadViewport(GLFWwindow* window)
{
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void handy_event_processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int helloWindow()
{
    handy_initGlfw();
    auto window = handy_createWindow();
    handy_loadGlad();
    handy_loadViewport(window);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        handy_event_processInput(window);

        // rendering command here. main loop
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}
