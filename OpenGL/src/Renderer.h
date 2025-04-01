#pragma once
#include "GL/glew.h"


#define ASSERT(x) if (!(x)) __debugbreak();
//���xΪ�٣����ϵ�

#define GLCALL(x) GLClearError();\
                  x;\
                  ASSERT(GLLogCall(#x, __FILE__, __LINE__))



//S10
void GLClearError();


//S10
//static void GLCheckError()
//{
//    while (GLenum error = glGetError())
//    {
//        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
//    }
//}

 bool GLLogCall(const char* function, const char* file, int line);



