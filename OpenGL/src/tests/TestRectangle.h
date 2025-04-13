#pragma once
#include "Test.h"
#include "Renderer.h"
#include <memory>

namespace test
{
	class TestRectangle : public Test
	{
	public:
		TestRectangle();
		virtual ~TestRectangle();

		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();
		virtual void OnImGuiRender();


	private:
		std::unique_ptr<VertexArray> m_va;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_vb;

		float m_Color1[4];
		float m_Color2[4];
		float m_Color3[4];
		float m_Color4[4];
	};
}
