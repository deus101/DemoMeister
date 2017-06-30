
#include <limits.h>
#include <string.h>

#include "lightPacket.h"

using namespace NS_EFF;
lightPacket::lightPacket()
{
}

bool lightPacket::Init()
{	

	//shouldnt i  initialize these with L for light, g for geometry etc?
	m_WVPLocation = GetUniformLocation("gWVP");

	m_WorldMatrixLocation = GetUniformLocation("gWorld");
	m_ViewLocation = GetUniformLocation("gView");
	m_ProjectionLocation = GetUniformLocation("gProjection");

	m_posTextureUnitLocation = GetUniformLocation("gPositionMap");
	m_colorTextureUnitLocation = GetUniformLocation("gAbedoMap");
	m_normalTextureUnitLocation = GetUniformLocation("gNormalMap");
	m_UvTextureUnitLocation = GetUniformLocation("gUvMap");
	m_AoTextureUnitLocation = GetUniformLocation("gAoPass");

	m_MaterialMapTextureUnitLocation = GetUniformLocation("MaterialMap");
	m_MaterialCountUnitLocation = GetUniformLocation("MaterialMap");
	m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
	m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
	m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");
	m_screenSizeLocation = GetUniformLocation("gScreenSize");
	
	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
		m_ViewLocation == INVALID_UNIFORM_LOCATION ||
		m_ProjectionLocation == INVALID_UNIFORM_LOCATION ||
		m_posTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
		m_colorTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
		m_normalTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
		m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
		m_matSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
		m_matSpecularPowerLocation == INVALID_UNIFORM_LOCATION ||
		m_screenSizeLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}


void lightPacket::SetWVP(const M3DMatrix44f& WVP)
{
	//glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, WVP);

	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, WVP);
}


void lightPacket::SetWorldMatrix(const M3DMatrix44f& W)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_FALSE, W);
}




void  lightPacket::SetViewMatrix(const M3DMatrix44f& V)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ViewLocation, 1, GL_FALSE, V);
}

void  lightPacket::SetProjectionMatrix(const M3DMatrix44f& P)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ProjectionLocation, 1, GL_FALSE, P);
}
//void lightPacket::SetPositionTextureUnit(unsigned int TextureUnit)
void lightPacket::SetPositionTextureUnit(GLenum TextureUnit)
{
	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_posTextureUnitLocation, SamplerID);

	std::cout << "Light postex Uniform Location is " << m_posTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;

	this->m_StageParamPtr->TextureUnits[TypeOfTexture::GBuffer_WorldPos_UNIT] = TextureUnit;
}


void lightPacket::SetColorTextureUnit(GLenum TextureUnit)
{
	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_colorTextureUnitLocation, SamplerID);

	std::cout << "Light colTex Uniform Location is " << m_colorTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::GBuffer_Albedo_UNIT] = TextureUnit;
}


void lightPacket::SetNormalTextureUnit(GLenum TextureUnit)
{
	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_normalTextureUnitLocation, SamplerID);

	std::cout << "Light normal tex Uniform Location is " << m_normalTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::GBuffer_Normal_UNIT] = TextureUnit;
}

void lightPacket::SetUvTextureUnit(GLenum TextureUnit)
{
	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_UvTextureUnitLocation, SamplerID);
	std::cout << "Light Uv Screen tex Uniform Location is " << m_UvTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::GBuffer_UV_UNIT] = TextureUnit;
}

void lightPacket::SetAoTextureUnit(GLenum TextureUnit)
{
	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_AoTextureUnitLocation, SamplerID);

	std::cout << "Light AO Uniform Location is " << m_AoTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::AOBuffer_AO_UNIT] = TextureUnit;
}

void lightPacket::SetEyeWorldPos(const NS_VEC::VEC3& EyePos)
{
	glUniform3f(m_eyeWorldPosLocation, EyePos.X, EyePos.Y, EyePos.Z);
}


void lightPacket::SetScreenSize(unsigned int Width, unsigned int Height)
{
	glUniform2f(m_screenSizeLocation, (float)Width, (float)Height);
}

//void lightPacket::SetMaterialMapUnit(unsigned int TextureUnit)
void lightPacket::SetMaterialMapUnit(GLenum TextureUnit)
{
	//glUniform2f(m_screenSizeLocation, (float)Width, (float)Height);

	//Material::GenerateMaterialMap
	int SamplerID = TextureUnit - GL_TEXTURE0;

	glUniform1i(m_MaterialMapTextureUnitLocation, SamplerID);
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::MaterialMap_UNIT] = TextureUnit;
	std::cout << "Material Map Uniform Location is " << m_MaterialMapTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
}

void lightPacket::SetMaterialsCount(GLenum NrMaterials)
{
	//glUniform2f(m_screenSizeLocation, (float)Width, (float)Height);

	//Material::GenerateMaterialMap


	glUniform1i(m_MaterialCountUnitLocation, NrMaterials);

	std::cout << "Unifor Location for MatCount is " << m_MaterialCountUnitLocation << " Value is " << NrMaterials << std::endl;
}