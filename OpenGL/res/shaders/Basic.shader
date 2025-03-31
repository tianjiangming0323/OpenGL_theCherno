#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
   gl_Position = position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color; 

//S11
//uniforms ͳһ����
uniform vec4 u_Color;

void main()
{
   //S11ע��
   //color = vec4(1.0, 0.0 ,0.0, 1.0);
   color = u_Color;
};