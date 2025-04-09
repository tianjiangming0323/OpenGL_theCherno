#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"


int main(void)
{
    GLFWwindow* window;
    
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);   
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

   
    glfwMakeContextCurrent(window);
    
    glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK)
        std::cout << "Error !" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();
   

        //S24���
        test::TestClearColor test;
 
        while (!glfwWindowShouldClose(window))
        {

            renderer.Clear();

            //S24���
            test.OnUpdate(0.0f);
            test.OnRender();


            ImGui_ImplGlfwGL3_NewFrame();
           

            //S24���
            test.OnImGuiRender();

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

           
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
       
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}