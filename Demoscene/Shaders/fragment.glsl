#version 330


in vec3 Normal;
in vec4 Eye;
in vec3 LightDir;
uniform vec4 Diffuse;
uniform vec4 Ambiant;
uniform vec4 Specular;
uniform float Shininess;
out vec4 output;

void main()
{
//this would be texture color
	vec4 color;
	vec4 amb;
	vec4 diff;
	vec4 spec = vec4(0.0);
	vec4 emmi;
//	float shiny;

	vec4 scene_ambient = vec4(0.2, 0.2, 0.2, 1.0);	

	float intensity;
	vec3 lightDir;
	vec3 n;
	vec3 e;
	
	
	lightDir = normalize(LightDir);
	n = normalize(Normal);	
	e = normalize(vec3(Eye));
	intensity = max(dot(lightDir,n),0.0);
	

		//color = Ambiance;
		//amb = vec4(0.2, 0.2, 0.2, 1.0);
		diff = Diffuse;
		amb = scene_ambient * Ambiant;
		
	if (intensity > 0.0) {
		// compute the half vector
		vec3 h = normalize(lightDir + e);	
		// compute the specular term into spec
		float intSpec = max(dot(h,n), 0.0);
		spec = Specular * pow(intSpec,Shininess);
	}

	
	output = max(intensity * diff + spec , amb);
}