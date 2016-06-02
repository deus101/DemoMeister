#version 330

layout (location = 0) in vec4 Position; 

uniform mat4 gWVP;

void main()
{          
    gl_Position = gWVP * vec4(Position.xyz, 1.0);
}
