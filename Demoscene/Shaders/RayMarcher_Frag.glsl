#version 330

smooth in vec2 uv;
//smooth in vec3 v;
//smooth in vec3 EP;

layout (location = 0) out vec4 WorldPosOut;   
layout (location = 1) out vec3 DiffuseOut;     
layout (location = 2) out vec3 NormalOut;  

uniform mat4 gWVP;
uniform mat4 gProjection;
uniform mat4 gView;


uniform vec2 gScreenSize;
uniform vec3 gEyeWorldPos;



const float focalLenght = 1.67f; 
//const float focalLenght = 0.67f; 
//const float focalLenght = 1.52; 
//const float focalLenght = 0.52; 


const float NEAR = 0.1f;
const float FAR = 50.0f;

const int raySteps		= 64;
const float rayEpsilon = 0.001f;

const float PI = 3.141592653589793238462643383;


vec2 spherical(vec3 d) {
	return vec2( acos(d.z), atan(d.y,d.x) );
}

float mapTo(float x, float minX, float maxX, float minY, float maxY)
{
	float a = (maxY - minY) / (maxX - minX);
	float b = minY - a * minX;
	return a * x + b;
}

float sdSphere( vec3 p, float s )
{
  return length(p)-s;
}

float udBox(vec3 p, vec3 size)
{
	return length(max(abs(p) - size, vec3(0.0f)));
}

float sdBox(vec3 p, vec3 size)
{
	vec3 d = abs(p) - size;
	return min(max(d.x, max(d.y, d.z)), 0.0f) + udBox(p, size);
}


float distScene(vec3 p)
{
	//p.xz = mod(p.xz, 2.0f) - vec2(1.0f);
	//return sdBox(p - vec3(0.0f, -0.25f, 0.0f), vec3(0.01f));
	float s_sphere = sdSphere(p - vec3(0.0f, 1.0f, 0.0f), 3.0f);
	float s_box =  sdBox(p - vec3(0.0f, 1.0f, 0.0f), vec3(2.25f));

	//return max(s_box, s_sphere);
	return max(-s_sphere, s_box);
}


void pewpew(vec3 orig, vec3 dir, out int i, out float t)
{
	t = 0.0;
	i = 0;
	for(i = 0; i < raySteps; i++)
	{
		float dist = distScene(orig + dir * t);

		if(dist < rayEpsilon * t * 2.0 || t > FAR)
			break;
		t += dist;
	}
}





//void dissectView()

vec3 getNormal(vec3 p)
{
	float h = 0.0001f;

	return normalize(vec3(
		distScene(p + vec3(h, 0, 0)) - distScene(p - vec3(h, 0, 0)),
		distScene(p + vec3(0, h, 0)) - distScene(p - vec3(0, h, 0)),
		distScene(p + vec3(0, 0, h)) - distScene(p - vec3(0, 0, h))));
}

vec4 chessBoard(vec3 p)
{
	//vec2 m = mod(p.xz, 0.5f) - vec2(0.05f,0.5f);
	vec2 m = mod(p.xz, 4.0f) - vec2(2);
	return m.x * m.y > 0.0f ? vec4(0.1f) : vec4(1.0f);
}


vec3 applyFog( in vec3  rgb,       
               in float distance ){
	float b = NEAR / FAR;
    float fogAmount = 1.0 - exp( (-distance)*b );
   vec3  fogColor  = vec3(0.5,0.6,0.7);
   return mix( rgb, fogColor, fogAmount );
}

float infPlane(vec3 ro, vec3 rd, vec3 n, vec3 o)
{
	return dot(o - ro, n) / dot(rd, n);
}

float LinearDepth(float depth)
{
    float z = depth * 2.0 - 1.0; 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));	
}


void main()
{	


	vec4 color = vec4(1.0); 
	
	vec4 skyColor = vec4(0.54 ,0.824,1.0,1.0);
	vec3 normal = vec3(0.0);

	
	//vec3 viewRight = normalize(vec3(1.0,0.0,0.0)*mat3(gView));
	//vec3 viewUp = normalize(vec3(0.0,1.0,0.0)*mat3(gView));
	//vec3 viewForward = cross( viewUp,viewRight);




	//time to fix the variables
	vec2 aspect = vec2(float(gScreenSize.x)/float(gScreenSize.y), 1.0); 

	float aspectRatio = gScreenSize.x / float(gScreenSize.y);
	

	vec3 eye = vec3(0, 0, -1);
    vec3 up = vec3(0, 1, 0);
    vec3 right = vec3(1, 0, 0);
	
	vec2 Pixel = vec2(0.0); 
	vec2 NDC = vec2(0.0);
	vec2 PixelNDC = vec2(0.0);
	vec2 PixelScreen = vec2(0.0);
	vec2 PixelCamera = vec2(0.0);
	vec3 PcameraSpace = vec3(0.0);
	

	float FovY = radians(60.0);
	float FovYscale = FovY * aspectRatio;
	float scale = tan(FovY / 2); 
	


	//UV
	//Pixel.x = gl_FragCoord.x * 2.0 / gScreenSize.x - 1.0;
	//Pixel.y = gl_FragCoord.y * 2.0 / gScreenSize.y - 1.0;



	PixelNDC.x =  (gl_FragCoord.x + 0.5) / gScreenSize.x;
	PixelNDC.y =  (gl_FragCoord.y + 0.5) / gScreenSize.y;



	PixelScreen.x = 2 * PixelNDC.x -1;
	//PixelScreen.x =  1 - 2 * PixelNDC.x;
	PixelScreen.y = 2 * PixelNDC.y -1;
	//PixelScreen.y =  1 - 2 * PixelNDC.y;



	//PixelCamera.x = (2 * PixelScreen.x - 1) * aspectRatio * scale;
	//PixelCamera.y = (1 - 2 * PixelScreen.y) * scale;	


	//Don't fuck this up
	PixelCamera.x = (PixelScreen.x) * scale * aspectRatio;
	PixelCamera.y = (PixelScreen.y) * scale;


	PcameraSpace = vec3(PixelCamera.x,PixelCamera.y, -1);



	//focalLenght
	vec3 rayOrigin = vec3(0.0, 0.0, 0.0); 
	


	mat4 GviewInv = inverse(gView);
	
	
	mat4 CamToWorld = gWVP * GviewInv;


	//mat4 CamToWorldTR = gWVP * transpose(gView);

	mat4 CamToWorldTR = transpose(gView);
	//mat4 CamToWorldTR = transpose(gView)*gWVP;
	//mat4 CamToWorldTR = gWVP * transpose(gView);



	//vec3 rayPWorld = vec3(0.0); 
	
	

	vec3 Asp = CamToWorldTR[2].xyz * -1;
	//CamToWorldTR[3].xyz = CamToWorldTR[2].xyz * -1;

	//CamToWorldTR[2] = CamToWorldTR[2] * -1;
	//CamToWorldTR = transpose(CamToWorldTR);
	//GviewInv[2].xyz = Asp;

	//vec3 eye = -(gView[3].xyz)*mat3(gView);
	//vec3 eye = (gView[3].xyz)*mat3(gView);
	
	//rayPWorld = vec3(0, 0,-1.0) * mat3(CamToWorldTR);
	
	
	//vec3 rayOriginWorld = (  vec4(rayOrigin,1)*GviewInv).xyz;
	//vec3 rayOriginWorld = (  vec4(rayOrigin,1)*-CamToWorldTR).xyz;
	
	//vec3 rayOriginWorld = (  GviewInv * vec4(rayOrigin,1)).xyz;
	vec3 rayOriginWorld = (  CamToWorld * vec4(rayOrigin,1)).xyz;

	//vec3 rayPWorld = (  vec4(vec3(0, 0,-1.0),0)*GviewInv).xyz;
	//vec3 rayPWorld = vec3(0, 0,-1.0) * mat3(-CamToWorldTR);
	//vec3 rayPWorld = ( GviewInv * vec4(vec3(0, 0,-1.0),0)).xyz;
	vec3 rayPWorld = ( CamToWorld * vec4(vec3(0, 0,-1.0),0)).xyz;


	//vec3 eyeFwd = normalize(vec3(0,0,-1.0)*mat3(gView));

	vec3 worldDir = normalize( rayPWorld - rayOriginWorld);
	

	

	//PcameraSpace  rayOriginWorld
	//vec3 ro = rayOriginWorld * focalLenght;
	//vec3 ro = gEyeWorldPos + PcameraSpace *  scale;
	//vec3 ro = PcameraSpace + rayOriginWorld * gEyeWorldPos;

	//vec3 ro = eye; 
	//vec3 ro = rayOriginWorld + vec3(PixelCamera.x * scale * aspectRatio , PixelCamera.y * scale, scale); 
	vec3 ro = rayOriginWorld;
	
	
	//vec3 pre_RD = PcameraSpace + right * PixelCamera.x * scale * aspectRatio + up * PixelCamera.y * scale;
	vec3 pre_RD =  PcameraSpace;

	//transpose(inverse(mat3(gView)));
	
	//vec3 rd = normalize( (gView * vec4(pre_RD,0)).xyz  );

	//this sorta works dont delete and forget you dumb fucker
	vec3 rd = normalize( (CamToWorld * vec4(pre_RD,0)).xyz  );



	//vec3 rd = normalize( (-scale * PcameraSpace) + right * PixelCamera.x * aspectRatio + up * PixelCamera.y  );
	//vec3 rd = normalize( PcameraSpace + right * PixelCamera.x * scale * aspectRatio + up * PixelCamera.y * scale);
	
	float t0;
	
	int i;

	
	pewpew(ro, rd, i, t0);
	vec3 floorNormal = vec3(0, 1, 0);



	//float eyeHitZ = -t0 *dot(normalize(EP),rd);
	//float ndcDepth = ((FAR+NEAR) + (2.0*FAR*NEAR)/eyeHitZ)/(FAR-NEAR);


	float eyeHitZ = 0.0;
	float ndcDepth = 0.0;
	
	float t1 = infPlane(ro, rd, floorNormal, vec3(0, -0.5, 0));


	vec3 p = vec3(0.0);
	//normal = floorNormal;


	float dep = 0.99f;
	gl_FragDepth = dep;
	float t;
	float z = 0;


	if(t1 < t0 && t1 >= NEAR && t1 <= FAR) 
	{
		t = t1;
		
		p = (ro + (rd * t));

		eyeHitZ = -t *dot(worldDir,rd);

		ndcDepth = ((FAR+NEAR) + (2.0*FAR*NEAR)/eyeHitZ)/(FAR-NEAR);
		normal = floorNormal;
		color = chessBoard(p);

		dep = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
	}
	else if(i < raySteps && t0 >= NEAR  && t0 <= FAR) 
	{
	
		t = t0;
		p = (ro + (rd * t));

		
		eyeHitZ = -t *dot(worldDir,rd);
		ndcDepth = ((FAR+NEAR) + (2.0*FAR*NEAR)/eyeHitZ)/(FAR-NEAR);

		normal = getNormal(p);

		dep = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
	}
	else
	{
		color = skyColor;

		//p.y = p.z;
		//eyeHitZ = -FAR *dot(rd,eyeFwd);
		eyeHitZ = -FAR *dot(worldDir,rd);
		//eyeHitZ = -FAR *dot(normalize(viewForward),rd);

		ndcDepth = ((FAR+NEAR) + (2.0*FAR*NEAR)/eyeHitZ)/(FAR-NEAR);
		p = ro + (rd * FAR);
		//p = (gProjection * vec4(p,1)).xyz;
		//z = mapTo(t, NEAR, FAR, 1, 0);
		//normal = vec3(0,-1,0);
		//dep = distance(ro, p) * 20000;
		//ndcDepth = FAR;
	}




	//gl_FragDepth = ndcDepth;
	//dep = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
	gl_FragDepth = dep;
	


	//float zSqrd = z * z;
	//color = mix(skyColor, color, zSqrd * (3.0f - 2.0f * z)); // Fog
	
	WorldPosOut.xyz = p;
	WorldPosOut.w = LinearDepth(dep);

	//WorldPosOut = CamToWorld[2];
	
	//WorldPosOut.w = scale;
	//WorldPosOut.w = projected.z;
	
	//DiffuseOut = applyFog(color.xyz,t);
	//DiffuseOut = vec3(NDC.x, NDC.y,0);
	//DiffuseOut = vec3(pixelScreenX, pixelScreenY,-1);
	
	DiffuseOut = color.xyz;
	//DiffuseOut = vec3(Pixel.x, Pixel.y,0);
	//DiffuseOut = rayOriginWorld;
	//DiffuseOut = rayOriginWorld;
	//DiffuseOut = rayPWorld;
	//DiffuseOut = RayDir;
	//DiffuseOut = worldDir;
	//DiffuseOut = vec3(PixelNDC.x, PixelNDC.y ,0);
	//DiffuseOut = vec3(NDC.x, NDC.y,uv.x);
	//DiffuseOut = vec3(Pixel.x, Pixel.y,0);
	
	//NormalOut = CamToWorldTR[0].xzw;
	NormalOut = normal;
	//NormalOut = w_p;
	//NormalOut = PcameraSpace;
	//NormalOut = vec3(uv.x, uv.y,0);
	//NormalOut = vec3(eyeHitZ,t,dep);
	//NormalOut = vec3(PixelScreen.x, PixelScreen.y,0);
	//NormalOut = vec3(uv.x, uv.y,0);
	//NormalOut = vec3(PixelNDC.x, PixelNDC.y,0);
	//NormalOut = vec3(PixelScreen.x, PixelScreen.y,0);
	//NormalOut = vec3(aspectRatio, scale,0);
	//NormalOut = (gView*vec4(rayOrigin,1)).xyz;
	//NormalOut = normalize((gView*vec4(rayOrigin,1)).xyz + (gView*vec4(vec3(Px, Py, -1.0), 0.0)).xyz);
	//NormalOut = vec3(gl_FragCoord.xy,0);
	//NormalOut = vec3(PcameraSpace.xy,0);
	//NormalOut = PcameraSpace.xyz;
	//NormalOut = rayOriginWorld;
	//NormalOut = worldDir;
	//NormalOut = rayPWorld;
	//NormalOut.y = dot(rd,eyeFwd);
	//NormalOut.z = eyeHitZ;
	//NormalOut = rd;
	//NormalOut = pre_RD;
}