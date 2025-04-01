#include "Renderer.h"
#include <iostream>

//S10
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
    //判断调用该函数之前的代码有没有错误
    //如果有错误就会陷入死循环
}

//S10
//static void GLCheckError()
//{
//    while (GLenum error = glGetError())
//    {
//        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
//    }
//}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "):" << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}
