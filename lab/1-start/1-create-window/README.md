### 流行的 OpenGL 库

例如 GLUT、SDL、SFML、GLFW，其中教程选择了 GLFW

GLFW 是用 C 写的，允许我们创建上下文，定义参数，处理输入

在这里下载 GLFW 的源码，自行编译感受一下 https://www.glfw.org/download.html


### CMake

并非每个人都有相同的 IDE 或者 Build 系统，因此需要 CMake

在这里安装 CMake http://www.cmake.org/cmake/resources/software.html

安装成功后可以选择 '命令行' 或者 'GUI'，方便起见使用 GUI

CMake 需要一个源代码文件夹 和 一个构建目标文件夹

- 源代码文件夹选择 GLFW 源码包文件夹
- 目标文件夹可以创建一个 build 目录，然后选择即可


### Compile

CMake 构建成功后打开 build 目录就可以看到一个 GLFW.sln 文件

用 VS 打开他构建即可，构建成功后会生成目录 build/src/Debug 里面有一个 glfw3.lib 文件

当我们生成库之后，确保 IDE 知道哪里可以找到 OpenGL 的包含文件

1. 找到 IDE 的 /lib 和 /include 文件夹，将 GLFW 的 include 文件夹添加到 /include 中；再将 glfw3.lib 添加到 /lib 中
2. (推荐) 在某个地方创建新目录，包含来自第三方库的所有头文件/库，每次创建新项目时告诉 IDE 这个目录在哪里

### 引用库

试着 include GLFW/glfw3.h 如果没有报错说明一切顺利

### OpenGL 库

如果使用的是 Windows，OpenGL 库 opengl32.lib 会和 Microsoft SDK 一起提供

不幸的是我们还需要加一个 GLAD 库来管理驱动和 OpenGL 之间的联系

完成之后 include glad/glad.h 仍应没有报错