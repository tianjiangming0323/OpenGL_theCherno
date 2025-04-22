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
//表示该 uniform 变量将引用一个绑定到特定纹理单元的纹理
//sampler2D：在着色器中声明时，实际关联的是一个纹理单元索引
//uniform sampler2D u_Texture2;


uniform sampler2D u_Texture[2];

void main()
{	
   //if(v_Index == 1.0f)
   //{
	  // color = texture(u_Texture[0], v_TexCoord);
	  // //texture 是一个 内置函数，用于从纹理中采样颜色值
	  // //据纹理坐标 v_TexCoord，从绑定到 u_Texture 的纹理中采样颜色值
   //}
   //else
   //{
	  // color = texture(u_Texture[1], v_TexCoord);
   //}
   
   int index = int(v_Index);
   color = texture(u_Texture[index],v_TexCoord);
   
};