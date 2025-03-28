#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

//S4 OpenGL��һ�������ӿڣ�����ĺ���ʵ����д���Կ������ϵ�
//��openGL����һ��״̬��   ״̬�����Ѿ�������buffer�����ݣ���shader
//����Ⱦʱ����OpenGLѡ�����buffer��shader��Ⱦ�������γ���
//OpenGL����buffer��shader�������������������Σ�����������

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

    glfwTerminate();
    return 0;
}