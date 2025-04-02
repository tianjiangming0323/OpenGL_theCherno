#pragma once
#include <vector>
#include <GL/glew.h>
#include "Renderer.h"


struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:           return 4;
			case GL_UNSIGNED_INT:    return 4;
			case GL_UNSIGNED_BYTE:   return 1;
		}
		ASSERT(false);
		return 0;
	}

};


class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout()
		: m_Stride(0) {}

	//S14 模版主版本 + 显式特化
	//代码中调用 Push<T>(count) 时，编译器会按照以下优先级选择要使用的模板版本
	//1.精确匹配的显式特化版本
	//2.主模版版本
	template<typename T>
	void Push(unsigned int count)
	{
		//static_assert(false);
		// C++ 编译器在 首次解析模板代码时 会立即处理所有 不依赖模板参数 的静态断言，无论模板是否被实际使用
		// 
		// 通过将断言条件改为 依赖模板参数 的表达式，编译器会推迟检查到 模板实例化时
		// 如下
		static_assert(sizeof(T) == 0, "Unsupported type");
	}
	//当用户尝试使用 未被显式特化的类型（如 double、int）调用 Push 时，触发编译错误，提示不支持的类型

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE});
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};
