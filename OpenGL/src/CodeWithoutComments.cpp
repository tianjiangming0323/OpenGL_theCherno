//#include "GL/glew.h"
//#include "GLFW/glfw3.h"
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//
//#include "Renderer.h"
//#include "IndexBuffer.h"
//#include "VertexBuffer.h"
//#include "VertexArray.h"
//#include "VertexBufferLayout.h"
//#include "Shader.h"
//#include "Texture.h"
//
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//
//
//int main(void)
//{
//    GLFWwindow* window;
//    
//    if (!glfwInit())
//        return -1;
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);   
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
//
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//   
//    glfwMakeContextCurrent(window);
//    
//    glfwSwapInterval(1);
//    
//    if (glewInit() != GLEW_OK)
//        std::cout << "Error !" << std::endl;
//
//    std::cout << glGetString(GL_VERSION) << std::endl;
//
//    {
//        float positions[16] =
//        {
//          -0.5f, -0.5f, 0.0f, 0.0f,
//           0.5f, -0.5f, 1.0f, 0.0f,
//           0.5f,  0.5f, 1.0f, 1.0f,
//          -0.5f,  0.5f, 0.0f, 1.0f,        
//        };
//   
//        unsigned int indices[] =
//        {
//            0, 1, 2,
//            2, 3, 0
//        };
// 
//        GLCALL(glEnable(GL_BLEND));
//        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//
//
//        VertexArray va;
//        VertexBufferLayout layout;
//        layout.Push<float>(2);
//        layout.Push<float>(2);
//       
//        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
//        IndexBuffer ib(indices, 6);
//
//        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
//        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-1, 0, 0)); 
//        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(2, 0.5, 0));
//        glm::mat4 mvp =  proj * view * model;
//
//        va.AddBuffer(vb, layout);
//
//        
//        Shader shader("res/shaders/TextureShader.shader");
//        shader.Bind();
// 
//		Texture texture("res/textures/pic.png");
//        texture.Bind();
//        shader.SetUniform1i("u_Texture", 0);
//        
//        shader.SetUnifromMat4f("u_MVP", mvp);
//
//        shader.Unbind();
//        va.Unbind();
//        ib.Unbind();
//        vb.Unbind();
//
//        Renderer renderer;
//
//
//        float r = 0.0f;
//        float increment = 0.05f;
//
// 
//        while (!glfwWindowShouldClose(window))
//        {
//
//            renderer.Clear();
//
//           
//            shader.Bind();
//            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
//            
//            renderer.Draw(va, ib, shader);
//
//
//            
//            if (r > 1.0f)
//            {
//                increment = -0.05f;
//            }
//            else if (r < 0.0f)
//            {
//                increment = 0.05f;
//            }
//            r += increment;
//
//           
//            glfwSwapBuffers(window);
//            glfwPollEvents();
//        }
//       
//    }
//   
//
//    glfwTerminate();
//    return 0;
//}