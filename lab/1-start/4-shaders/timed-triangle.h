//
// Created by nes on 2024/2/26.
//

#ifndef TIMED_TRIANGLE_H
#define TIMED_TRIANGLE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class TimedTriangle
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
#endif //TIMED_TRIANGLE_H
