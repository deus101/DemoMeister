#include "DeferredPipeMother.h"

using namespace NS_EFF;

DeferredPipeMother::DeferredPipeMother()
{
}


DeferredPipeMother::~DeferredPipeMother()
{
}


bool DeferredPipeMother::Init()
{


	return true;
}


void DeferredPipeMother::SetWVP(const M3DMatrix44f& WVP)
{
	//glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, WVP);

	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, WVP);
}


void DeferredPipeMother::SetWorldMatrix(const M3DMatrix44f& W)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_FALSE, W);
}




void  DeferredPipeMother::SetViewMatrix(const M3DMatrix44f& V)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ViewLocation, 1, GL_FALSE, V);


}

void  DeferredPipeMother::SetProjectionMatrix(const M3DMatrix44f& P)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ProjectionLocation, 1, GL_FALSE, P);
}

void DeferredPipeMother::SetEyeWorldPos(const NS_VEC::VEC3& EyePos)
{
	glUniform3f(m_eyeWorldPosLocation, EyePos.X, EyePos.Y, EyePos.Z);
}


void DeferredPipeMother::SetScreenSize(unsigned int Width, unsigned int Height)
{
	glUniform2f(m_screenSizeLocation, (float)Width, (float)Height);
}



//void GeomPacket::SetDiffuseTextureUnit(unsigned int TextureUnit)
void DeferredPipeMother::SetDiffuseTextureUnit(GLenum TextureUnit)
{
	GLint ShaderProg;
	glGetIntegerv(GL_CURRENT_PROGRAM, &ShaderProg);

	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_diffuseTextureUnitLocation, SamplerID);
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::DiffuseMap_UNIT] = TextureUnit;
	std::cout << "Diffuse Map Uniform Location is " << m_diffuseTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
	//typeid(TextureUnit).name()
}



void DeferredPipeMother::SetPositionTextureUnit(GLenum TextureUnit)
{
	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_posTextureUnitLocation, SamplerID);

	std::cout << "Light postex Uniform Location is " << m_posTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;

	this->m_StageParamPtr->TextureUnits[TypeOfTexture::GBuffer_WorldPos_UNIT] = TextureUnit;
}


void DeferredPipeMother::SetAbedoTextureUnit(GLenum TextureUnit)
{
	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_AbedoTextureUnitLocation, SamplerID);
	// rename gl id 
	std::cout << "Light colTex Uniform Location is " << m_AbedoTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::GBuffer_Albedo_UNIT] = TextureUnit;
}


void DeferredPipeMother::SetNormalTextureUnit(GLenum TextureUnit)
{
	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_normalTextureUnitLocation, SamplerID);

	std::cout << "Light normal tex Uniform Location is " << m_normalTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::GBuffer_Normal_UNIT] = TextureUnit;
}

void DeferredPipeMother::SetUvTextureUnit(GLenum TextureUnit)
{
	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_UvTextureUnitLocation, SamplerID);
	std::cout << "Light Uv Screen tex Uniform Location is " << m_UvTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::GBuffer_UV_UNIT] = TextureUnit;
}

void DeferredPipeMother::SetAoTextureUnit(GLenum TextureUnit)
{
	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_AoTextureUnitLocation, SamplerID);

	std::cout << "Light AO Uniform Location is " << m_AoTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::AOBuffer_AO_UNIT] = TextureUnit;
}




//should be inherited shared with both lightpacket and Raymarcher
void DeferredPipeMother::SetMaterialMapUnit(GLenum TextureUnit)
{

	//glUniform2f(m_screenSizeLocation, (float)Width, (float)Height);

	//Material::GenerateMaterialMap

	GLint ShaderProg;
	glGetIntegerv(GL_CURRENT_PROGRAM, &ShaderProg);

	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_MaterialMapTextureUnitLocation, SamplerID);
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::MaterialMap_UNIT] = TextureUnit;
	std::cout << "Material Map  Uniform Location: " << m_MaterialMapTextureUnitLocation << " Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
}

void DeferredPipeMother::SetMaterialsCount(unsigned int MatCount)
{
	//glUniform2f(m_screenSizeLocation, (float)Width, (float)Height);

	//Material::GenerateMaterialMap


	glUniform1i(m_MaterialCountUnitLocation, MatCount);

	std::cout << "Unifor Location for MatCount is " << m_MaterialCountUnitLocation << " Value is " << MatCount << std::endl;
}