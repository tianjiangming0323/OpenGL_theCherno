#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

//S4 OpenGL是一个函数接口，具体的函数实现是写在显卡驱动上的
//将openGL看做一个状态机   状态机里已经有例如buffer（数据）和shader
//在渲染时告诉OpenGL选择这个buffer和shader渲染个三角形出来
//OpenGL根据buffer和shader决定绘制怎样的三角形，绘制在哪里

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //设置上下文
    glfwMakeContextCurrent(window);


    //S3 要成功调用glewInit需要再OpenGL project -> Properties -> C/C++ -> Preprocessor -> Preprocessor Definition 中定义GLEW_STATIC
    //原因 glewInit函数需要，自个儿在函数定义里去找吧（需要定义GLEWAPI， 然后是GLEW_STATIC
    if (glewInit() != GLEW_OK)
        std::cout << "Error !" << std::endl;
    //glew函数的调用必须在设置openGL上下文之后

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[6] =
    {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    //该函数接受两个参数，第一个是生成的buffer数量，第二个参数是buffer的唯一标识符（无符号整形）
    //OpenGL中所有生成的东西都会被分配一个唯一整数标识符
    //GLuint buffers[3];
    //glGenBuffers(3, buffers); // 生成 3 个缓冲对象名称
    //使用 buffers[0], buffers[1], buffers[2] 分别操作
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    //循环一直存在 直到用户关闭window
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /*glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.0f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();*/
        //S2 glBegin和glEnd是Legacy OpenGL
        //Modern OpenGL的步骤
        //创建顶点缓冲区,包含这些顶点数据，将buffer传到OpenGL的VRAM
        //发出DrawCall OpenGL根据缓冲中的数据进行渲染

        glDrawArrays(GL_TRIANGLES, 0, 3);
        //S4 这里有个问题，OpenGL是怎么知道该渲染哪个buffer里的数据呢
        //答：bind的是哪个，就渲染哪个，因为OpenGL是上下文相关的
        //最好的gl学习文档docs.gl

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}