#include "TestRectangle.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
	TestRectangle::TestRectangle()
		: m_Color1{ 1.0f, 0.0f, 0.0f, 1.0f },
		  m_Color2{ 1.0f, 0.0f, 0.0f, 1.0f },
		  m_Color3{ 1.0f, 0.0f, 0.0f, 1.0f },
		  m_Color4{ 1.0f, 0.0f, 0.0f, 1.0f }
	{

		float vertexAttribute[] =
		{
			//位置              颜色
			0.5f,  0.5f, 0.0f, m_Color1[0],  m_Color1[1],  m_Color1[2], // 右上
			0.5f, -0.5f, 0.0f, m_Color2[0],  m_Color2[1],  m_Color2[2], // 右下
		   -0.5f, -0.5f, 0.0f, m_Color3[0],  m_Color3[1],  m_Color3[2], // 左下
		   -0.5f,  0.5f, 0.0f, m_Color4[0],  m_Color4[1],  m_Color4[2]  // 左上

		};

		unsigned int indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_va = std::make_unique<VertexArray>();
		m_ib = std::make_unique<IndexBuffer>(indices, 6);
		m_Shader = std::make_unique<Shader>("res/shaders/TestRectangle.shader");

		m_vb = std::make_unique<VertexBuffer>(vertexAttribute, 4 * 6 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);

		m_va->AddBuffer(*m_vb, layout);
		m_Shader->Bind();

		
	}

	TestRectangle::~TestRectangle()
	{

	}

	void TestRectangle::OnUpdate(float deltaTime)
	{
		float vertexAttribute[] =
		{
			//位置              颜色
			 0.5f,  0.5f, 0.0f, m_Color1[0], m_Color1[1], m_Color1[2], // 右上
			 0.5f, -0.5f, 0.0f, m_Color2[0], m_Color2[1], m_Color2[2], // 右下
			-0.5f, -0.5f, 0.0f, m_Color3[0], m_Color3[1], m_Color3[2], // 左下
			-0.5f,  0.5f, 0.0f, m_Color4[0], m_Color4[1], m_Color4[2]  // 左上
		};
			

		// 绑定顶点缓冲区并更新数据
		m_vb->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexAttribute), vertexAttribute);
		//glBufferSubData 是 OpenGL 中用于更新缓冲区对象（如顶点缓冲区）部分或全部数据的函数
		//可以动态修改已存在的缓冲区内容
		//void glBufferSubData(
		//	GLenum target,          缓冲区目标（如 GL_ARRAY_BUFFER）
		//	GLintptr offset,        数据更新的起始位置（字节单位）
		//	GLsizeiptr size,        要更新的数据大小（字节单位）
		//	const void* data        新数据的指针
		//);

	}

	void TestRectangle::OnRender()
	{
		GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		renderer.Draw(*m_va, *m_ib, *m_Shader);
	}


	void TestRectangle::OnImGuiRender()
	{
		ImGui::ColorEdit4("Set ColorRT", m_Color1);
		ImGui::ColorEdit4("Set ColorRD", m_Color2);
		ImGui::ColorEdit4("Set ColorLD", m_Color3);
		ImGui::ColorEdit4("Set ColorLT", m_Color4);

		
	}
}

//在不写OnUpdate()函数前  
//还要将VertexBuffer中的GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW))  改成GL_DYNAMIC_DRAW
//Test框架没问题，但无法改变Rectangle颜色
//因为顶点缓冲区的颜色数据是固定的数值（如 m_Color1[0] 初始为1.0），与后续 m_Color 变量的修改无关