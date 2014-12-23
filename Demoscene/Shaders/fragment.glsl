#version 330


in vec3 Normal;
uniform vec4 Ambiance;

out vec4 output;

void main()
{
	vec4 color;
	vec4 amb;
	vec4 diff;
	vec4  spec;
	vec4 emmi;
//	vec shiny;

	float intensity;
	vec3 lightDir;
	vec3 n;
		
	
	lightDir = normalize(vec3(1.0,1.0,1.0));
	n = normalize(Normal);	
	intensity = max(dot(lightDir,n),0.0);
	

		color = Ambiance;
		amb = vec4(0.2, 0.2, 0.2, 1.0);

	
	output = (color * intensity) + amb;
	

}
