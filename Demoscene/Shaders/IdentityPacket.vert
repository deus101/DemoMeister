#version 330

//layout (location = 0) in vec4 Position; 
layout (location = 0) in vec3 Position;                                             

uniform mat4 gWVP;
uniform mat4 gProjection;
uniform mat4 gWorld;
uniform mat4 gView;

void main()
{   //vec4 viewPos = gView * gWorld * Position;
    //gl_Position = gView * Position;

    gl_Position = gWVP * vec4(Position.xyz, 1.0);
}
