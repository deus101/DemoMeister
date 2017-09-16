void LookUpMaterial(float ID, out vec4 MatDiffuse, out vec4 MatSpecular)
{

	float PZ_MM_Y = 1 / textureSize(MaterialMap, 0).y;
	float fixID = (ID * PZ_MM_Y) * 0.5;
	MatDiffuse = vec4(texture(MaterialMap, vec2(0, fixID)).xyz, 1.0);
	MatSpecular = vec4(texture(MaterialMap, vec2(1, fixID)).xyz, 1.0);


}
