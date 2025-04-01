#include "Renderer.h"
#include <iostream>

//S10
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
    //�жϵ��øú���֮ǰ�Ĵ�����û�д���
    //����д���ͻ�������ѭ��
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
