#version 330

//layout (location = 0) in vec4 Position; 
layout (location = 0) in vec4 Position;                                             

//uniform mat4 gWVP;
//uniform mat4 gProjection;
//uniform mat4 gWorld;
//uniform mat4 gView;

smooth out vec2 uv;
void main()
{   
	//vec4 viewPos = gView * gWorld * vec4(Position, 1.0f);
    //gl_Position = gProjection * viewPos;

	uv = Position.xy;
	gl_Position = vec4(Position.xy, 0.0f, 1.0f);
}
