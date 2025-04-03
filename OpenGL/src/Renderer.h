#pragma once
#include "GL/glew.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


#define ASSERT(x) if (!(x)) __debugbreak();
//如果x为假，则打断点

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


//S16
 class Renderer
 {
 public:
     void Clear() const;
     void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
 };
