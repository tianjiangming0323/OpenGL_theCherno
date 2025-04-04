#pragma once
#include "Renderer.h"

class Texture
{
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;   //纹理的本地存储
	int m_Width, m_Height, m_BPP;   //BPP: bits per pixel 表示原始图像每个像素的通道数(4：RGBA 图（四通道，含透明度）)

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

};