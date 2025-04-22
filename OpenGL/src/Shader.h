#pragma once
#include <iostream>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;

	//caching for uniforms
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;


public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set Uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);   //4��float
	void SetUniform1i(const std::string& name, int value);    //1��int
	void SetUnifromMat4f(const std::string& name, const glm::mat4& matrix);    //4*4����
	void SetUniformArrayInt(const std::string& name, const int size, const int* Array);     //����

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name) const;
	//const��ʾ�ú����޷��޸����Ա������ֵ
	//���ǳ�Ա����ǰ���mutable���δ�
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	
};