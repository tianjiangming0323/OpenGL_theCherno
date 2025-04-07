#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"



Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);

    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCALL(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    //�����ļ������Ӵ����ļ��ж�ȡ���ݵ��ڴ�

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    //�ַ�����
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
        //istream& getline(istream& stream, string& line)
        //stream:����������
        //line:�洢��ȡ���ݵ��ַ�������
        //�� C++ ��׼�������ڴ������������ļ����ַ����������ж�ȡ���ݵĺ���
        //�� stream �ж�ȡ�ַ���ֱ���������з� \n ��������
    {
        if (line.find("#shader") != std::string::npos)  //��ʾ�ҵ���
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    //������ɫ������
    const char* src = source.c_str();
    //������ɫ��Դ��
    //�� C++ ��׼�ַ�����std::string��ת��Ϊ C ����ַ���
    //OpenGL�ǻ��� C ������Ƶģ����ǵĺ�������ͨ����Ҫ const char* ����
    GLCALL(glShaderSource(id, 1, &src, nullptr));
    //��Դ��󶨵���ɫ������
    //glShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length)
    //shader:��ɫ������ ID
    //count:ָ��Դ���ַ��������������Դ���ǵ����ַ������������������Ϊ 1����Դ��ֶ�Σ�����д��룩����Ϊ��Ӧ�ķֶ���
    //string:��ɫ��Դ��,������Ҫ const char**��ָ�������ָ�룩��src������Ϊchar*������Ҫ����&src
    //length:�ַ�����������ָ��.���Ϊ nullptr��OpenGL �����ÿ���ַ����� \0 ��β���Զ����㳤��
    GLCALL(glCompileShader(id));
    //������ɫ��

    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    //glGetShaderiv(GLuint shader,GLenum pname,GLint* params);
    //shader:��ɫ������ID
    //pname:Ҫ��ѯ��״̬����
    //�洢��ѯ����ı�����ַ(����ѯ��״̬ΪGL_COMPILE_STATUS)

    if (result == GL_FALSE)
    {
        int length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        //������ɫ����Ϣ��־�е��ַ���
        char* message = (char*)alloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(id, length, &length, message));
        //��������־���ݶ�ȡ��ָ���Ļ�����
        //glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
        //shader:��ɫ������ID
        //maxLength:�����������������Ӧ�� GL_INFO_LOG_LENGTH ��ȡ��ֵһ��
        //length:���ʵ��д�����־���ȣ��ɺ��ԣ�ֱ�Ӵ� nullptr
        //message:�洢������־�Ļ�����ָ��

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
    }

    return id;

}


unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    //������ɫ�����򣬿ճ������
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    //���붥���Ƭ����ɫ��


    GLCALL(glAttachShader(program, vs));// ���Ӷ�����ɫ��
    GLCALL(glAttachShader(program, fs));// ����Ƭ����ɫ��
    GLCALL(glLinkProgram(program));// ���ӳ���
    GLCALL(glValidateProgram(program));// ��֤������Ч�ԣ���ѡ�������ã�

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));
    //ɾ�������ӵ���ɫ������
    return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
    //find(name)�ķ���ֵ��iterator
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    //std::unordered_map<std::string, int> m_UniformLocationCache;
    //���صľ��Ǽ�ֵ�����ֵ
    //operator[]����Ϊ
    //����� name ���ڣ�
    //ֱ�ӷ��ض�Ӧ��ֵ���� location����
    //����� name �����ڣ�
    //�����һ���¼�ֵ�ԣ���Ϊ name��ֵΪ int ���͵�Ĭ��ֵ���� 0����
    //��������²����Ĭ��ֵ 0

    //ÿ�ζ�����glGetUniformLocation���������Ĵ�
    //��ʹ��<unordered_map>ʵ��ӳ��
    GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
    {
        std::cout << "Warning : uniform '" << name << " ' doesn't exist ! " << std::endl;
    }
    
     m_UniformLocationCache[name] = location;
    
    return location;
}

void Shader::Bind() const
{
    GLCALL(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCALL(glUseProgram(0));
}

//Set Uniforms
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUnifromMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}