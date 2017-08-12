#version 330
//Directional Light
struct BaseLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct DirectionalLight
{
    BaseLight Base;
    vec3 Direction;
};

struct Attenuation
{
    float Constant;
    float Linear;
    float Exp;
};

struct PointLight
{
    BaseLight Base;
    vec3 Position;
    Attenuation Atten;
};

struct SpotLight
{
    PointLight Base;
    vec3 Direction;
    float Cutoff;
};

//here I will add glsl code automatically


uniform sampler2D MaterialMap;

//gColorMap should be diffuseMap
//uniform sampler2D gColorMap;

uniform sampler2D gPositionMap;
uniform sampler2D gAbedoMap;
uniform sampler2D gNormalMap;
uniform sampler2D gUvMap;
uniform sampler2D gAoPass;

//uniform sampler2D MaterialMap;


uniform mat4 gProjection;
uniform mat4 gView;	
uniform mat4 gWorld;

uniform DirectionalLight gDirectionalLight;
uniform PointLight gPointLight;
uniform SpotLight gSpotLight;
uniform vec3 gEyeWorldPos;
uniform float gMatSpecularIntensity = 0.9f;
uniform float gSpecularPower = 8.0f;
uniform int gLightType;
uniform vec2 gScreenSize;



//if we run a effect lookup first we can anticipate what paramaters we require
//void LookUpMaterial(int ID, out vec3 MatDiffuse,out vec3 MatSpecular,out float MatEmmi)
void LookUpMaterial(float ID, out vec4 MatDiffuse,out vec4 MatSpecular)
{

	float PZ_MM_Y = 1/textureSize( MaterialMap, 0).y;
	float fixID = (ID * PZ_MM_Y) * 0.5;
	MatDiffuse = vec4( texture(MaterialMap, vec2(0, fixID)).xyz,1.0);
	MatSpecular = vec4(texture(MaterialMap, vec2(1, fixID)).xyz,1.0);
	//MatDiffuse = vec4( texture(MaterialMap, vec2(0, fixID/10)).xyz,1.0);
	//MatSpecular = vec4(texture(MaterialMap, vec2(1, fixID/10)).xyz,1.0);
	//MatDiffuse = vec4(texture(MaterialMap, vec2(ID, 0)).xyz,1.0);
	//MatSpecular = vec4(texture(MaterialMap, vec2(ID, 1)).xyz,1.0);

}
	
vec4 CalcLightInternal(BaseLight Light,
					   vec3 LightDirection,
					   float ID,
					   vec3 WorldPos,
					   float Depth,
					   vec3 Normal,
					   float AO)
{
	//vec4 OcculsionFactor = vec4(vec3(AO),0.0);
    //vec4 AmbientColor =  vec4(Light.Color * Light.AmbientIntensity, 1.0) ;
	//vec3 OcculsionFactor = vec3(AO);
    //vec3 AmbientColor =  vec3(Light.Color * (Light.AmbientIntensity * AO)) ;


    vec4 DiffuseColor  = vec4(0, 0, 0, 0);	
    vec4 SpecularColor = vec4(0, 0, 0, 0);
	vec3 DiffuseColor1  = vec3(0, 0,  0);	
    vec3 SpecularColor1 = vec3(0, 0,  0);

	LookUpMaterial(ID,DiffuseColor,SpecularColor);
	//Light.AmbientIntensity
	vec3 AmbientColor =  vec3(Light.AmbientIntensity * DiffuseColor.xyz *  AO) ;
	//AmbientColor *= OcculsionFactor;
    //float DiffuseFactor = max(dot(Normal, LightDirection),0.0);
	float DiffuseFactor = dot(Normal, LightDirection);
	

    if (DiffuseFactor > 0.0) {
        DiffuseColor1  = Light.DiffuseIntensity * (DiffuseColor.xyz * Light.Color) ;
		//* Light.DiffuseIntensity * 
        //vec3 VertexToEye = normalize(gEyeWorldPos - WorldPos);
		//vec3 VertexToEye = normalize(WorldPos - gEyeWorldPos);
		//vec3 VertexToEye = normalize(-WorldPos);
		//vec3 FragUV = vec3(vec2(gl_FragCoord.xy/gScreenSize ), 0.0);
		vec2 madd=vec2(0.5,0.5);


		vec3 VertexToEye = normalize((-WorldPos)+((vec3(vec2(gl_FragCoord.xy/gScreenSize )*madd+madd, 0.0)+gEyeWorldPos)));
		vec3 halfwayDir = normalize(LightDirection + VertexToEye);
		
		
		//mat3 viewNormalMat = transpose(mat3(gView));
		//vec3 ViewNorm = viewNormalMat * Normal;
		//vec3 LightReflect = normalize(reflect( Normal,LightDirection));
		//vec3 LightReflect = normalize(reflect(LightDirection, Normal));
        //float SpecularFactor = dot(VertexToEye,LightReflect );
        //float SpecularFactor = dot(LightReflect,VertexToEye );
		float SpecularFactor = dot( Normal,halfwayDir);
		
		SpecularFactor = pow(SpecularFactor, gSpecularPower);
        if (SpecularFactor > 0.0) {
            //SpecularColor1 = Light.Color * gMatSpecularIntensity;
			SpecularColor1 = Light.Color * gMatSpecularIntensity;
			SpecularColor1 *=  SpecularColor.xyz  *SpecularFactor;
			//gMatSpecularIntensity * SpecularColor
        }
    }

    return vec4(AmbientColor += (DiffuseColor1 + SpecularColor1), 1.0 	);
	//return vec4(SpecularColor1, 1.0 	);
	//return (AmbientColor + SpecularColor );
}

vec4 CalcDirectionalLight(float ID, vec3 WorldPos,float Depth, vec3 Normal,float AO)
{
    return CalcLightInternal(gDirectionalLight.Base,
							 gDirectionalLight.Direction,
							 ID,
							 WorldPos,
							 Depth,
							 Normal,
							 AO);
}

vec4 CalcPointLight(float ID, vec3 WorldPos, float Depth, vec3 Normal,float AO)
{
    vec3 LightDirection = WorldPos - gPointLight.Position;
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);

    vec4 Color = CalcLightInternal(gPointLight.Base, LightDirection,ID, WorldPos,Depth, Normal,AO);

    float Attenuation =  gPointLight.Atten.Constant +
                         gPointLight.Atten.Linear * Distance +
                         gPointLight.Atten.Exp * Distance * Distance;

    Attenuation = max(1.0, Attenuation);

    return Color / Attenuation;
}


vec2 CalcTexCoord()
{
    return gl_FragCoord.xy / gScreenSize;
}

out vec4 FragColor;

void main()
{
	//mat3 viewNormal = transpose(inverse(mat3(gView)));
	//mat3 viewNormal = transpose(mat3(gView));
	//int draw_mode = 0;
	//float debug = 1.0f;
	//vec4 Debugger = vec4(0, 0, 0, 0);

    vec2 TexCoord = CalcTexCoord();
	vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
	float Depth = texture(gPositionMap, TexCoord).a;
	//material id
	vec3 Color = texture(gAbedoMap, TexCoord).xyz;

	//int MatId = int(texture(gUvMap, TexCoord).z);
	//int MatId = int(texture(gUvMap, TexCoord).z);
	float MatId = texture(gUvMap, TexCoord).z;
	//int MatId = int(texture(gColorMap, TexCoord).x);
	//for some reasong gColormMap has the same handle as gPositionm
	
	

	vec4 Diff;
	vec4 Spec;

	LookUpMaterial(MatId, Diff, Spec);


    vec3 Normal = texture(gNormalMap, TexCoord).xyz;
	vec2 Uv = texture(gUvMap, TexCoord).xy;
	//vec2 texelSize =  vec2(textureSize(gAoPass, 0));
	float AmbientOcculsion = texture(gAoPass, TexCoord ).r;


	vec3 satan = Normal;
	//Normal = normalize(Normal);
	//Normal = normalize(Normal * 2.0 - 1.0);
	//Normal = normalize(viewNormal * Normal);

	FragColor = vec4(Color, 1.0) *  CalcDirectionalLight(MatId,WorldPos, Depth,satan,AmbientOcculsion);
	//FragColor = Diff * 
	//FragColor =  CalcDirectionalLight(MatId,WorldPos, Depth,satan,AmbientOcculsion);
	//FragColor = Diff;
	//FragColor = vec4(WorldPos, 1.0) * CalcDirectionalLight(WorldPos, Normal,AmbientOcculsion);
	//FragColor = vec4(Normal, 1.0) * 10;
	//FragColor = CalcDirectionalLight(WorldPos, Normal,AmbientOcculsion);
	//FragColor = vec4(Uv,0.0, 1.0);

}
