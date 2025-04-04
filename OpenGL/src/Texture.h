#pragma once
#include "Renderer.h"

class Texture
{
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;   //����ı��ش洢
	int m_Width, m_Height, m_BPP;   //BPP: bits per pixel ��ʾԭʼͼ��ÿ�����ص�ͨ����(4��RGBA ͼ����ͨ������͸���ȣ�)

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

};