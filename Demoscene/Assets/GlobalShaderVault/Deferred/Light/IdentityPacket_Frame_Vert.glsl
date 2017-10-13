#version 330

//layout (location = 0) in vec4 Position; 
layout (location = 0) in vec3 Position;                                             

uniform mat4 gWVP;
uniform mat4 gProjection;
uniform mat4 gWorld;
uniform mat4 gView;


//basically just a quad
void main()
{   //vec4 viewPos = gView * gWorld * Position;
    //gl_Position = gView * Position;
	//mat4 bla = gWorld * gView;
    gl_Position = vec4(Position.xy, 1.0f, 1.0);
	//gl_Position = bla * vec4(Position.xy, -1.0f, 1.0f);
}
