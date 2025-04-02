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

	//S14 ģ�����汾 + ��ʽ�ػ�
	//�����е��� Push<T>(count) ʱ���������ᰴ���������ȼ�ѡ��Ҫʹ�õ�ģ��汾
	//1.��ȷƥ�����ʽ�ػ��汾
	//2.��ģ��汾
	template<typename T>
	void Push(unsigned int count)
	{
		//static_assert(false);
		// C++ �������� �״ν���ģ�����ʱ �������������� ������ģ����� �ľ�̬���ԣ�����ģ���Ƿ�ʵ��ʹ��
		// 
		// ͨ��������������Ϊ ����ģ����� �ı��ʽ�����������Ƴټ�鵽 ģ��ʵ����ʱ
		// ����
		static_assert(sizeof(T) == 0, "Unsupported type");
	}
	//���û�����ʹ�� δ����ʽ�ػ������ͣ��� double��int������ Push ʱ���������������ʾ��֧�ֵ�����

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
