#version 330


//in vec2 TexCoord0;                                                                 
in vec3 Normal0;                                                                    
in vec3 WorldPos0;                                                                  
in vec3 Color;  
uniform mat4  gWorld, gWVP;



layout (location = 0) out vec3 WorldPosOut;   

layout (location = 1) out vec3 DiffuseOut;     

layout (location = 2) out vec3 NormalOut;     

layout (location = 3) out vec3 TexCoordOut;    



//uniform sampler2D gColorMap;                


void main()									
{											
	 //WorldPosOut = vec4(1.0f, 0.0f, 0.0f, 1.0f);	
	WorldPosOut     = WorldPos0.xyz;

     DiffuseOut      = Color;

	 NormalOut       = normalize(Normal0);					

	//TexCoordOut     = vec3(TexCoord0, 0.0);				

}