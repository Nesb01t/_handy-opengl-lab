//
// Created by nes on 2024/2/26.
//
#include "glad/glad.c"
#include "GLFW/glfw3.h"
#include "log.h"

/**
 * \brief 初始化 glfw
 */
void handy_initGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

/**
* \brief 创建窗口
*/
GLFWwindow* handy_createWindow(const int& width, const int& height, const char* windowName)
{
    GLFWwindow* window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    if (window == nullptr)
    {
        log("glfw: window create failed");
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    return window;
}

/**
 * \brief 加载 glad
 * \return 0 成功 -1 失败
 */
int handy_loadGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log("glad: load failed");
        return -1;
    }
    return 0;
}

/**
* \brief 加载视口
*/
void handy_cb_loadViewport(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void handy_loadViewport(GLFWwindow* window)
{
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, handy_cb_loadViewport);
}
