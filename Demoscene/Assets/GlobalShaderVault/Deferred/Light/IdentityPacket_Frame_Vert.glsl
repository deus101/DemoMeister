#version 330

//layout (location = 0) in vec4 Position; 
layout (location = 0) in vec3 Position;                                             

uniform mat4 gWVP;
uniform mat4 commonProjectionMatrix;
uniform mat4 commonWorldMatrix;
uniform mat4 commonViewMatrix;


//basically just a quad
void main()
{  

    gl_Position = vec4(Position.xy, 1.0f, 1.0);

}
