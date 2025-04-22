#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_texcoord;
layout(location = 3) in float a_Index;

out vec2 v_TexCoord;
out vec3 v_Color;
out float v_Index;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * a_position;
   v_TexCoord = a_texcoord;
   v_Color = a_color;
   v_Index = a_Index;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color; 

in vec2 v_TexCoord;
in vec3 v_Color;
in float v_Index;

uniform vec4 u_Color;
//uniform sampler2D u_Texture1;  
//��ʾ�� uniform ����������һ���󶨵��ض�����Ԫ������
//sampler2D������ɫ��������ʱ��ʵ�ʹ�������һ������Ԫ����
//uniform sampler2D u_Texture2;


uniform sampler2D u_Texture[2];

void main()
{	
   //if(v_Index == 1.0f)
   //{
	  // color = texture(u_Texture[0], v_TexCoord);
	  // //texture ��һ�� ���ú��������ڴ������в�����ɫֵ
	  // //���������� v_TexCoord���Ӱ󶨵� u_Texture �������в�����ɫֵ
   //}
   //else
   //{
	  // color = texture(u_Texture[1], v_TexCoord);
   //}
   
   int index = int(v_Index);
   color = texture(u_Texture[index],v_TexCoord);
   
};