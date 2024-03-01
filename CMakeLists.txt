cmake_minimum_required(VERSION 3.15)
project(build)
set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(GLAD_STATIC)

link_directories(lib)
set(OpenGLLibs glfw3 opengl32)

include_directories(include)
include_directories(common)
include_directories(constant)
include_directories(lab)

add_executable(build intro.cpp
        common/log.h
        common/log.cpp
        common/setup.h
        common/setup.h
        common/setup.h
        common/setup.cpp
        lab/1-start/3-triangle/triangle.cpp
        lab/1-start/3-triangle/triangle.h
        common/glsl-reader.h
        common/glsl-reader.cpp
        lab/1-start/4-shaders/timed-triangle.cpp
        lab/1-start/4-shaders/timed-triangle.h)

target_link_libraries(build ${OpenGLLibs})