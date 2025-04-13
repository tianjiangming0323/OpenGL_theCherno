#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"


namespace test
{
	TestClearColor::TestClearColor()
		: m_ClearColor{1.0f, 1.0f, 1.0f, 1.0f}
	{
		
	}

	TestClearColor::~TestClearColor()
	{

	}

	void TestClearColor::OnUpdate(float deltaTime)
	{

	}

	void TestClearColor::OnRender()
	{
		GLCALL(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		//���������ɫ������ʱʹ�õ� RGBA ��ɫֵ
		//�ú�������ִ�����������ֻ�Ƕ������ glClear ʹ�õ���ɫ
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
		//���ָ���Ļ���������������ɫ������
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		//����ImGui ������ɫ��RGBAֵ
	}
}