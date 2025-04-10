#include "Test.h"
#include "imgui/imgui.h"

namespace test
{
	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_currentTest(currentTestPointer)
	{

	}


	TestMenu::~TestMenu()
	{

	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
				m_currentTest = test.second();
			    //ImGui ����ģʽ GUI �����ԣ�
				//ÿ֡���� ImGui::Button ʱ����ʵʱ�� UI �д�����ť��
				//����ť�����ʱ��ImGui::Button ���� true�����������ڵ��߼���
		}
	}


}