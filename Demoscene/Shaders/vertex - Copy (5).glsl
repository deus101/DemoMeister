uniform vec3 v_Light;
uniform vec3 v_SkyC;
uniform vec3 v_GroundC;

varying vec3 Frag_Diffuse;

varying vec3 V;

varying vec3 diffuseColor;
varying vec3 specularColor;
varying vec3 emissiveColor;
varying vec3 ambientColor;
varying float shininess;







void main(void)
{


//øye koordinater(ecPostition)
V = gl_ModelViewMatrix * gl_Vertex;
//tnorm
vec3 N = normalize(gl_NormalMatrix * gl_Normal);


//lys vektor 
vec3 L = normalize(v_Light - V);

//
vec3 H = normalize(L + vec3(0.0, 0.0, 1.0));


float costheta = dot(N, L);
float a = 0.5 + 0.5 * costheta;


const float specularity = 128.0;


//Normalisert dot produkt til lys
float NdotL = max(0.0, dot(N, L));

//endre denne eller?
vec4 diffuse = gl_Color * vec4(NdotL);

float NdotH = max(0.0, dot(N, H));	

//var dette fargen?
vec4 specular = vec4(0.0);


//
if(NdotL > 0.0)
specular = vec4(pow(NdotH, specularity));


    
Frag_Diffuse =  mix(v_GroundC, v_SkyC, a) + vec3( diffuse );
gl_FrontColor = diffuse + specular ;


gl_Position     = ftransform();



 diffuseColor = vec3(gl_FrontMaterial.diffuse);
 specularColor = vec3(gl_FrontMaterial.specular);
 emissiveColor = vec3(gl_FrontMaterial.emission);
 ambientColor = vec3(gl_FrontMaterial.ambient);
 shininess = gl_FrontMaterial.shininess;

}


