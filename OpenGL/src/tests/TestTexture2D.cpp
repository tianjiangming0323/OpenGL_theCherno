#include "TestTexture2D.h"
#include "Renderer.h"
#include "imgui/imgui.h"

#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"



namespace test
{
	TestTexture2D::TestTexture2D()
        : m_TranslationA{ 2.0f, 0.5f, 0.0f }, m_TranslationB{ -2.0f, 0.5f, 0.0f },
        m_Proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(-1, 0, 0)))
	{
        float positions[16] =
        {
          -0.5f, -0.5f, 0.0f, 0.0f,
           0.5f, -0.5f, 1.0f, 0.0f,
           0.5f,  0.5f, 1.0f, 1.0f,
          -0.5f,  0.5f, 0.0f, 1.0f,
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_Shader = std::make_unique<Shader>("res/shaders/TextureShader.shader");
        m_VAO = std::make_unique<VertexArray>();
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        //VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        //最开始没有将vb写成类成员变量
        //结果就是会出现报错（报错类型有些复杂，自己到时候重现一下吧）
        //原因是非类成员变量会在该作用域（此处即为构造函数）结束时释放——即调用析构函数，导致VertexBuffer为空
        //而VertexArray中记录的是VertexBuffer中数据的配置
        //注意：只是顶点数据配置，没有顶点数据本身
        //所以当顶点数据被释放后，出现错误
        //故需要将VertexBuffer设置为类成员变量
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_Shader->Bind();
        m_Shader->SetUniform1i("u_Texture", 0);

        m_Texture = std::make_unique<Texture>("res/textures/pic.png");
        
	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		GLCALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        m_Texture->Bind();


        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->SetUnifromMat4f("u_MVP", mvp);

            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->SetUnifromMat4f("u_MVP", mvp);

            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
		
	}

	void TestTexture2D::OnImGuiRender()
	{
        ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 1.0f);
        ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 1.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}