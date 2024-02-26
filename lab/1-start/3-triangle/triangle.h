//
// Created by nes on 2024/2/26.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Triangle
{
    static void triangleMainLoop(GLFWwindow* window);

    static unsigned int createVBO();
    static unsigned int createVAO();

    static unsigned int createVertexShader();
    static unsigned int createFragmentShader();

    static unsigned int createShaderProgram();

public:
    static void run();
};
#endif //TRIANGLE_H
