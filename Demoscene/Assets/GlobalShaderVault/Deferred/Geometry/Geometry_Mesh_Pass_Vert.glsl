#version 330

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 2) in vec3 Normal;
layout(location = 3) in mat4 Root;
layout(location = 7) in mat4 Child;



//layout (location = 3) in float MatId;
uniform mat4 gWVP;
uniform mat4 commonViewMatrix;
uniform mat4 commonWorldMatrix;
uniform mat4 commonProjectionMatrix;


out vec2 TexCoord0;
out vec3 Normal0;
out vec3 WorldPos0;
out vec4 ModelData;
flat out int InstanceID;


void main()
{
	vec4 viewPos = commonViewMatrix * commonWorldMatrix * vec4(Position, 1.0f);
	//vec4 viewPos = commonWorldMatrix * commonViewMatrix * commonProjectionMatrix * vec4(Position, 1.0f);

	//gl_Position    = gWVP * vec4(Position, 1.0f);
	gl_Position = commonProjectionMatrix * viewPos;
	//gl_Position =  viewPos;

	TexCoord0 = TexCoord;
	//mat3 normalMatrix = transpose(inverse(mat3(commonViewMatrix * commonWorldMatrix)));
	Normal0 = (commonWorldMatrix * vec4(Normal, 0.0f)).xyz;
	//Normal0        = normalMatrix * Normal;

	WorldPos0 = (commonWorldMatrix * vec4(Position, 1.0f)).xyz;
	InstanceID = gl_InstanceID;
	ModelData = Child[0];

	//Real name should be viewpos
	//WorldPos0      = viewPos.xyz;
}