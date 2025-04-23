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
//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw_gl3.h"
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
//        float positionsAndUV[] =
//        {
//          //position(2) uv(2)       
//          -0.5f, -0.5f, 0.0f, 0.0f, 
//           0.5f, -0.5f, 1.0f, 0.0f, 
//           0.5f,  0.5f, 1.0f, 1.0f, 
//          -0.5f,  0.5f, 0.0f, 1.0f, 
//
//          -1.5f, -1.5f, 0.0f, 0.0f, 
//          -0.5f, -1.5f, 1.0f, 0.0f, 
//          -0.5f, -0.5f, 1.0f, 1.0f, 
//          -1.5f, -0.5f, 0.0f, 1.0f
//        };
//
//        float positionsAndColor[] =
//        {
//            //position(2) color(3)       
//            -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
//             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
//             0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
//            -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
//
//            -1.5f, -1.5f, 0.5f, 0.0f, 0.2f,
//            -0.5f, -1.5f, 0.7f, 1.0f, 0.1f,
//            -0.5f, -0.5f, 0.2f, 0.0f, 1.0f,
//            -1.5f, -0.5f, 1.0f, 1.0f, 0.8f
//        };
//
//        //S30Ìí¼Ó
//        float positionsAndColorAndUVAndIndex[] =
//        {
//            //position(2) color(3)          UV(2)       IndexOfTexture(1)
//            -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//             0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//            -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//
//            -1.5f, -1.5f, 0.5f, 0.0f, 0.2f, 0.0f, 0.0f, 1.0f,
//            -0.5f, -1.5f, 0.7f, 1.0f, 0.1f, 1.0f, 0.0f, 1.0f,
//            -0.5f, -0.5f, 0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//            -1.5f, -0.5f, 1.0f, 1.0f, 0.8f, 0.0f, 1.0f, 1.0f
//        };
//                
//           
//        unsigned int indices[] =
//        {
//            0, 1, 2,
//            2, 3, 0,
//
//            4, 5, 6,
//            6, 7, 4
//        };
//
//        GLCALL(glEnable(GL_BLEND));
//        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//
//
//        VertexArray va;
//        VertexBufferLayout layout;
//        layout.Push<float>(2);
//        layout.Push<float>(3);
//        layout.Push<float>(2);
//        layout.Push<float>(1);
//        
//
//        VertexBuffer vb(positionsAndColorAndUVAndIndex, 8 * 8 * sizeof(float));
//        IndexBuffer ib(indices, 12);
//        va.AddBuffer(vb, layout);
//
//
//        //Shader shader("res/shaders/TextureShader.shader");
//        Shader shader("res/shaders/TextureShaderBatching.shader");
//        shader.Bind();
//
//        Texture texture("res/textures/pic.png");
//        Texture texture1("res/textures/pic1.png");
//        texture.Bind(0);
//        texture1.Bind(1);
//
//        shader.SetUniform1i("u_Texture1", 0);
//        shader.SetUniform1i("u_Texture2", 1);
//
//        int array[2] = { 0,1 };
//        shader.SetUniformArrayInt("u_Texture", 2, array);
//
//
//        shader.Unbind();
//        va.Unbind();
//        ib.Unbind();
//        vb.Unbind();
//
//        Renderer renderer;
//
//
//        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
//        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-1, 0, 0));
//        glm::vec3 translationA(2.0f, 0.5f, 0.0f);
//
//        ImGui::CreateContext();
//        ImGui_ImplGlfwGL3_Init(window, true);
//        ImGui::StyleColorsDark();
//
//
//        float r = 0.0f;
//
//        while (!glfwWindowShouldClose(window))
//        {
//
//            renderer.Clear();
//
//            ImGui_ImplGlfwGL3_NewFrame();
//
//            shader.Bind();
//            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
//
//            {
//                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
//                glm::mat4 mvp = proj * view * model;
//                shader.SetUnifromMat4f("u_MVP", mvp);
//
//                renderer.Draw(va, ib, shader);
//            }
//
//
//            ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 1.0f);
//            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//            ImGui::Render();
//            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
//
//
//            glfwSwapBuffers(window);
//            glfwPollEvents();
//        }
//
//    }
//
//    ImGui_ImplGlfwGL3_Shutdown();
//    ImGui::DestroyContext();
//
//    glfwTerminate();
//    return 0;
//}