#version 330
//Point Light
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

uniform sampler2D gPositionMap;
uniform sampler2D gAbedoMap;
uniform sampler2D gNormalMap;
uniform sampler2D gUvMap;
uniform sampler2D gAoPass;

uniform sampler2D MaterialMap;

uniform mat4 gProjection;
uniform mat4 gView;
uniform mat4 gWorld;

uniform DirectionalLight gDirectionalLight;
uniform PointLight gPointLight;
uniform SpotLight gSpotLight;
uniform vec3 gEyeWorldPos;
uniform float gMatSpecularIntensity;
uniform float gSpecularPower;
uniform int gLightType;
uniform vec2 gScreenSize;


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
					   vec3 Normal,
					   float AO,
					   float Att)
{

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
        
		
		vec3 VertexToEye = normalize(gEyeWorldPos - WorldPos);
        vec3 LightReflect = normalize(reflect(LightDirection, Normal));
        float SpecularFactor = dot(VertexToEye, LightReflect);
        SpecularFactor = pow(SpecularFactor, gSpecularPower);
        
		
		if (SpecularFactor > 0.0) {
            
			SpecularColor1 = Light.Color * gMatSpecularIntensity;
			SpecularColor1 *=  SpecularColor.xyz  *SpecularFactor;
        }
    }
	DiffuseColor1 *= Att;
	SpecularColor1 *= Att;
    return vec4(AmbientColor += (DiffuseColor1 + SpecularColor1), 1.0 	);
}

vec4 CalcDirectionalLight(float ID, vec3 WorldPos, vec3 Normal,float AO, float Attenuation)
{
    return CalcLightInternal(gDirectionalLight.Base,
							 gDirectionalLight.Direction,
							 ID,
							 WorldPos,
							 Normal,
							 AO,
							 Attenuation);
}

vec4 CalcPointLight(float ID, vec3 WorldPos, vec3 Normal,float AO)
{
    vec3 LightDirection = WorldPos - gPointLight.Position;
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);

	float Attenuation =  gPointLight.Atten.Constant +
                         gPointLight.Atten.Linear * Distance +
                         gPointLight.Atten.Exp * Distance * Distance;

    Attenuation = max(1.0, Attenuation);

    vec4 Color = CalcLightInternal(gPointLight.Base, LightDirection,ID, WorldPos, Normal,AO,Attenuation);



    return Color;
}


vec2 CalcTexCoord()
{
    return gl_FragCoord.xy / gScreenSize;
}


out vec4 FragColor;

void main()
{
	mat3 viewNormal = transpose(inverse(mat3(gView)));
	
    vec2 TexCoord = CalcTexCoord();
	vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
	vec3 Color = texture(gAbedoMap, TexCoord).xyz;
	vec3 UVMat = texture(gUvMap, TexCoord).xyz;
	//vec3 Color = texture(MaterialMap, vec2(0,UVMat.z)).xyz;
	float MatId = texture(gUvMap, TexCoord).z;
	vec3 Normal = texture(gNormalMap, TexCoord).xyz;
	float AmbientOcculsion = texture(gAoPass, TexCoord).r;

	Normal = normalize(Normal * 2.0 - 1.0);
	Normal = normalize(viewNormal * Normal);
		
    FragColor = vec4(Color, 1.0) * CalcPointLight(MatId,WorldPos, Normal,AmbientOcculsion);
	//FragColor = CalcPointLight(MatId,WorldPos, Normal,AmbientOcculsion);
}
