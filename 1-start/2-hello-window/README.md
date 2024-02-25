### 窗口！

运行 hello-window.cpp

首先通过 glfwInit 和 glfwWindowHint 初始化 GLFW 库

接下来通过 glfwCreateWindow 创建一个窗口对象，参数分别是宽、高和窗口标题

再初始化 glad，初始化 Viewport

### 渲染

我们希望程序持续渲染，因此创建一个 render 循环

其中 pollEvents 用于处理窗口事件，swapBuffers 用于交换颜色缓冲

即 pollEvents 用于处理用户输入，swapBuffers 用于显示渲染结果

### 最终

最后通过 glfwTerminate 释放 GLFW 资源

### add1. 监听 INPUT

通过 handy_event_processInput 函数

判断如果按下某个键就退出

### add2. 尝试加入 glClearColor

通过 glClearColor 函数设置清空屏幕所用的颜色

并插入在 rendering loop 中