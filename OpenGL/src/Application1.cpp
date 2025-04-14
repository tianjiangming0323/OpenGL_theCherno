//#include "GL/glew.h"
//#include "GLFW/glfw3.h"
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//
//#include "Renderer.h"
//#include "IndexBuffer.h"
//#include "VertexBuffer.h"
//#include "VertexArray.h"
//#include "VertexBufferLayout.h"
//#include "Shader.h"
//#include "Texture.h"
//
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw_gl3.h"
//
//
////S4 OpenGL��һ�������ӿڣ�����ĺ���ʵ����д���Կ������ϵ�
////��openGL����һ��״̬��   ״̬�����Ѿ�������buffer�����ݣ���shader
////����Ⱦʱ����OpenGLѡ�����buffer��shader��Ⱦ�������γ���
////OpenGL����buffer��shader�������������������Σ�����������
////��õ�glѧϰ�ĵ�docs.gl
//
////S8 ���
////S15 ע��
////struct ShaderProgramSource
////{
////    std::string VertexSource;
////    std::string FragmentSource;
////};
//
////S8 ���
////S15 ע��
////static ShaderProgramSource ParseShader(const std::string& filepath)
////{
////    std::ifstream stream(filepath);
////    //�����ļ������Ӵ����ļ��ж�ȡ���ݵ��ڴ�
////
////    enum class ShaderType
////    {
////        NONE = -1, VERTEX = 0, FRAGMENT = 1
////    };
////
////    std::string line;
////    std::stringstream ss[2];
////    //�ַ�����
////    ShaderType type = ShaderType::NONE;
////    while (getline(stream, line))  
////    //istream& getline(istream& stream, string& line)
////    //stream:����������
////    //line:�洢��ȡ���ݵ��ַ�������
////    //�� C++ ��׼�������ڴ������������ļ����ַ����������ж�ȡ���ݵĺ���
////    //�� stream �ж�ȡ�ַ���ֱ���������з� \n ��������
////    {
////        if (line.find("#shader") != std::string::npos)  //��ʾ�ҵ���
////        {
////            if (line.find("vertex") != std::string::npos)
////                type = ShaderType::VERTEX;
////            else if (line.find("fragment") != std::string::npos)
////                type = ShaderType::FRAGMENT;
////        }
////        else
////        {
////            ss[(int)type] << line << '\n';
////        }
////    }
////
////    return { ss[0].str(),ss[1].str() };
////}
//
////S7 ���
////S15 ע��
////static unsigned int CompileShader(unsigned int type, const std::string& source)
////{
////    unsigned int id = glCreateShader(type);
////    //������ɫ������
////    const char* src = source.c_str();
////    //������ɫ��Դ��
////    //�� C++ ��׼�ַ�����std::string��ת��Ϊ C ����ַ���
////    //OpenGL�ǻ��� C ������Ƶģ����ǵĺ�������ͨ����Ҫ const char* ����
////    GLCALL(glShaderSource(id, 1, &src, nullptr));
////    //��Դ��󶨵���ɫ������
////    //glShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length)
////    //shader:��ɫ������ ID
////    //count:ָ��Դ���ַ��������������Դ���ǵ����ַ������������������Ϊ 1����Դ��ֶ�Σ�����д��룩����Ϊ��Ӧ�ķֶ���
////    //string:��ɫ��Դ��,������Ҫ const char**��ָ�������ָ�룩��src������Ϊchar*������Ҫ����&src
////    //length:�ַ�����������ָ��.���Ϊ nullptr��OpenGL �����ÿ���ַ����� \0 ��β���Զ����㳤��
////    GLCALL(glCompileShader(id));
////    //������ɫ��
////
////    int result;
////    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
////    //glGetShaderiv(GLuint shader,GLenum pname,GLint* params);
////    //shader:��ɫ������ID
////    //pname:Ҫ��ѯ��״̬����
////    //�洢��ѯ����ı�����ַ(����ѯ��״̬ΪGL_COMPILE_STATUS)
////
////    if (result == GL_FALSE)
////    {
////        int length;
////        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
////        //������ɫ����Ϣ��־�е��ַ���
////        char* message = (char*)alloca(length * sizeof(char));
////        GLCALL(glGetShaderInfoLog(id, length, &length, message));
////        //��������־���ݶ�ȡ��ָ���Ļ�����
////        //glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
////        //shader:��ɫ������ID
////        //maxLength:�����������������Ӧ�� GL_INFO_LOG_LENGTH ��ȡ��ֵһ��
////        //length:���ʵ��д�����־���ȣ��ɺ��ԣ�ֱ�Ӵ� nullptr
////        //message:�洢������־�Ļ�����ָ��
////
////        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!"<< std::endl;
////        std::cout << message << std::endl;
////    }
////
////    return id;
////}
//
////S7
////������������ɫ�����򣬱��벢�����Ŷ����Ƭ����ɫ�������շ��س������ ID
////&����������б�ʾ���ã�����������ʾȡַ
////S15 ע��
////static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
////{
////    unsigned int program = glCreateProgram();
////    //������ɫ�����򣬿ճ������
////    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
////    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
////    //���붥���Ƭ����ɫ��
////
////
////    GLCALL(glAttachShader(program, vs));// ���Ӷ�����ɫ��
////    GLCALL(glAttachShader(program, fs));// ����Ƭ����ɫ��
////    GLCALL(glLinkProgram(program));// ���ӳ���
////    GLCALL(glValidateProgram(program));// ��֤������Ч�ԣ���ѡ�������ã�
////
////    GLCALL(glDeleteShader(vs));
////    GLCALL(glDeleteShader(fs));
////    //ɾ�������ӵ���ɫ������
////    return program;
////}
//
//int main(void)
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    //S12���
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);   //Ҫ�� GLFW ���� OpenGL 3.3 ��������
//    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);   //����ģʽ
//    //�������� GLFW ���ڵ� OpenGL �����İ汾��ģʽ
//    // NVIDIA��Ĭ�Ϸ��ظ��߰汾�� OpenGL���� 4.6��������Ȼ֧�ּ���ģʽ
//    //���磬���� 3.3 ʱ���������ܷ��� 4.6����������ʹ�� 3.3 �Ĺ��ܺͼ�������
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);   //����ģʽ
//    //����ģʽ�ͺ���ģʽ�������Ƿ�֧�־ɰ� OpenGL �������ù���
//    /* ����ģʽ��Core Profile��
//       Ŀ�꣺�ṩ���ִ��� OpenGL ʵ�֣�ǿ��ʹ�ÿɱ�̹��ߡ�
//       ���ԣ�
//       �Ƴ����������ù��ܣ�����̶����ߣ�glBegin / glEnd��������ģʽ��glVertex3f�����ɰ���������glMatrixMode�������գ�glLightfv����
//       ǿ��ʹ���ִ����ԣ�����ʹ����ɫ����Shader�������㻺�����VBO���������������VAO����
//       �ϸ�汾���ƣ������İ汾�ϸ���ѭ glfwWindowHint ���õİ汾���� 3.3��4.6��*/
//
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    //����������
//    glfwMakeContextCurrent(window);
//
//    //S11���
//    glfwSwapInterval(1);
//    //���ô�ֱͬ����֡������Ϊ��ʾ��ˢ���ʣ�
//
//
//    //S3 Ҫ�ɹ�����glewInit��Ҫ��OpenGL project -> Properties -> C/C++ -> Preprocessor -> Preprocessor Definition �ж���GLEW_STATIC
//    //ԭ�� glewInit������Ҫ���Ը����ں���������ȥ�Ұɣ���Ҫ����GLEWAPI�� Ȼ����GLEW_STATIC
//    if (glewInit() != GLEW_OK)
//        std::cout << "Error !"<< std::endl;
//    //glew�����ĵ��ñ���������openGL������֮��
//
//    std::cout << glGetString(GL_VERSION) << std::endl;
//
//    {
//        //S17 �޸��������ݣ������uv����
//        float positions[16] =
//        {
//            -0.5f, -0.5f, 0.0f, 0.0f,//index = 0
//             0.5f, -0.5f, 1.0f, 0.0f,//index = 1
//             0.5f,  0.5f, 1.0f, 1.0f,//index = 2
//
//             // 0.5f,  0.5f,
//             -0.5f, 0.5f, 0.0f, 1.0f,  //index = 3
//             //-0.5f, -0.5f
//
//             //S9 �����ж����������ڴ�ռ��̫��
//             //ÿ�����������ŵ������Σ���Ҫ�ظ���������
//             //���ҵ��Ժ󶥵����Ը���ʱ�����绹�з��ߡ�uv�����ԣ����ĸ���
//             //���������������� index buffer
//        };
//
//        //S9 index buffer
//        //��Ҫ unsigned ��
//        unsigned int indices[] =
//        {
//            0, 1, 2,
//            2, 3, 0
//        };
//
//        //S17���
//        GLCALL(glEnable(GL_BLEND));
//        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//        //FLL P169
//        //src:ƬԪ��������ɫ
//        //dst:�Ѿ���������ɫ�����е���ɫ
//        //����͸�����壬���ڹر������д�룬������Ⱦ˳�����Ҫ
//
//
//        //S12  ��� ��������
//        //S14 ע��
//        /*unsigned int vao;
//        GLCALL(glGenVertexArrays(1, &vao));
//        GLCALL(glBindVertexArray(vao));*/
//
//
//        //S14 ���   ����������
//        VertexArray va;
//        VertexBufferLayout layout;
//        layout.Push<float>(2);
//        //��ô���ĺô��ǿ���easily���������layout����
//        //�������Ҫ���3ά����
//        //layout.Push<float>(3);
//        // 
//        //S17 ���UV����
//        layout.Push<float>(2);
//        
//
//
//        //S13 �����㻺����ע�͵�����VertexBuffer.h��ʵ��
//        //unsigned int buffer;
//        //GLCALL(glGenBuffers(1, &buffer));
//        ////�ú�������������������һ�������ɵ�buffer�������ڶ���������buffer��Ψһ��ʶ�����޷������Σ�
//        ////OpenGL���������ɵĶ������ᱻ����һ��Ψһ������ʶ��
//        ////GLuint buffers[3];
//        ////glGenBuffers(3, buffers); // ���� 3 �������������
//        ////ʹ�� buffers[0], buffers[1], buffers[2] �ֱ����
//        //GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
//        //GLCALL(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW));
//        //S4
//        //�����򻺳�������������ݵĺ��ĺ���  �����ڰ󶨻����������
//        //����һ�����ݴ�CPU�ڴ浽GPU�Դ�
//        //void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
//        //target: ���������ͣ��� GL_ARRAY_BUFFER:�����������ݣ��綥�����꣩��GL_ELEMENT_ARRAY_BUFFER���������ݣ�
//        //size: ���ݵ����ֽڴ�С
//        //data: ָ�����ݵ�ָ�루�綥�����飩
//        //usage: ���ݵ�ʹ�÷�ʽ���� GL_STATIC_DRAW:���ݼ������䣨�羲̬ģ�Ͷ��㣩��GL_DYNAMIC_DRAW:����Ƶ���޸ģ��綯̬ UI Ԫ�أ���GL_STREAM_DRAW:����ÿ֡�޸ģ�������ϵͳ��)
//
//        //S9 �Լ����ڰ󶨵��ɻ�
//        //��Ϊbuffer�а����ݵ�ʱ������ôȷ���ǰ󶨸���buffer���أ��᲻��󶨵�����ͬ����GL_ARRAY_BUFFER�Ļ���������
//        //glBindBuffer(GL_ARRAY_BUFFER, buffer) ������
//        //��һ���� buffer ����Ϊ��ǰ��Ծ�� GL_ARRAY_BUFFER Ŀ�ꡣ����������� GL_ARRAY_BUFFER �Ĳ������� glBufferData���������ڵ�ǰ�󶨵Ļ���������buffer��
//        //��glBufferData������Զ��Ե�ǰ�󶨵�Ŀ�껺�����������һ�� glBindBuffer ���õĽ�������в�����
//        //�� OpenGL ����Ⱦ�����У�ÿ���󶨵㣨Target��ͬһʱ��ֻ�ܰ�һ�����������󡣰��»�����ʱ���ɻ��������Զ����
//        //����ͬ�󶨵�Ļ���������ͬʱ��
//
//
//        //S13���
//        //S17�޸�   4 * 2  �ĳ�   4 * 4
//        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
//
//        //S9���
//        //S13ע�ͣ���IndexBuffer.h��ʵ��
//        //unsigned int ibo;   //index buffer object
//        //GLCALL(glGenBuffers(1, &ibo));
//        //GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
//        //GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));
//
//        //S13���
//        IndexBuffer ib(indices, 6);
//
//        //S18���
//        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
//        //����ͶӰ���� 3D �ռ��е�����ͶӰ�� 2D ƽ���ϣ�������͸��Ч���������С�������仯��
//        //glm::ortho �Ĳ�������������ͶӰ�� �Ӿ��壨View Frustum����Χ��glm::ortho(left, right, bottom, top, near, far)
//        //���������ĳ�glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f)
//        //��Ⱦ���Ľ����С
//        //��Ϊ����ͶӰ����Ὣ�Ӿ��壨View Frustum���ڵ���������ӳ�䵽��һ���豸���꣨NDC���� [-1, 1] ��Χ
//        //��position����Ķ�������ֱ�ĳ�+- 2 ��+-1.5������������и�������
//        //proj���(��OpenGL��Ϊ��������),������ʾ�Ľ����������
//        //(  2/(r-l),         0,         0,   -(r+l)/(r-l),
//        //         0,   2/(t-b),         0,   -(t+b)/(t-b),
//        //         0,         0,   2/(n-f),   -(n+f)/(n-f),
//        //         0,         0,         0,             1)
//       
//        //S21���
//        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
//        //����ʼ��λ����glm::mat4(1.0f)���� x �Ḻ����ƽ�� 1 ��λ
//        //1,0,0,-1,
//        //0,1,0,0,
//        //0,0,1,0,
//        //0,0,0,1
//        //S22ע��
//        //glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(2, 0.5, 0));
//        //glm::mat4 mvp =  proj * view * model;
//
//        //S14
//        va.AddBuffer(vb,layout);
//
//        //S14 ע��
//        //GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
//        //S5 ���ö������� ��������GL_ARRAY_BUFFER
//        //�����������ӣ������positions[6]Ϊ��1
//        //������һ����������struct��һ��������3��floatΪposition��2��floatΪuv��3��floatΪnormal
//        //glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
//        //index:������2��positionΪ0��uvΪ1��normalΪ2
//        //size: ȡֵֻ��Ϊ1��2��3��4      ��1��positionΪ2����2��positionΪ3��uvΪ2��normalΪ3    ������������������ÿ�������м���ֵ
//        //type: �������ͣ�GL_FLOAT
//        //normalized: �Ƿ���Ҫ��һ��   GL_TRUE/GL_FALSE
//        //stride:���㵽����֮���ƫ��������1�У��Ӷ���1������2��Ҫ�������float����2�дӶ���1������2��Ҫ���3+2+3��float
//        //pointer:ÿһ�������У�ĳ���Ե����λ��  ��1�У�positionΪ0����2�У�positionΪ0��uvΪ12��normalΪ20
//        //ͬʱ�����������vao��buffer������
//        //GLCALL(glEnableVertexAttribArray(0));
//        //����index���������Ե�λ������������ 0 ��ʾ����λ�ã�1 ��ʾ���ߵȣ�
//
//        //S7���
//        //S8ע�͵�
//       /* std::string vertexShader =
//            "#version 330 core\n"
//            "\n"
//            "layout(location = 0) in vec4 position; \n"
//            "\n"
//            "void main()\n"
//            "{ \n"
//            "   gl_Position = position; \n"
//            "}\n";
//
//
//        std::string fragmentShader =
//            "#version 330 core\n"
//            "\n"
//            "layout(location = 0) out vec4 color; \n"
//            "\n"
//            "void main()\n"
//            "{ \n"
//            "  color = vec4(1.0, 0.0 ,0.0, 1.0); \n"
//            "}\n"; */
//
//
//        //S8���
//        //S15 ע��
//        /*ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
//        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
//        GLCALL(glUseProgram(shader));*/
//
//        //S15 ���
//        Shader shader("res/shaders/TextureShader.shader");
//        shader.Bind();
//
//
//        //S18���
//        //S21�޸�  proj   Ϊmvp
//        //S22ע��
//        //shader.SetUnifromMat4f("u_MVP", mvp);
//
//
//        //S11 ���
//        //S15 ע��
//       /* GLCALL(int location = glGetUniformLocation(shader, "u_Color"));
//        ASSERT(location != -1);*/
//        //GLCALL(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));   
//        //glUseProgram�ж�����u_Color���Դ��У�
//        //����C++�����ж�����uniform
//
//       
//
//        //S12 ���  
//        //S15 �޸�
//       /* GLCALL(glUseProgram(0));
//        GLCALL(glBindVertexArray(0));
//        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
//        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));*/
//
//        //S17���
//        Texture texture("res/textures/pic.png");
//        texture.Bind();
//        shader.SetUniform1i("u_Texture", 0);   //���ò��ʰ󶨵����0
//        //�� u_Texture ��ֵ��Ϊ 0����ʾ��ɫ��Ӧ�� GL_TEXTURE0 ��Ԫ��ȡ����
//
//        shader.Unbind();
//        va.Unbind();
//        ib.Unbind();
//        vb.Unbind();
//
//
//        //S16���
//        Renderer renderer;
//
//        //S22���
//        ImGui::CreateContext();
//        ImGui_ImplGlfwGL3_Init(window, true);
//        ImGui::StyleColorsDark();
//        
//
//        //S22���
//        glm::vec3 translationA(2.0f, 0.5f, 0.0f);
//        glm::vec3 translationB(0.0f, 0.5f, 0.0f);
//
//        float r = 0.0f;
//        float increment = 0.05f;
//
//        //ѭ��һֱ���� ֱ���û��ر�window
//        while (!glfwWindowShouldClose(window))
//        {
//
//            /* Render here */
//            //GLCALL(glClear(GL_COLOR_BUFFER_BIT));    S16ע��
//            renderer.Clear();
//
//
//            //S22���
//            ImGui_ImplGlfwGL3_NewFrame();
//
//            //S12���  S15 �޸�
//            shader.Bind();//GLCALL(glUseProgram(shader));        
//            //GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));  S13ע��
//            //ib.Bind();                                           //S16ע�ͣ���ӵ�Renderer.h��ȥ
//            //GLCALL(glBindVertexArray(vao));                      S14ע��
//            //va.Bind();                                           //S14���      S16ע�ͣ���ӵ�Renderer.h��ȥ
//            //����Ҫ�ٰ�vb�ˣ����ݹ����Ѿ���va��ʵ��
//
//            /*glBegin(GL_TRIANGLES);
//            glVertex2f(-0.5f, -0.5f);
//            glVertex2f( 0.0f,  0.5f);
//            glVertex2f( 0.5f, -0.5f);
//            glEnd();*/
//            //S2 glBegin��glEnd��Legacy OpenGL
//            //Modern OpenGL�Ĳ���
//            //�������㻺����,������Щ�������ݣ���buffer����OpenGL��VRAM
//            //����DrawCall OpenGL���ݻ����е����ݽ�����Ⱦ
//
//            //glDrawArrays(GL_TRIANGLES, 0, 6);
//            //S4
//            //void glDrawArrays(GLenum mode, GLint first, GLsizei count );
//            //mode:ָ�����Ƶ�ͼԪ����,GL_TRIANGLES��ÿ 3 ������ ����һ������������
//            //first:�Ӷ�������������ĸ�λ�ÿ�ʼ��ȡ����
//            //count:�ܹ���Ҫ���ƶ��ٸ�����(GL_TRIANGLES��������3�ı�����  count/3 �����Ƶ�����������
//            //�����и����⣬OpenGL����ô֪������Ⱦ�ĸ�buffer���������
//            //��bind�����ĸ�������Ⱦ�ĸ�����ΪOpenGL����������ص�
//            //S9 ���index buffer��ע��
//
//            //S10���,����˺��ע��
//            //GLClearError();
//
//            
//
//
//            //S11���  S15�޸�
//            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);//GLCALL(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
//            //uniforms are set per draw while attributes are set per vertex
//            //����˵Ҫ�����������ε��������������ò�ͬ����ɫ
//            //������������������ͬһ��draw call����Ⱦ��
//            //��ʹ��uniforms����ʵ�֣�ֻ����attributes
//
//
//            {
//                //S22���   
//                //S23�޸�
//                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
//                glm::mat4 mvp = proj * view * model;
//                shader.SetUnifromMat4f("u_MVP", mvp);
//
//                renderer.Draw(va, ib, shader);
//            }
//
//            {
//                //S23���   
//                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
//                glm::mat4 mvp = proj * view * model;
//                shader.SetUnifromMat4f("u_MVP", mvp);
//
//                renderer.Draw(va, ib, shader);
//            }
//
//
//
//
//            //S16���   
//            //S23ע�ͣ��Ƶ�{}������Ⱦ
//            //renderer.Draw(va, ib, shader);
//            
//
//            //GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));      //S16ע�ͣ���ӵ�Renderer.h��ȥ
//            //S9
//            //OpenGL �����ڸ���������������EBO/IBO�����Ƽ�����ĺ��ĺ���
//            //void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices // �������ݵ���ʼƫ�ƣ��ֽڣ�);
//            //mode: ͼԪ���ͣ��� GL_TRIANGLES��GL_LINES��
//            //count:Ҫ���Ƶ���������
//            //type: �������������ͣ��� GL_UNSIGNED_INT��
//            //indices: �������ݵ���ʼƫ�ƣ��ֽڣ�
//
//            //S9
//            //index buffer��ô֪������ָ���λ����
//            //��������ָ�򶥵����������
//            //1.�󶨶��㻺������VBO����glBindBuffer(GL_ARRAY_BUFFER, vbo)
//            //2.��������������IBO����glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo)��IBO�洢���Ƕ��㻺����������ֵ
//            //3.���ö�������ָ�룺ͨ�� glVertexAttribPointer �������ݸ�ʽ
//            //4.���Ƶ��ã�glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0)
//            //���ݽ���ͨ����������ָ��
//
//            //S10���
//            //GLCheckError();
//            //���ص����Σ�ת����16���ƺ󣬿�����glew.h��Ѱ�ұ�������
//
//            //S10��ӣ�������GLCheckError������˺��ע��
//            //ASSERT(GLLogCall());
//
//            //S11���
//            if (r > 1.0f)
//            {
//                increment = -0.05f;
//            }
//            else if (r < 0.0f)
//            {
//                increment = 0.05f;
//            }
//            r += increment;
//
//            //S22���
//            {
//               
//                ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 1.0f); //0.0f �� 1.0f �ֱ��ǻ���������Сֵ�����ֵ
//                ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 1.0f); //S23 ���B ��UI������
//                //�Լ��ʼ�и����ʣ�translation��3ά�ģ���ôtranslation.x��Ӧ��ֻ��һ��floatֵ
//                //��ImGui����ô�ܿ���x��y��z����������ƶ��ģ���
//                //ImGui::SliderFloat3 �ĵڶ������������� float[3]����һ�� ���� 3 ������ float ������ ��ָ��
//                //��glm::vec3 ��һ������ 3 �� float �����Ľṹ�壬���ڴ沼��Ĭ���� ������
//                //��&translation.x ���Ա���Ϊһ�� ָ������ 3 �� float ��ָ�루�� float* �� float[3]��
//                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//            }
//
//            //S22���
//            ImGui::Render();
//            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
//
//
//            /* Swap front and back buffers */
//            glfwSwapBuffers(window);
//
//            /* Poll for and process events */
//            glfwPollEvents();
//        }
//        //S15 ע��  �����������л��Զ�����shader.Unbind()
//        //GLCALL(glDeleteProgram(shader));
//    }
//    //S13���
//    //�����һ���µ�������
//    //���û������������ڹر���Ⱦwindow����������û�н���
//    //��Ϊ�����ȵ���glfwTerminate()�ƻ��˺��������ģ�Ȼ���ٵ��������������������ʱ��������û���������޷�ʵ��
//    //�ʽ���취�Ǽ�һ��������
//    //���е��������β���ͻ��������������Ȼ���ٵ���glfwTerminate()
//    
//    //S22���
//    ImGui_ImplGlfwGL3_Shutdown();
//    ImGui::DestroyContext();
//
//    glfwTerminate();
//    return 0;
//}