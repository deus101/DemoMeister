#version 330




in vec3 Normal;

out vec4 output;

void main()
{
	vec4 color;
	vec4 amb;
	float intensity;
	vec3 lightDir;
	vec3 n;
	
	lightDir = normalize(vec3(1.0,1.0,1.0));
	n = normalize(Normal);	
	intensity = max(dot(lightDir,n),0.0);
	

		color = vec4(0.7, 0.0, 0.0, 0.0);
		amb = vec4(0.2, 0.2, 0.2, 0.0);

	
	output = (color * intensity) + amb;
	

}
