#shader vertex
#version 330 core
      
layout(location = 0) in vec4 position; 
layout(location = 1) in vec3 color; 
        
out vec3 vertexColor;
void main()
{ 
    gl_Position = position; 
    vertexColor = color; 
};


#shader fragment 
#version 330 core
      
in vec3 vertexColor; 
out vec4 finalColor; 
       
void main()
{ 
    finalColor = vec4(vertexColor, 1.0); 
};