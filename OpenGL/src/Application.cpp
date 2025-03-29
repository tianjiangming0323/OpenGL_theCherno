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

  
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    //S5 设置顶点属性
    //设置两个例子，上面的positions[6]为例1
    //再设置一个顶点属性struct，一个顶点有3个float为position，2个float为uv，3个float为normal
    //glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
    //index:对于例2，position为0，uv为1，normal为2
    //size: 取值只能为1，2，3，4      例1中position为2，例2中position为3，uv为2，normal为3    ————————即每个属性有几个值
    //type: 数据类型，GL_FLOAT
    //normalized: 是否需要归一化   GL_TRUE/GL_FALSE
    //stride:顶点到顶点之间的偏移量。例1中，从顶点1到顶点2需要跨过两个float；例2中从顶点1到顶点2需要跨过3+2+3个float
    //pointer:每一个顶点中，某属性的起点位置  例1中，position为0；例2中，position为0、uv为12、normal为20
    glEnableVertexAttribArray(0);
    //参数index：顶点属性的位置索引（例如 0 表示顶点位置，1 表示法线等）
  
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