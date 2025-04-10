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
			    //ImGui 立即模式 GUI 的特性：
				//每帧调用 ImGui::Button 时，会实时在 UI 中创建按钮。
				//当按钮被点击时，ImGui::Button 返回 true，触发条件内的逻辑。
		}
	}


}