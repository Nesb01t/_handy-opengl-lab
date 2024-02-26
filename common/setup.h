//
// Created by nes on 2024/2/26.
//

#ifndef SETUP_H
#define SETUP_H
#include <GLFW/glfw3.h>
void handy_initGlfw();
GLFWwindow* handy_createWindow(const int& width, const int& height, const char* windowName);
int handy_loadGlad();
void handy_loadViewport(GLFWwindow* window);
#endif //SETUP_H
