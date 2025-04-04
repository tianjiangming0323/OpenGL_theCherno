#include "Texture.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Height(0), m_Width(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	//�ڼ���ͼ��ʱ��ͼ����д�ֱ��ת
	//OpenGL ����������ԭ�� (0, 0) Ĭ���� ���½ǣ�bottom-left�����������ͼ���ʽ���� PNG��JPEG�����������ݴ洢˳���� ���Ͻǣ�top-left��Ϊԭ��

	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	//���ļ�·�� path ����ͼ�����ݵ��ڴ滺���� m_LocalBuffer

	GLCALL(glGenTextures(1, &m_RendererID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));


	//void glTexParameteri(GLenum target, GLenum pname, GLint param);
	//glTexParameteri �е� i ��ʾ�ú������ܵĲ��������� GLint��������
	//target: �������ͣ��� GL_TEXTURE_2D����
	//pname : Ҫ���õĲ��������� GL_TEXTURE_MIN_FILTER����
	//param : ����ֵ��������һ��������GLint��
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//������С���ˣ���������С����Զ������Ⱦʱ��������С����Ļ���أ�ʱ��ʹ�����Բ�ֵ��GL_LINEAR��ƽ������
	//���÷Ŵ���ˣ��������Ŵ����������Ⱦʱ�������ش�����Ļ���أ�ʱ��ʹ�����Բ�ֵ��GL_LINEAR��ƽ��������
	/*GL_NEAREST	����ڲ������ٶȿ쵫������ԣ��ʺ����ط磩��
	  GL_LINEAR	���Բ�ֵ��ƽ������΢ģ�����ʺϴ������������
	  GL_NEAREST_MIPMAP_NEAREST	ʹ������� Mipmap �㼶 + ����ڲ����������� Mipmap����
	  GL_LINEAR_MIPMAP_LINEAR	ʹ�� Mipmap �㼶���ֵ + ���Բ����������������*/
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	//�����������껷��ģʽ
	//���������� S �ᣨˮƽ���򣩳��� [0,1] ��Χʱ����Ϊ   ��T�� ��ֱ����
	/*GL_REPEAT	�ظ�����Ĭ����Ϊ����
	  GL_CLAMP_TO_EDGE	��Ե�������죨���������Ե���ֲ���Ȼ����ɫ����
	  GL_CLAMP_TO_BORDER	����������ָ����ɫ��䣨��������ñ߿���ɫ����
	  GL_MIRRORED_REPEAT	�����ظ�����*/

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	//glTexImage2D �����ڽ� CPU �ڴ��е����������ϴ��� GPU �������Ĺؼ�����
	//void glTexImage2D
	//(
	//	GLenum target,         // ����Ŀ�꣨�� GL_TEXTURE_2D��,��������ֵ��GL_TEXTURE_CUBE_MAP����������ͼ����
	//	GLint level,           // Mipmap �㼶��0 ��ʾ�����㣩  ���� Mipmap������� glGenerateMipmap(GL_TEXTURE_2D) ����
	//	GLint internalFormat,  // ������ GPU �еĴ洢��ʽ���� GL_RGBA8��
	//	GLsizei width,         // ������
	//	GLsizei height,        // ����߶�
	//	GLint border,          // �߿��ȣ�����Ϊ 0����ʷ��������
	//	GLenum format,         // �������ݸ�ʽ���� GL_RGBA��  ָ������������ CPU �ڴ��еĸ�ʽ
	//	GLenum type,           // �����������ͣ��� GL_UNSIGNED_BYTE��GL_UNSIGNED_BYTE��ÿͨ�� 8 λ��0~255����GL_FLOAT���������ݣ�HDR ���������
	//	const void* data       // ��������ָ��
	//);
	
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
		m_LocalBuffer = nullptr;
	}	
	//stbi_image_free �� stbi_load �������������
	//�����ݲ�����Ҫʱ�����ϴ��� GPU �������ͷš�
	//�ͷź��ÿ�ָ��
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