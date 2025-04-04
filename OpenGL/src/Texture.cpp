#include "Texture.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Height(0), m_Width(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	//在加载图像时对图像进行垂直翻转
	//OpenGL 的纹理坐标原点 (0, 0) 默认在 左下角（bottom-left），而大多数图像格式（如 PNG、JPEG）的像素数据存储顺序是 左上角（top-left）为原点

	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	//从文件路径 path 加载图像数据到内存缓冲区 m_LocalBuffer

	GLCALL(glGenTextures(1, &m_RendererID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));


	//void glTexParameteri(GLenum target, GLenum pname, GLint param);
	//glTexParameteri 中的 i 表示该函数接受的参数类型是 GLint（整数）
	//target: 纹理类型（如 GL_TEXTURE_2D）。
	//pname : 要设置的参数名（如 GL_TEXTURE_MIN_FILTER）。
	//param : 参数值，必须是一个整数（GLint）
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//设置缩小过滤：当纹理被缩小（如远距离渲染时纹理像素小于屏幕像素）时，使用线性插值（GL_LINEAR）平滑采样
	//设置放大过滤：当纹理被放大（如近距离渲染时纹理像素大于屏幕像素）时，使用线性插值（GL_LINEAR）平滑采样。
	/*GL_NEAREST	最近邻采样，速度快但锯齿明显（适合像素风）。
	  GL_LINEAR	线性插值，平滑但略微模糊（适合大多数场景）。
	  GL_NEAREST_MIPMAP_NEAREST	使用最近的 Mipmap 层级 + 最近邻采样（需生成 Mipmap）。
	  GL_LINEAR_MIPMAP_LINEAR	使用 Mipmap 层级间插值 + 线性采样（最高质量）。*/
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	//设置纹理坐标环绕模式
	//控制纹理在 S 轴（水平方向）超出 [0,1] 范围时的行为   （T轴 垂直方向）
	/*GL_REPEAT	重复纹理（默认行为）。
	  GL_CLAMP_TO_EDGE	边缘像素拉伸（避免纹理边缘出现不自然的颜色）。
	  GL_CLAMP_TO_BORDER	超出部分用指定颜色填充（需额外设置边框颜色）。
	  GL_MIRRORED_REPEAT	镜像重复纹理。*/

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	//glTexImage2D 是用于将 CPU 内存中的像素数据上传到 GPU 纹理对象的关键函数
	//void glTexImage2D
	//(
	//	GLenum target,         // 纹理目标（如 GL_TEXTURE_2D）,其他可能值：GL_TEXTURE_CUBE_MAP（立方体贴图）等
	//	GLint level,           // Mipmap 层级（0 表示基本层）  若需 Mipmap：需调用 glGenerateMipmap(GL_TEXTURE_2D) 生成
	//	GLint internalFormat,  // 纹理在 GPU 中的存储格式（如 GL_RGBA8）
	//	GLsizei width,         // 纹理宽度
	//	GLsizei height,        // 纹理高度
	//	GLint border,          // 边框宽度（必须为 0）历史遗留参数
	//	GLenum format,         // 像素数据格式（如 GL_RGBA）  指定像素数据在 CPU 内存中的格式
	//	GLenum type,           // 像素数据类型（如 GL_UNSIGNED_BYTE）GL_UNSIGNED_BYTE：每通道 8 位（0~255）。GL_FLOAT：浮点数据（HDR 或深度纹理）
	//	const void* data       // 像素数据指针
	//);
	
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
		m_LocalBuffer = nullptr;
	}	
	//stbi_image_free 是 stbi_load 的配对清理函数。
	//在数据不再需要时（如上传到 GPU 后）立即释放。
	//释放后置空指针
}

Texture::~Texture()
{
	GLCALL(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCALL(glBindTexture(GL_TEXTURE, 0));
}