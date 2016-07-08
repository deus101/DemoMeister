#version 330

smooth in vec2 uv;

layout (location = 0) out vec4 WorldPosOut;   
layout (location = 1) out vec3 DiffuseOut;     
layout (location = 2) out vec3 NormalOut;  


uniform mat4 gView;

//uniform sampler2D gPositionMap;
//uniform sampler2D gColorMap;
//uniform sampler2D gNormalMap;


uniform vec2 gScreenSize;
uniform vec3 gEyeWorldPos;

const float focalLenght = 1.67f; 
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
	t = 0.0f;
	for(i = 0; i < raySteps; ++i)
	{
		float dist = distScene(orig + dir * t);


		if(dist < rayEpsilon * t * 2.0f || t > FAR)
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


float infPlane(vec3 ro, vec3 rd, vec3 n, vec3 o)
{
	return dot(o - ro, n) / dot(rd, n);
}


void main()
{
	vec3 ro = gView[3].xyz;
	
	vec4 color = vec4(1.0); 
	
	vec4 skyColor = vec4(0.54 ,0.824,1.0,1.0);
	vec3 normal = vec3(0.0);

	vec3 viewRight = gView[0].xyz;
	vec3 viewUp = gView[1].xyz;
	vec3 viewForward = gView[2].xyz;
	float aspectRatio = 16.0 / 9.0;
	vec3 rd = normalize(viewForward * focalLenght + viewRight * uv.x * aspectRatio + viewUp * uv.y);


	float t0;
	int i;

	pewpew(ro, rd, i, t0);
	vec3 floorNormal = vec3(0, 1, 0);


	float t1 = infPlane(ro, rd, floorNormal, vec3(0, -0.5, 0));
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
		dep = distance(ro, p);
		z = mapTo(t, NEAR, FAR, 1, 0);

	}
	else if(i < raySteps && t0 >= NEAR  && t0 <= FAR) 
	{
		t = t0;
		p = ro + rd * t0;
		normal = getNormal(p);
		dep = distance(ro, p);
		z = mapTo(t, NEAR, FAR, 1, 0);
	}
	else
	{
		color = skyColor;
	}

	p.z = z;
	WorldPosOut = vec4(p,dep);
	DiffuseOut = color.xyz;
	NormalOut = normal;
}