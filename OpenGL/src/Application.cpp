#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

//S4 OpenGL是一个函数接口，具体的函数实现是写在显卡驱动上的
//将openGL看做一个状态机   状态机里已经有例如buffer（数据）和shader
//在渲染时告诉OpenGL选择这个buffer和shader渲染个三角形出来
//OpenGL根据buffer和shader决定绘制怎样的三角形，绘制在哪里

//S7
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    //创建着色器对象
    const char* src = source.c_str();
    //设置着色器源码
    //将 C++ 标准字符串（std::string）转换为 C 风格字符串
    //OpenGL是基于 C 语言设计的，它们的函数参数通常需要 const char* 类型
    glShaderSource(id, 1, &src, nullptr);
    //将源码绑定到着色器对象
    //glShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length)
    //shader:着色器对象 ID
    //count:指定源码字符串的数量。如果源码是单条字符串（常见情况），设为 1；若源码分多段（如多行代码），设为对应的分段数
    //string:着色器源码,类型需要 const char**（指针数组的指针），src的类型为char*，故需要输入&src
    //length:字符串长度数组指针.如果为 nullptr，OpenGL 会假设每个字符串以 \0 结尾，自动计算长度
    glCompileShader(id);
    //编译着色器

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    //glGetShaderiv(GLuint shader,GLenum pname,GLint* params);
    //shader:着色器对象ID
    //pname:要查询的状态类型
    //存储查询结果的变量地址(当查询的状态为GL_COMPILE_STATUS)

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        //返回着色器信息日志中的字符数
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        //将错误日志内容读取到指定的缓冲区
        //glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
        //shader:着色器对象ID
        //maxLength:缓冲区的最大容量（应与 GL_INFO_LOG_LENGTH 获取的值一致
        //length:输出实际写入的日志长度（可忽略，直接传 nullptr
        //message:存储错误日志的缓冲区指针

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
    }

    return id;
}

//S7
//创建完整的着色器程序，编译并链接着顶点和片段着色器，最终返回程序对象 ID
static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    //创建着色器程序，空程序对象
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    //编译顶点和片段着色器

    glAttachShader(program, vs);// 附加顶点着色器
    glAttachShader(program, fs);// 附加片段着色器
    glLinkProgram(program);// 链接程序
    glValidateProgram(program);// 验证程序有效性（可选，调试用）

    glDeleteShader(vs);
    glDeleteShader(fs);
    //删除已链接的着色器对象
    return program;
}

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

    //S7
    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";


    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color; \n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0 ,0.0, 1.0);\n"
        "}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);
  
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

    //S7
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}