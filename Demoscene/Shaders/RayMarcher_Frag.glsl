#version 330

smooth in vec2 uv;
smooth in vec3 v;
smooth in vec3 EP;

layout (location = 0) out vec4 WorldPosOut;   
layout (location = 1) out vec3 DiffuseOut;     
layout (location = 2) out vec3 NormalOut;  

uniform mat4 gWVP;
uniform mat4 gProjection;
uniform mat4 gView;


uniform vec2 gScreenSize;
uniform vec3 gEyeWorldPos;
//0.52359877559
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
	return sdBox(p - vec3(1.75f, -0.25f, 0.25f), vec3(0.25f));



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
	vec2 m = mod(p.xz, 4.0f) - vec2(2.0f);
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

	vec2 NDC = vec2(0.0);


	//Im just drawing a simple square so no need to divide it to image size
	NDC.x = (uv.x*0.5+0.5);
	//NDC.y = (uv.y*0.5+0.5);
	//NDC.x = -(uv.x*0.5-0.5);
	NDC.y = -(uv.y*0.5-0.5);
	
	
	//gWVP
	//mat4 iVP = inverse(gView);
	//mat4 VP = gProjection * gView;
	//EP
	//vec3 ro = gEyeWorldPos;

	//ro = -(vec4(0,0,0,1)*gView).xyz;
	//vec3 ro = gEyeWorldPos + EP;
	
	vec4 color = vec4(1.0); 
	
	vec4 skyColor = vec4(0.54 ,0.824,1.0,1.0);
	vec3 normal = vec3(0.0);




	vec3 viewRight = normalize(vec3(1.0,0.0,0.0)*mat3(gView));
	vec3 viewUp = normalize(vec3(0.0,1.0,0.0)*mat3(gView));
	


	vec3 viewForward = cross( viewUp,viewRight);



	float aspectRatio = gScreenSize.x / float(gScreenSize.y);
	vec2 aspect = vec2(float(gScreenSize.x)/float(gScreenSize.y), 1.0); 
    vec2 screenCoords = (2.0*uv.xy/vec2(float(gScreenSize.x), float(uv.y)) - 1.0)*aspect;
	vec2 screenPos = (2.0*gl_FragCoord.xy-vec2(float(gScreenSize.x), float(gScreenSize.y)))/float(gScreenSize.y);

	
	float FovY = radians(60.0);
	float FovYscale = FovY * aspectRatio;
	float Fuck = (tan(FovY) );
	float scale = tan(FovY / 2); 
	//float scale = tan(radians(60.0 * 0.5)); 
	//float scale = gProjection[1].y;

	float pixelScreenX = 2 * NDC.x -1;
	//float pixelScreenY = 2 * NDC.y -1;

	float pixelScreenY = 1 - 2 * NDC.y;
	//float pixelScreenX = 1 - 2 * NDC.x;
	
	//PixelCamera
	float Px = (pixelScreenX ) * scale * aspectRatio;
	float Py = (pixelScreenY) * scale;
	//float Px = (pixelScreenX ) * scale;
	//float Py = (pixelScreenY) * scale * 1 / aspectRatio;
	//Oh yeah, note to self stop working while tired


	//float Px = NDC.x * aspectRatio *scale;
	//float Py = NDC.y * scale;
	//float Px = ((pixelScreenX ) * scale * aspectRatio) / 2;
	//float Py = ((pixelScreenY) * scale) / 2;


	//focalLenght
	vec3 rayOrigin = vec3(0.0, 0.0, 0.0); 
	//vec3 rayOrigin = viewForward * -focalLenght;
	//vec3 rayOrigin = vec3(0.0, 0.0, -focalLenght); 

	
	mat4 CamToWorld = inverse(gView);
	//mat4 CamToWorld = inverse(gWVP);


	mat4 CamToWorldTR = transpose(CamToWorld);



	vec3 rayOriginWorld = (vec4(rayOrigin,1)*CamToWorldTR).xyz;



	vec3 rayPWorld = vec3(0.0); 
	
	//remember perspective is seen from above, dofus
	vec3 w_p = (-(aspectRatio*2) / 2 ) * CamToWorldTR[0].xyz + (2 / 2) * CamToWorldTR[1].xyz - ((2 / 2) / tan(FovY * 0.5));
	//vec3 NDCrd = normalize(pixelScreenX * CamToWorldTR[0].xyz + pixelScreenY * (-CamToWorldTR[1].xyz) + w_p); 
	
	
	vec3 NDCrd = normalize(NDC.x * CamToWorldTR[0].xyz + NDC.y * (-CamToWorldTR[1].xyz) + w_p); 

	

	rayPWorld = (vec4(vec3(Px, Py, -1), 1.0)*CamToWorldTR).xyz;

	//rayPWorld = (vec4(vec3(Px, Py, -0.1), 1.0)*CamToWorldTR).xyz;


	

	//one is just a direction, the fuck am i doing?!
	//vec3 worldDir =  rayOriginWorld - rayPWorld;
	vec3 worldDir =  rayPWorld - rayOriginWorld;

	//vec3 eyeFwd = viewForward;
	vec3 eyeFwd = normalize(worldDir);
	//vec3 rd = normalize(worldDir);
	vec3 rd = NDCrd;
	//vec3 ro = rayOriginWorld - worldDir * focalLenght;
	//vec3 ro = gEyeWorldPos - (worldDir * vec3(0 , 0 , -focalLenght));



	//vec3 ro = gEyeWorldPos * 1;
	vec3 ro = vec3(0,0,0);
	//What the fuck, what is it Im not getting!
	
	//ro = ro * focalLenght;
	
	float t0;
	
	int i;

	
	pewpew(ro, rd, i, t0);
	vec3 floorNormal = vec3(0, 1, 0);


	//float eyeHitZ = -t0 *dot(normalize(EP),rd);
	//float ndcDepth = ((FAR+NEAR) + (2.0*FAR*NEAR)/eyeHitZ)/(FAR-NEAR);
	float eyeHitZ = 0.0;
	float ndcDepth = 0.0;
	float t1 = infPlane(ro, rd, floorNormal, vec3(0, -0.5, 0));
	
	//hmmm
	//vec3 p = ro + rd * t1;
	vec3 p = vec3(0.0);
	//normal = floorNormal;
	float dep = 0.0f;

	float t;
	float z = 0;
	if(t1 < t0 && t1 >= NEAR && t1 <= FAR) 
	{
		t = t1;
		p = (ro + (rd * t));
		//p = (gProjection * vec4(p,1)).xyz;
		//eyeHitZ = -t *dot(rd,eyeFwd);
		eyeHitZ = -t *dot(eyeFwd,rd);
		//eyeHitZ = -t *dot(normalize(viewForward),rd);
		ndcDepth = ((FAR+NEAR) + (2.0*FAR*NEAR)/eyeHitZ)/(FAR-NEAR);

		normal = floorNormal;
		color = chessBoard(p);
		//float Col = i / 64 + 64.0f;
		//color = vec4(0.512,0.0,0.0,1.0);
		dep = distance(ro, p);
		z = mapTo(t, NEAR, FAR, 1, 0);

		//dep = LinearDepth(z);

	}
	else if(i < raySteps && t0 >= NEAR  && t0 <= FAR) 
	{
	
		t = t0;
		p = ro + (rd * t);
		//p = (gProjection * vec4(p ,1)).xyz;
		//eyeHitZ = -t *dot(rd,eyeFwd);
		eyeHitZ = -t *dot(eyeFwd,rd);

		//eyeHitZ = -t *dot(normalize(viewForward),rd);
		ndcDepth = ((FAR+NEAR) + (2.0*FAR*NEAR)/eyeHitZ)/(FAR-NEAR);
		normal = getNormal(p);
		dep = distance(ro, p);
		z = mapTo(t, NEAR, FAR, 1, 0);
		//dep = LinearDepth(z);

	}
	else
	{
		color = skyColor;

		//p.y = p.z;
		//eyeHitZ = -FAR *dot(rd,eyeFwd);
		eyeHitZ = -FAR *dot(eyeFwd,rd);
		//eyeHitZ = -FAR *dot(normalize(viewForward),rd);

		ndcDepth = ((FAR+NEAR) + (2.0*FAR*NEAR)/eyeHitZ)/(FAR-NEAR);
		p = ro + (rd * FAR);
		//p = (gProjection * vec4(p,1)).xyz;
		z = mapTo(t, NEAR, FAR, 1, 0);
		//normal = vec3(0,-1,0);
		//dep = distance(ro, p) * 20000;
		//ndcDepth = FAR;
	}


	//p.z = p.z * z;
	//float zc = (VP * vec4(p, 1.0 )).z;

	//float wc = (VP * vec4(p, 1.0 )).w;

	gl_FragDepth = ndcDepth;
	//gl_FragDepth = zc / wc;


	//float zSqrd = z * z;
	//color = mix(skyColor, color, zSqrd * (3.0f - 2.0f * z)); // Fog
	

	//WorldPosOut.xyz = p /wc;
	//WorldPosOut.xyz = p / 2;
	//WorldPosOut.w = dep / 2;
	WorldPosOut.xyz = p;
	//WorldPosOut.w = dep * 0.5;
	
	//WorldPosOut.w = z;
	WorldPosOut.w = LinearDepth(ndcDepth);
	//WorldPosOut.xyz = p;
	//WorldPosOut.w = dep;

	//WorldPosOut.w = scale;
	//WorldPosOut.w = projected.z;
	
	//DiffuseOut = applyFog(color.xyz,t);
	//DiffuseOut = vec3(NDC.x, NDC.y,0);
	//DiffuseOut = vec3(pixelScreenX, pixelScreenY,-1);
	
	//DiffuseOut = color.xyz;
	//DiffuseOut = rayOriginWorld;
	//DiffuseOut = rayOriginWorld;
	//DiffuseOut = rayPWorld;
	//DiffuseOut = RayDir;
	//DiffuseOut = worldDir;
	DiffuseOut = rd;
	//DiffuseOut = NDCrd;
	
	//NormalOut = normal;
	//NormalOut = w_p;
	NormalOut = NDCrd;
	//NormalOut.xy = NDC.xy;
	//NormalOut = vec3(pixelScreenX, pixelScreenY,-1);
	//NormalOut = vec3(eyeHitZ,t,dep);
	//NormalOut = vec3(pixelScreenX, pixelScreenY,-1);
	//NormalOut = rayOriginWorld.xyz;

}