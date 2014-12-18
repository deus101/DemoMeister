varying vec3 Frag_Diffuse; 

varying vec3 diffuseColor;
varying vec3 specularColor;
varying vec3 emissiveColor;
varying vec3 ambientColor;
varying float shininess;











void main(void)
{

 

gl_FragColor = vec4(Frag_Diffuse, 1.0) + mix(gl_Color, vec4( vec3(gl_SecondaryColor), 1.0), 0.5);


}