#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

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


struct Vertex
{
    std::array<float, 2> Position;
    std::array<float, 3> Color;
    std::array<float, 2> UV;
    float IndexID;
    /* float Position[2];    Position不是可以赋值的左值
     float Color[3];
     float UV[2];
     float IndexID;*/
};


static std::array<Vertex, 4> CreateQuad(float x, float y, float index)
{
    float size = 1.0f;

    Vertex v0;
    v0.Position = { x, y };
    v0.Color = { 1.0f, 0.0f, 0.0f };
    v0.UV = { 0.0f, 0.0f };
    v0.IndexID = index;

    Vertex v1;
    v1.Position = { x + size, y };
    v1.Color = { 0.0f, 1.0f, 0.0f };
    v1.UV = { 1.0f, 0.0f };
    v1.IndexID = index;

    Vertex v2;
    v2.Position = { x + size, y + size };
    v2.Color = { 0.0f, 0.0f, 1.0f };
    v2.UV = { 1.0f, 1.0f };
    v2.IndexID = index;

    Vertex v3;
    v3.Position = { x, y + size };
    v3.Color = { 1.0f, 1.0f, 0.0f };
    v3.UV = { 0.0f, 1.0f };
    v3.IndexID = index;

    return { v0, v1,v2,v3 };
}


static Vertex* CreateQuadNew(Vertex* target, float x, float y, float index)
{
    float size = 1.0f;

    target->Position = { x, y };
    target->Color = { 1.0f, 0.0f, 0.0f };
    target->UV = { 0.0f, 0.0f };
    target->IndexID = index;
    target++;

    
    target->Position = { x + size, y };
    target->Color = { 0.0f, 1.0f, 0.0f };
    target->UV = { 1.0f, 0.0f };
    target->IndexID = index;
    target++;

    target->Position = { x + size, y + size };
    target->Color = { 0.0f, 0.0f, 1.0f };
    target->UV = { 1.0f, 1.0f };
    target->IndexID = index;
    target++;

    target->Position = { x, y + size };
    target->Color = { 1.0f, 1.0f, 0.0f };
    target->UV = { 0.0f, 1.0f };
    target->IndexID = index;
    target++;

    return target;
}


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
        const size_t MaxQuadCount = 1000;
        //size_t:无符号整数类型，专门用于表示 内存中对象的大小、数组索引 或 数量计数
        //为什么用 size_t 而不是 int 或 unsigned int
        //1.平台兼容性：
        //size_t 的大小会根据当前系统的寻址能力自动调整，确保能表示 系统中可能存在的最大对象的大小。
        //例如，在 64 位系统中，若用 unsigned int（4 字节）表示内存地址，可能导致溢出，而 size_t 会是 8 字节。
        //
        //2.标准库一致性：
        //C / C++ 标准库函数（如 strlen, malloc）和容器方法（如 vector::size()）返回 size_t，直接用它可避免类型转换。
        //
        //3.避免负数：
        //大小和索引不可能为负数，使用无符号类型 size_t 更符合逻辑
        const size_t MaxVertexCount = MaxQuadCount * 4;
        const size_t MaxIndexCount = MaxQuadCount * 6;


        /* unsigned int indices[] =
         {
             0, 1, 2,
             2, 3, 0,

             4, 5, 6,
             6, 7, 4
         };*/

        uint32_t indices[MaxIndexCount];
        size_t offset = 0;
        for (size_t i = 0; i < MaxIndexCount; i += 6)
        {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;

            offset += 4;

        }




        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        unsigned int m_QuadVA;
        GLCALL(glCreateVertexArrays(1, &m_QuadVA));
        GLCALL(glBindVertexArray(m_QuadVA));

        unsigned int m_QuadVB;
        GLCALL(glCreateBuffers(1, &m_QuadVB));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB));
        //GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MaxVertexCount, nullptr, GL_DYNAMIC_DRAW));

        GLCALL(glEnableVertexArrayAttrib(m_QuadVA, 0));
        GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position)));

        GLCALL(glEnableVertexArrayAttrib(m_QuadVA, 1));
        GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color)));

        GLCALL(glEnableVertexArrayAttrib(m_QuadVA, 2));
        GLCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, UV)));

        GLCALL(glEnableVertexArrayAttrib(m_QuadVA, 3));
        GLCALL(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, IndexID)));


        unsigned int m_QuadIB;
        GLCALL(glCreateBuffers(1, &m_QuadIB));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadIB));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));


        /*VertexArray va;
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(3);
        layout.Push<float>(2);
        layout.Push<float>(1);


        VertexBuffer vb(positionsAndColorAndUVAndIndex, 8 * 8 * sizeof(float));
        IndexBuffer ib(indices, 12);
        va.AddBuffer(vb, layout);*/


        //Shader shader("res/shaders/TextureShader.shader");
        Shader shader("res/shaders/TextureShaderBatching.shader");
        shader.Bind();

        Texture texture("res/textures/pic.png");
        Texture texture1("res/textures/pic1.png");
        texture.Bind(0);
        texture1.Bind(1);

        shader.SetUniform1i("u_Texture1", 0);
        shader.SetUniform1i("u_Texture2", 1);

        int array[2] = { 0,1 };
        shader.SetUniformArrayInt("u_Texture", 2, array);


        shader.Unbind();

        Renderer renderer;


        glm::mat4 proj = glm::ortho(-6.0f, 6.0f, -4.5f, 4.5f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-1, 0, 0));
        glm::vec3 translationA(2.0f, 0.5f, 0.0f);

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();


        float r = 0.0f;

        float x0 = 0.0f;
        float y0 = 0.0f;
        float x1 = -1.0f;
        float y1 = -1.0f;


        while (!glfwWindowShouldClose(window))
        {

            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);


            //S31添加
            //float positionsAndColorAndUVAndIndex[] =
            //{
            //    //position(2) color(3)          UV(2)       IndexOfTexture(1)
            //    -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            //     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            //     0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            //    -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            //    -1.5f, -1.5f, 0.5f, 0.0f, 0.2f, 0.0f, 0.0f, 1.0f,
            //    -0.5f, -1.5f, 0.7f, 1.0f, 0.1f, 1.0f, 0.0f, 1.0f,
            //    -0.5f, -0.5f, 0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            //    -1.5f, -0.5f, 1.0f, 1.0f, 0.8f, 0.0f, 1.0f, 1.0f
            //};

            uint32_t indexCount = 0;
            std::array<Vertex, 1000> vertices;
            Vertex* buffer = vertices.data();
            for (int y = 0; y < 5; y++)
            {
                for (int x = 0; x < 5; x++)
                {
                    buffer = CreateQuadNew(buffer, x, y, (x + y) % 2);
                    indexCount += 6;
                }
            }

            buffer = CreateQuadNew(buffer, x0, y0, 0.0f);
            buffer = CreateQuadNew(buffer, x1, y1, 0.0f);
            indexCount += 12;

           /* auto q0 = CreateQuad(x0, y0, 0.0f);
            auto q1 = CreateQuad(x1, y1, 1.0f);*/

            //void* memcpy(void* dest, const void* src, size_t count);
            //dest：目标内存地址（复制到哪）。
            //src：源内存地址（从哪复制）。
            //count：要复制的字节数（不是元素个数！）。
            //返回值：dest 的地址（一般可忽略）。
            // 
            //标准库容器（如 std::array、std::vector）提供 .data() 方法，返回容器底层存储数据的 裸指针（T*）。
            //这个指针指向容器第一个元素的内存地址
            // q0 的内存布局：
            //+---------------- + ---------------- + ---------------- + ---------------- +
            //| Vertex 0 | Vertex 1 | Vertex 2 | Vertex 3 |
            //+---------------- + ---------------- + ---------------- + ---------------- +
            //^
            //|
            //q0.data() 指向这里
            // 
            //q0.size() 返回元素个数（例如 4），而 sizeof(Vertex) 返回单个元素的大小
            /*Vertex vertices[8];
            memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
            memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));*/

            //自己的解决思路，没有改CreateQuad函数
            //但要改glDrawElements里的12，和上面Vertex Vertices[8]的数字8
            /* for (int m = 0; m < 10; m++)
            {
                auto qq = CreateQuad(-2.0f - m, -2.0f - m, 1.0f);
                memcpy(vertices + qq.size() * (2 + m), qq.data(), qq.size() * sizeof(Vertex));
            }*/

            //GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
            GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()));

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shader.SetUnifromMat4f("u_MVP", mvp);

                //GLCALL(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr));
                GLCALL(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
            }


            ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 1.0f);

            ImGui::SliderFloat("x0", &x0, 0.0f, 1.0f);
            ImGui::SliderFloat("y0", &y0, 0.0f, 1.0f);
            ImGui::SliderFloat("x1", &x1, 0.0f, 1.0f);
            ImGui::SliderFloat("y1", &y1, 0.0f, 1.0f);




            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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