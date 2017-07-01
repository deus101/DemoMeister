#version 330                                                                        
                                                                                    
layout (location = 0) in vec3 Position;                                             
layout (location = 1) in vec2 TexCoord;                                             
layout (location = 2) in vec3 Normal;    
layout (location = 3) in mat4 Root; 
layout (location = 7) in mat4 Child; 


                                           
//layout (location = 3) in float MatId;
uniform mat4 gWVP;
uniform mat4 gView;
uniform mat4 gWorld;
uniform mat4 gProjection;                
				   
				                        
out vec2 TexCoord0;                                                                 
out vec3 Normal0;                                                                   
out vec3 WorldPos0;
out vec4 ModelData;                                                                  
flat out int InstanceID; 


void main()
{       
	vec4 viewPos = gView * gWorld * vec4(Position, 1.0f);
    //vec4 viewPos = gWorld * gView * gProjection * vec4(Position, 1.0f);

	//gl_Position    = gWVP * vec4(Position, 1.0f);
	gl_Position = gProjection * viewPos;
    //gl_Position =  viewPos;

	TexCoord0      = TexCoord;                  
	//mat3 normalMatrix = transpose(inverse(mat3(gView * gWorld)));
	Normal0        = (gWorld * vec4(Normal, 0.0f)).xyz;   
	//Normal0        = normalMatrix * Normal;

	WorldPos0      = (gWorld * vec4(Position, 1.0f)).xyz;
	InstanceID = gl_InstanceID; 
	ModelData = Child[0];

   //Real name should be viewpos
   //WorldPos0      = viewPos.xyz;
}