#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>

namespace test
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};



	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test" << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}

	private:
		Test*& m_currentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
		//m_Tests是一个vector
		//vector中存一个pair
		//pair是由一个string和一个function构成的
		//这个function为一个返回 Test*的无参函数
	};
}