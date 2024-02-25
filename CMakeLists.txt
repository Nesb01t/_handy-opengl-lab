cmake_minimum_required(VERSION 3.15)
project(build)

add_compile_definitions(GLAD_STATIC)

link_directories(lib)
set(OpenGLLibs glfw3 opengl32)

include_directories(include)
include_directories(common)

add_executable(build intro.cpp
        1-start/1-create-window/create-window.cpp
        common/log.h
        common/log.cpp
        1-start/2-hello-window/hello-window.cpp
        1-start/2-hello-window/hello-window.h)

target_link_libraries(build ${OpenGLLibs})