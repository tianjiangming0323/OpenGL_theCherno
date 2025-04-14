////test 1
////render a rectangle with different colors in four angles and interpolate
//
//
//#include "GL/glew.h"
//#include "GLFW/glfw3.h"
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//
//#define ASSERT(x) if (!(x)) __debugbreak();
////如果x为假，则打断点
//
//#define GLCALL(x) GLClearError();\
//                  x;\
//                  ASSERT(GLLogCall(#x, __FILE__, __LINE__))
//
//static void GLClearError()
//{
//    while (glGetError() != GL_NO_ERROR);
//
//}
//
//static bool GLLogCall(const char* function, const char* file, int line)
//{
//    while (GLenum error = glGetError())
//    {
//        std::cout << "[OpenGL Error] (" << error << "):" << function << " " << file << ":" << line << std::endl;
//        return false;
//    }
//    return true;
//}
//
//
//static unsigned int CompileShader(unsigned int type, const std::string& source)
//{
//    unsigned int id = glCreateShader(type);
//   
//    const char* src = source.c_str();
//  
//    GLCALL(glShaderSource(id, 1, &src, nullptr));
//   
//    GLCALL(glCompileShader(id));
//    
//
//    int result;
//    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
//    
//    if (result == GL_FALSE)
//    {
//        int length;
//        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
//       
//        char* message = (char*)alloca(length * sizeof(char));
//        GLCALL(glGetShaderInfoLog(id, length, &length, message));
//
//        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
//        std::cout << message << std::endl;
//    }
//
//    return id;
//}
//
//
//static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
//{
//    unsigned int program = glCreateProgram();
//
//    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//
//
//    GLCALL(glAttachShader(program, vs));
//    GLCALL(glAttachShader(program, fs));
//    GLCALL(glLinkProgram(program));
//    GLCALL(glValidateProgram(program));
//    GLCALL(glDeleteShader(vs));
//    GLCALL(glDeleteShader(fs));
//    
//    return program;
//}
//
//int main(void)
//{
//    GLFWwindow* window;
//
//    if (!glfwInit())
//        return -1;
//
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);   
//   
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
//   
//    window = glfwCreateWindow(480, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//
//    glfwSwapInterval(1);
//
//    if (glewInit() != GLEW_OK)
//        std::cout << "Error !" << std::endl;
//
//
//    std::cout << glGetString(GL_VERSION) << std::endl;
//
//    float vertexAttribute[] =
//    {
//        //位置              颜色
//        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 右上
//        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 右下
//       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // 左下
//       -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f  // 左上
//
//    };
//
//    unsigned int indices[] =
//    {
//        0, 1, 3,
//        1, 2, 3
//    };
//
//    unsigned int vao;
//    GLCALL(glGenVertexArrays(1, &vao));
//    GLCALL(glBindVertexArray(vao));
//
//    unsigned int buffer;
//    GLCALL(glGenBuffers(1, &buffer));
//   
//    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
//    GLCALL(glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertexAttribute, GL_STATIC_DRAW));
//   
//    unsigned int ibo;   
//    GLCALL(glGenBuffers(1, &ibo));
//    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
//    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));
//
//    //位置
//    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0));   
//    GLCALL(glEnableVertexAttribArray(0));
//
//    //颜色
//    GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float))));
//    GLCALL(glEnableVertexAttribArray(1));
//
//     std::string vertexShader =
//        "#version 330 core\n"
//        "\n"
//        "layout(location = 0) in vec4 position; \n"
//        "layout(location = 1) in vec3 color; \n"
//        "\n"
//        "out vec3 vertexColor;\n"
//        "void main()\n"
//        "{ \n"
//        "   gl_Position = position; \n"
//        "   vertexColor = color; \n"
//        "}\n";
//
//
//    std::string fragmentShader =
//        "#version 330 core\n"
//        "\n"
//        "in vec3 vertexColor; \n"
//        "out vec4 finalColor; \n"
//        "\n"
//        "void main()\n"
//        "{ \n"
//        "  finalColor = vec4(vertexColor, 1.0); \n"
//        "}\n"; 
//    
//    
//
//    unsigned int shader = CreateShader(vertexShader, fragmentShader);
//    GLCALL(glUseProgram(shader));
//
//
//
//    GLCALL(glUseProgram(0));
//    GLCALL(glBindVertexArray(0));
//    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
//    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
//
//
//    while (!glfwWindowShouldClose(window))
//    {
//
//        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
//
//
//        GLCALL(glUseProgram(shader));
//        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
//        GLCALL(glBindVertexArray(vao));
//
//       
//
//        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
//       
//        
//      
//        glfwSwapBuffers(window);
//
//       
//        glfwPollEvents();
//    }
//
//    GLCALL(glDeleteProgram(shader));
//
//    glfwTerminate();
//    return 0;
//}