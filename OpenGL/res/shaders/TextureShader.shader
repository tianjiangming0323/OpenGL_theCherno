#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * position;
   v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color; 
//定义片段着色器的输出颜色写入到帧缓冲区（Framebuffer）的索引

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;  //表示该 uniform 变量将引用一个绑定到特定纹理单元的纹理
//sampler2D：在着色器中声明时，实际关联的是一个纹理单元索引

void main()
{
   vec4 texColor = texture(u_Texture, v_TexCoord);
   //texture 是一个 内置函数，用于从纹理中采样颜色值
   //据纹理坐标 v_TexCoord，从绑定到 u_Texture 的纹理中采样颜色值
   color = texColor;
};