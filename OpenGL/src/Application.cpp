#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

//S4 OpenGL��һ�������ӿڣ�����ĺ���ʵ����д���Կ������ϵ�
//��openGL����һ��״̬��   ״̬�����Ѿ�������buffer�����ݣ���shader
//����Ⱦʱ����OpenGLѡ�����buffer��shader��Ⱦ�������γ���
//OpenGL����buffer��shader�������������������Σ�����������

//S7
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    //������ɫ������
    const char* src = source.c_str();
    //������ɫ��Դ��
    //�� C++ ��׼�ַ�����std::string��ת��Ϊ C ����ַ���
    //OpenGL�ǻ��� C ������Ƶģ����ǵĺ�������ͨ����Ҫ const char* ����
    glShaderSource(id, 1, &src, nullptr);
    //��Դ��󶨵���ɫ������
    //glShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length)
    //shader:��ɫ������ ID
    //count:ָ��Դ���ַ��������������Դ���ǵ����ַ������������������Ϊ 1����Դ��ֶ�Σ�����д��룩����Ϊ��Ӧ�ķֶ���
    //string:��ɫ��Դ��,������Ҫ const char**��ָ�������ָ�룩��src������Ϊchar*������Ҫ����&src
    //length:�ַ�����������ָ��.���Ϊ nullptr��OpenGL �����ÿ���ַ����� \0 ��β���Զ����㳤��
    glCompileShader(id);
    //������ɫ��

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    //glGetShaderiv(GLuint shader,GLenum pname,GLint* params);
    //shader:��ɫ������ID
    //pname:Ҫ��ѯ��״̬����
    //�洢��ѯ����ı�����ַ(����ѯ��״̬ΪGL_COMPILE_STATUS)

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        //������ɫ����Ϣ��־�е��ַ���
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
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

//S7
//������������ɫ�����򣬱��벢�����Ŷ����Ƭ����ɫ�������շ��س������ ID
static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    //������ɫ�����򣬿ճ������
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    //���붥���Ƭ����ɫ��

    glAttachShader(program, vs);// ���Ӷ�����ɫ��
    glAttachShader(program, fs);// ����Ƭ����ɫ��
    glLinkProgram(program);// ���ӳ���
    glValidateProgram(program);// ��֤������Ч�ԣ���ѡ�������ã�

    glDeleteShader(vs);
    glDeleteShader(fs);
    //ɾ�������ӵ���ɫ������
    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //����������
    glfwMakeContextCurrent(window);


    //S3 Ҫ�ɹ�����glewInit��Ҫ��OpenGL project -> Properties -> C/C++ -> Preprocessor -> Preprocessor Definition �ж���GLEW_STATIC
    //ԭ�� glewInit������Ҫ���Ը����ں���������ȥ�Ұɣ���Ҫ����GLEWAPI�� Ȼ����GLEW_STATIC
    if (glewInit() != GLEW_OK)
        std::cout << "Error !" << std::endl;
    //glew�����ĵ��ñ���������openGL������֮��

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[6] =
    {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    //�ú�������������������һ�������ɵ�buffer�������ڶ���������buffer��Ψһ��ʶ�����޷������Σ�
    //OpenGL���������ɵĶ������ᱻ����һ��Ψһ������ʶ��
    //GLuint buffers[3];
    //glGenBuffers(3, buffers); // ���� 3 �������������
    //ʹ�� buffers[0], buffers[1], buffers[2] �ֱ����
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    //S5 ���ö�������
    //�����������ӣ������positions[6]Ϊ��1
    //������һ����������struct��һ��������3��floatΪposition��2��floatΪuv��3��floatΪnormal
    //glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
    //index:������2��positionΪ0��uvΪ1��normalΪ2
    //size: ȡֵֻ��Ϊ1��2��3��4      ��1��positionΪ2����2��positionΪ3��uvΪ2��normalΪ3    ������������������ÿ�������м���ֵ
    //type: �������ͣ�GL_FLOAT
    //normalized: �Ƿ���Ҫ��һ��   GL_TRUE/GL_FALSE
    //stride:���㵽����֮���ƫ��������1�У��Ӷ���1������2��Ҫ�������float����2�дӶ���1������2��Ҫ���3+2+3��float
    //pointer:ÿһ�������У�ĳ���Ե����λ��  ��1�У�positionΪ0����2�У�positionΪ0��uvΪ12��normalΪ20
    glEnableVertexAttribArray(0);
    //����index���������Ե�λ������������ 0 ��ʾ����λ�ã�1 ��ʾ���ߵȣ�

    //S7
    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";


    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color; \n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0 ,0.0, 1.0);\n"
        "}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);
  
    //ѭ��һֱ���� ֱ���û��ر�window
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /*glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.0f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();*/
        //S2 glBegin��glEnd��Legacy OpenGL
        //Modern OpenGL�Ĳ���
        //�������㻺����,������Щ�������ݣ���buffer����OpenGL��VRAM
        //����DrawCall OpenGL���ݻ����е����ݽ�����Ⱦ

        glDrawArrays(GL_TRIANGLES, 0, 3);
        //S4 �����и����⣬OpenGL����ô֪������Ⱦ�ĸ�buffer���������
        //��bind�����ĸ�������Ⱦ�ĸ�����ΪOpenGL����������ص�
        //��õ�glѧϰ�ĵ�docs.gl

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //S7
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}