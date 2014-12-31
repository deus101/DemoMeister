#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

//in vec3 vertexPosition_modelspace;
//in vec2 vertexUV;
//in vec3 vertexNormal_modelspace;
// Values that stay constant for the whole mesh.

uniform mat4 P;
//uniform mat4 V;
uniform mat4 MV;
uniform mat4 M;

//mat4 MVP; 
vec4 LightPos;
vec4 WorldPos;

out vec4 vertexPos;
out vec2 TexCoord;
out vec3 Normal;
out vec4 Eye;
out vec3 LightDir;
void main()
{	
//ingen lys system enda
	LightPos = vec4(10.0, 10.0, 10.0, 0.0);
//Normal matris == inv av MV
	Normal = normalize(vec3(MV * M * vec4(vertexNormal_modelspace,0.0)));	
	TexCoord = vec2(vertexUV);
	WorldPos = M  * vec4(vertexPosition_modelspace,1.0);
	Eye = -(MV * WorldPos);
	LightDir = vec3(LightPos - WorldPos);
	gl_Position = P * MV  * WorldPos;
}