#version 330


//in vec2 TexCoord0;                                                                 
in vec3 Normal0;                                                                    
in vec3 WorldPos0;                                                                  
in vec3 Color;  
uniform mat4  commonWorldMatrix, gWVP;



layout (location = 0) out vec4 WorldPosOut;   

layout (location = 1) out vec3 DiffuseOut;     

layout (location = 2) out vec3 NormalOut;     

//layout (location = 3) out vec3 TexCoordOut;    

const float NEAR = 1.0f;
const float FAR = 200.0f;
float LinearDepth(float depth)
{
    float z = depth * 2.0 - 1.0; 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));	
}

//uniform sampler2D gbAbedoMap;                


void main()									
{											
	 //WorldPosOut = vec4(1.0f, 0.0f, 0.0f, 1.0f);	
	WorldPosOut.xyz    = WorldPos0.xyz;
	WorldPosOut.w = LinearDepth(gl_FragCoord.z);
     DiffuseOut      = Color;

	 NormalOut       = normalize(Normal0);					

	//TexCoordOut     = vec3(TexCoord0, 0.0);				

}