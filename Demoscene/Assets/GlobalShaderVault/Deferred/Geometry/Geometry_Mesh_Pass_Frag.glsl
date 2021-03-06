#version 450 core

in vec2 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;
in vec4 ModelData;
flat in int InstanceID0;


layout(location = 0) out vec4 WorldPosOut;
layout(location = 1) out vec3 DiffuseOut;
layout(location = 2) out vec3 NormalOut;
layout(location = 3) out vec3 TexCoordOut;



uniform sampler2D A_DiffuseMap;

uniform sampler2DArray ArrayDiffuseMaps;

uniform sampler2D MaterialMap;
uniform int MaterialCount;

uniform vec3 mDiffuseCol;
uniform float mSpecularInt;
uniform float mSpecularPow;

const float NEAR = 0.1f;
//const float FAR = 50.0f;
const float FAR = 100.0f;

float LinearDepth(float depth)
{
	float z = depth * 2.0 - 1.0;
	return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));
}


void LookUpMaterial(float ID, out vec4 MatDiffuse, out vec4 MatSpecular)
{

	float PZ_MM_Y = 1 / textureSize(MaterialMap, 0).y;
	float PZ_MM_X = 1 / textureSize(MaterialMap, 0).x;
	float fixID = (ID * PZ_MM_Y) * 0.5;
	//float fixDataSet = (DataSet * PZ_MM_X) * 0.5;
	MatDiffuse = vec4(texture(MaterialMap, vec2((1 * PZ_MM_X) * 0.5, fixID)).xyz, 1.0);
	MatSpecular = vec4(texture(MaterialMap, vec2((2 * PZ_MM_X) * 0.5, fixID)).xyz, 1.0);


}

void LookUpMaterialTexture(float ID,  out vec3 MapInfo)
{

	//float PZ_MM_Y = 1 / textureSize(MaterialMap, 0).y;
	//float PZ_MM_X = 1 / textureSize(MaterialMap, 0).x;
	//float fixID = (ID * PZ_MM_Y) * 0.5;
	//float fixDataSet = (DataSet * PZ_MM_X) * 0.5;
	//MapInfo = 1/texture(MaterialMap, vec2((2 * PZ_MM_X) * 0.5, fixID)).xyz;
	MapInfo = 1 / texture(MaterialMap, ivec2(2, ID)).xyz;
}




void main()
{	//With depth										
	//WorldPosOut.xyz     = WorldPos0;
	//WorldPosOut.w = LinearDepth(gl_FragCoord.z);

	WorldPosOut.xyz = WorldPos0;

	WorldPosOut.w = LinearDepth(gl_FragCoord.z);
	//WorldPosOut.w = gl_FragCoord.z;
	vec4 MatDiffuseColor = vec4(0, 0, 0, 0);
	vec4 MatSpecularColor = vec4(0, 0, 0, 0);

	vec3 MatTextureInfo = vec3(0, 0, 0);

	LookUpMaterial(ModelData.x, MatDiffuseColor, MatSpecularColor);



	LookUpMaterialTexture(ModelData.x,MatTextureInfo);


	//if (textureSize(A_DiffuseMap, 0).x > 0)
	//if (MatTextureInfo.x <= 0)
	//{	
	//	DiffuseOut = vec3(TexCoord0, 0);
	//	DiffuseOut = texture(A_DiffuseMap, TexCoord0).xyz;
	//}
	//else if
	//else
	//{
	//	DiffuseOut = MatDiffuseColor.xyz;
	//}

	//switch(TexCase)
	//{
	//case 0: DiffuseOut = texture(A_DiffuseMap, TexCoord0).xyz;
	//break;

	//default: DiffuseOut = texture(ArrayDiffuseMaps, UVP).xyz;
	//break;

	//}


	//float fixID = (ID * PZ_MM_Y) * 0.5;


	DiffuseOut =  texture(ArrayDiffuseMaps, vec3(vec2(TexCoord0),float(int(MatTextureInfo.y)))).xyz;
	//DiffuseOut = MatDiffuseColor.xyz;
	//DiffuseOut = MatTextureInfo;
	NormalOut = normalize(Normal0);
	//TexCoordOut     = vec3(TexCoord0, 0.0);	
	//cheap hack	
	//TexCoordOut     = vec3(TexCoord0,floor(ModelData.x+0.1));
	TexCoordOut = vec3(TexCoord0, ModelData.x);
	//TexCoordOut     = vec3(TexCoord0,2);	
}
