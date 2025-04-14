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
			//λ��              ��ɫ
			0.5f,  0.5f, 0.0f, m_Color1[0],  m_Color1[1],  m_Color1[2], // ����
			0.5f, -0.5f, 0.0f, m_Color2[0],  m_Color2[1],  m_Color2[2], // ����
		   -0.5f, -0.5f, 0.0f, m_Color3[0],  m_Color3[1],  m_Color3[2], // ����
		   -0.5f,  0.5f, 0.0f, m_Color4[0],  m_Color4[1],  m_Color4[2]  // ����

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
			//λ��              ��ɫ
			 0.5f,  0.5f, 0.0f, m_Color1[0], m_Color1[1], m_Color1[2], // ����
			 0.5f, -0.5f, 0.0f, m_Color2[0], m_Color2[1], m_Color2[2], // ����
			-0.5f, -0.5f, 0.0f, m_Color3[0], m_Color3[1], m_Color3[2], // ����
			-0.5f,  0.5f, 0.0f, m_Color4[0], m_Color4[1], m_Color4[2]  // ����
		};
			

		// �󶨶��㻺��������������
		m_vb->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexAttribute), vertexAttribute);
		//glBufferSubData �� OpenGL �����ڸ��»����������綥�㻺���������ֻ�ȫ�����ݵĺ���
		//���Զ�̬�޸��Ѵ��ڵĻ���������
		//void glBufferSubData(
		//	GLenum target,          ������Ŀ�꣨�� GL_ARRAY_BUFFER��
		//	GLintptr offset,        ���ݸ��µ���ʼλ�ã��ֽڵ�λ��
		//	GLsizeiptr size,        Ҫ���µ����ݴ�С���ֽڵ�λ��
		//	const void* data        �����ݵ�ָ��
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

//�ڲ�дOnUpdate()����ǰ  
//��Ҫ��VertexBuffer�е�GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW))  �ĳ�GL_DYNAMIC_DRAW
//Test���û���⣬���޷��ı�Rectangle��ɫ
//��Ϊ���㻺��������ɫ�����ǹ̶�����ֵ���� m_Color1[0] ��ʼΪ1.0��������� m_Color �������޸��޹�