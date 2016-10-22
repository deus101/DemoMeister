#version 330

//layout (location = 0) in vec4 Position; 
layout (location = 0) in vec4 Position;                                             
layout (location = 1) in vec2 TexCoord;                                             
layout (location = 2) in vec3 Normal;    


uniform mat4 gWVP;
uniform mat4 gProjection;
//uniform mat4 gWorld;
uniform mat4 gView;

smooth out vec2 uv;
//smooth out vec3 v;
//smooth out vec3 EP;
//const vec2 madd=vec2(0.5,0.5);

void main()
{   
	//gl_Position =  Position;
	//vec4 viewPos = gView * gWorld * vec4(Position, 1.0f);
    //gl_Position = gProjection * viewPos;
	//v = vec3( Position* gView);
	//v = vec3( Position * gView);
	//EP = vec3( gView*vec4(0,0,-1,1) );

	//EP = vec3(0,0,-1) * mat3(gView);

	//EP = vec3( vec4(0,0,-1,1)*gView );
	

	//uv.x = TexCoord.x;
	//uv.y = -TexCoord.y +1;
	//uv.y = TexCoord.y;
	uv = Position.xy;
	//uv = Position.xy*madd+madd;

	gl_Position =  vec4(Position.xy, -1.0f, 1.0f);

	//gl_Position = vec4(Position.xy, 0.0f, 1.0f);
	

}
