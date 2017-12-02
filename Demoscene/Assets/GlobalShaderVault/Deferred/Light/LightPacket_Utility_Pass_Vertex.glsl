#version 330                                                                        

//layout (location = 0) in vec4 Position; 
layout (location = 0) in vec3 Position;                                             

uniform mat4 gWVP;
uniform mat4 commonProjectionMatrix;
uniform mat4 commonWorldMatrix;
uniform mat4 commonViewMatrix;

void main()
{          	
	//vec4 viewPos = commonViewMatrix * commonWorldMatrix * Position;
	vec4 viewPos = commonViewMatrix * commonWorldMatrix * vec4(Position, 1.0f);

	gl_Position = commonProjectionMatrix * viewPos;

}
