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
		//设置清除颜色缓冲区时使用的 RGBA 颜色值
		//该函数本身不执行清除操作，只是定义后续 glClear 使用的颜色
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
		//清除指定的缓冲区（这里是颜色缓冲区
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		//利用ImGui 调控颜色的RGBA值
	}
}