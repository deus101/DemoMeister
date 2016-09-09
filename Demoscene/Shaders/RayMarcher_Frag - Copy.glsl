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
//const float focalLenght = 1.52; 
//const float focalLenght = 0.52; 
const float NEAR = 0.1f;
const float FAR = 50.0f;

const int raySteps		= 64;
const float rayEpsilon = 0.001f;

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
	p.xz = mod(p.xz, 1.0f) - vec2(0.5f);
	return sdBox(p - vec3(0.0f, -0.25f, 0.0f), vec3(0.25f));


}

//does this work with 330 or do I need to change something?
//I don't think I've quite got a good grasp of glsl versions
void pewpew(vec3 orig, vec3 dir, out int i, out float t)
{
	t = 0.0;
	for(i = 0; i < raySteps; ++i)
	{
		float dist = distScene(orig + dir * t);

		//if(dist < rayEpsilon * t * 2.0 || t > FAR)

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
	vec2 m = mod(p.xz, 2.0f) - vec2(1.0f);
	return m.x * m.y > 0.0f ? vec4(0.1f) : vec4(1.0f);
}


//vec3 applyFog( in vec3  rgb,       
//               in float distance ){
//    float fogAmount = 1.0 - exp( -distance*b );
//    vec3  fogColor  = vec3(0.5,0.6,0.7);
//   return mix( rgb, fogColor, fogAmount );
//}

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

	mat4 iVP = inverse(gView);
	mat4 VP = gProjection * gView;

	//vec3 ro = mat3(gView) * gEyeWorldPos ;
	//vec3 ro = gEyeWorldPos * mat3(gView);

	vec3 ro =  gEyeWorldPos;

	//ro.z = ro.z + focalLenght;
	//nope im using components from the view allready cant use that
	//vec3 ro = EP;
	
	vec4 color = vec4(1.0); 
	
	vec4 skyColor = vec4(0.54 ,0.824,1.0,1.0);
	vec3 normal = vec3(0.0);



	//vec3 viewRight = normalize(vec3(1.0,0.0,0.0)*mat3(gView));
	//vec3 viewUp = normalize(vec3(0.0,1.0,0.0)*mat3(gView));
	//vec3 viewForward = normalize(vec3(0,0,-1.0)*mat3(gView));


	vec3 viewRight = normalize(vec3(1.0,0.0,0.0)*mat3(gView));
	vec3 viewUp = normalize(vec3(0.0,1.0,0.0)*mat3(gView));
	
	//vec3 viewForward = vec3(0,0,-1)*mat3(gView);
	//vec3 viewForward = vec3(0,0,-1)*mat3(gView);


	vec3 viewForward = normalize(cross( viewUp,viewRight));
	//vec3 viewForward = cross( viewUp,viewRight);
	//vec3 viewForward = cross( viewRight,viewUp);



	float aspectRatio = gScreenSize.x / float(gScreenSize.y);
	vec2 aspect = vec2(float(gScreenSize.x)/float(gScreenSize.y), 1.0); 
    vec2 screenCoords = (2.0*uv.xy/vec2(float(gScreenSize.x), float(uv.y)) - 1.0)*aspect;
	vec2 screenPos = (2.0*gl_FragCoord.xy-vec2(float(gScreenSize.x), float(gScreenSize.y)))/float(gScreenSize.y);

	
	float FovY = radians(60.0);
	float FovYscale = FovY * aspectRatio;
	float Fuck = (tan(FovY) );


	//vec3 rdx = viewRight;
	//vec3 rdy = viewUp; 

	//vec3 rdx = viewRight * uv.x;
	//vec3 rdy = viewUp * uv.y; 
	//vec3 rdz = viewForward * Fuck;

	vec3 rdx = viewRight * uv.x * aspectRatio;
	vec3 rdy = viewUp * uv.y; 
	//vec3 rdx = viewRight * screenPos.x * aspectRatio;
	//vec3 rdy = viewUp * screenPos.y; 
	//vec3 rdx = viewRight * (uv * screenPos).x * FovYscale / aspectRatio;
	//vec3 rdy = viewUp * (uv * screenPos).y * FovY / aspectRatio; 

	//vec3 rdx = viewRight * (uv.x * screenPos.x);
	//vec3 rdy = viewUp * (uv.y * screenPos.y);
	//vec3 rdz = viewForward * Fuck;
	//vec3 rdz = viewForward * (tan(FovY) );
	//vec3 rdz = viewForward * focalLenght;
	//vec3 rdz = cross(rdy, rdx);
	//vec3 rdz = cross(rdx, rdy);

	//vec3 rdx = viewRight * uv.x;
	//vec3 rdy = viewUp * uv.y;
	//vec3 rdz = viewForward * Fuck;	
	//vec3 rdz = viewForward;
	//vec3 rdz = normalize(cross( rdy,rdx));
	//vec3 rdz = viewForward * focalLenght * aspectRatio;
	vec3 rdz = viewForward * focalLenght;

	
	//vec3 rd = normalize(viewForward * focalLenght  + (viewRight * uv.x * aspectRatio* FovY) + viewUp * uv.y );
	//vec3 rd = normalize((viewForward * focalLenght *aspectRatio )  + (viewRight * uv.x * FovYscale * aspectRatio / aspectRatio)  + (viewUp * uv.y * aspectRatio / aspectRatio));
	//vec3 rd = normalize((viewForward * focalLenght  )  + (viewRight * uv.x * FovYscale * (aspectRatio / aspectRatio))  + (viewUp * uv.y * (aspectRatio / aspectRatio)));
	


	//vec3 rd = normalize(viewForward * focalLenght + viewRight * uv.x * aspectRatio + viewUp * uv.y);
	//vec3 rd = normalize(viewForward * focalLenght + viewRight * screenCoords.x  + viewUp * screenCoords.y);

	//vec3 rd = normalize(viewForward + viewRight * uv.x * aspectRatio  + viewUp * uv.y);

	//rd = rd * 0.5;

	vec3 rd = normalize(rdx + rdy + rdz);
	//vec3 rd = rdx + rdy + normalize(rdz);
	//vec3 rd = normalize(cross(viewRight,viewUp ));
	//vec3 rd = normalize(cross(viewUp, viewRight));



	float t0;
	int i;

	//ro = ro + vec3(0.0, Fuck,Fuck);
	//ro = ro + rd * .2;
	//ro = ro + rd;
	//ro = ro * focalLenght;
	//ro = ro * Fuck;
	//ro = (gProjection * vec4(ro,1.0)).xyz;
	//ro = ( vec4(ro,1.0) * gProjection).xyz;

	//ro.xy = ro.xy +  screenPos;


	//ro = ro * (uv.x * screenPos.x);
	//ro = ro * (uv.y * screenPos.y);

	//ro.z = ro.z;

	//focalLenght
	//ro = (gView * vec4(0.0f, 0.0f, 0.0f,1.0f)).xyz;
	//ro = ( vec4(0.0f, 0.0f, 0.0f,1.0f) *gView).xyz;
	//ro = ( vec4(vec3(viewForward * focalLenght),1.0f) *gView).xyz;
	//vec3 planePos = viewForward * -focalLenght;
	//ro = ( vec4(planePos,1.0f) * gView ).xyz;
	//ro = ro - (  vec4(planePos,1.0f)*gView).xyz;

	pewpew(ro, rd, i, t0);
	vec3 floorNormal = vec3(0, 1, 0);


	float t1 = infPlane(ro, rd, floorNormal, vec3(0, -0.5, 0));
	
	//hmmm
	vec3 p = ro + rd * t1;
	//normal = floorNormal;
	float dep = 0.0f;

	float t;
	float z = 0;
	if(t1 < t0 && t1 >= NEAR && t1 <= FAR) 
	{
		t = t1;
		p = ro + rd * t1;
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
		p = ro + rd * t0;
		normal = getNormal(p);
		dep = distance(ro, p);
		z = mapTo(t, NEAR, FAR, 1, 0);
		//dep = LinearDepth(z);

	}
	else
	{
		color = skyColor;

		//p.y = p.z;
		p = ro + rd * FAR;
		z = mapTo(t, NEAR, FAR, 1, 0);
		dep = FAR;
	}

	//debug
	//color.x = Fuck;
	//color.y = FovYs;
	//color.z = ro.z;

	//p.z = p.z * z;
	float zc = (VP * vec4(p, 1.0 )).z;

	float wc = (VP * vec4(p, 1.0 )).w;
	//p = (VP * vec4(p, 1.0 )).xyz;
	//p = (VP * vec4(p, 0.0 )).xyz;
	//p = ( vec4(p, 1.0 ) * VP).xyz;
	//p = (vec4(p, 0.0 )*VP).xyz;

	//p = (gProjection * vec4(p, 1.0 )).xyz;
	//p = (gProjection * vec4(p, 0.0 )).xyz;
	//p = ( vec4(p, 1.0 ) * gProjection).xyz;
	//p = (vec4(p, 0.0 )*VP).xyz;


	//vec3 wPos = (iVP * vec4(p,1.0)).xyz;
	//vec3 wPos = (VP * vec4(p,1.0)).xyz/wc;
	
	//gl_FragDepth = z;
	//float fragDep = p.z /wc;
	float fragDep = zc/wc;
	gl_FragDepth = fragDep;
	

	float zSqrd = z * z;
	color = mix(skyColor, color, zSqrd * (3.0f - 2.0f * z)); // Fog
	

	//vec4 projected =   vec4(0.0, 0.0, dep, 1.0) * inverse(gProjection);
	//WorldPosOut.xyz = p /wc;
	WorldPosOut.xyz = p;
	//WorldPosOut.xyz = vec3( vec4(p,1.0) * VP );
	WorldPosOut.w = dep;
	//WorldPosOut.w = projected.z;
	
	//DiffuseOut = applyFog(color.xyz,t);
	DiffuseOut = color.xyz;
	//DiffuseOut = ro.xyz;
	NormalOut = normal;
	//NormalOut = ro.xyz;

}