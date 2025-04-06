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
    //输入文件流：从磁盘文件中读取数据到内存

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    //字符串流
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
        //istream& getline(istream& stream, string& line)
        //stream:输入流对象
        //line:存储读取内容的字符串引用
        //是 C++ 标准库中用于从输入流（如文件、字符串）中逐行读取数据的函数
        //从 stream 中读取字符，直到遇到换行符 \n 或流结束
    {
        if (line.find("#shader") != std::string::npos)  //表示找到了
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
    //创建着色器对象
    const char* src = source.c_str();
    //设置着色器源码
    //将 C++ 标准字符串（std::string）转换为 C 风格字符串
    //OpenGL是基于 C 语言设计的，它们的函数参数通常需要 const char* 类型
    GLCALL(glShaderSource(id, 1, &src, nullptr));
    //将源码绑定到着色器对象
    //glShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length)
    //shader:着色器对象 ID
    //count:指定源码字符串的数量。如果源码是单条字符串（常见情况），设为 1；若源码分多段（如多行代码），设为对应的分段数
    //string:着色器源码,类型需要 const char**（指针数组的指针），src的类型为char*，故需要输入&src
    //length:字符串长度数组指针.如果为 nullptr，OpenGL 会假设每个字符串以 \0 结尾，自动计算长度
    GLCALL(glCompileShader(id));
    //编译着色器

    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    //glGetShaderiv(GLuint shader,GLenum pname,GLint* params);
    //shader:着色器对象ID
    //pname:要查询的状态类型
    //存储查询结果的变量地址(当查询的状态为GL_COMPILE_STATUS)

    if (result == GL_FALSE)
    {
        int length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        //返回着色器信息日志中的字符数
        char* message = (char*)alloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(id, length, &length, message));
        //将错误日志内容读取到指定的缓冲区
        //glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
        //shader:着色器对象ID
        //maxLength:缓冲区的最大容量（应与 GL_INFO_LOG_LENGTH 获取的值一致
        //length:输出实际写入的日志长度（可忽略，直接传 nullptr
        //message:存储错误日志的缓冲区指针

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
    }

    return id;

}


unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    //创建着色器程序，空程序对象
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    //编译顶点和片段着色器


    GLCALL(glAttachShader(program, vs));// 附加顶点着色器
    GLCALL(glAttachShader(program, fs));// 附加片段着色器
    GLCALL(glLinkProgram(program));// 链接程序
    GLCALL(glValidateProgram(program));// 验证程序有效性（可选，调试用）

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));
    //删除已链接的着色器对象
    return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
    //find(name)的返回值是iterator
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    //std::unordered_map<std::string, int> m_UniformLocationCache;
    //返回的就是键值对里的值
    //operator[]的行为
    //如果键 name 存在：
    //直接返回对应的值（即 location）。
    //如果键 name 不存在：
    //会插入一个新键值对，键为 name，值为 int 类型的默认值（即 0）。
    //返回这个新插入的默认值 0

    //每次都调用glGetUniformLocation函数，消耗大
    //故使用<unordered_map>实现映射
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