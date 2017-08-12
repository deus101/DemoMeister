

#include "GeomPacket.h"

//#include "../util.h"

#include <limits.h>
#include "../../Rendrer/context.h"
using namespace NS_EFF;


GeomPacket::GeomPacket()
{
}

bool GeomPacket::Init()
{
	if (!renderPacket::Init()) {
		return false;
	}

	if (!LoadShader(GL_VERTEX_SHADER, "Shaders/geometry_pass.vs")) {
		return false;
	}


	if (!LoadShader(GL_FRAGMENT_SHADER, "Shaders/geometry_pass.fs")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}

	m_WVPLocation = GetUniformLocation("gWVP");
	m_WorldMatrixLocation = GetUniformLocation("gWorld");
	m_ViewLocation = GetUniformLocation("gView");
	m_ProjectionLocation = GetUniformLocation("gProjection");
	m_diffuseTextureUnitLocation = GetUniformLocation("A_DiffuseMap");
	m_MaterialMapTextureUnitLocation = GetUniformLocation("MaterialMap");
	m_MaterialCountUnitLocation = GetUniformLocation("MaterialMap");
	//NS_ENG::Material::

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
		m_MaterialMapTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
		m_diffuseTextureUnitLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}

/*
//ugh why dont I virtualize these in the base class
void GeomPacket::SetWVP(const M3DMatrix44f& WVP)
{
	//glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, WVP);

	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, WVP);
}


void GeomPacket::SetWorldMatrix(const M3DMatrix44f& W)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_FALSE, W);
}




void  GeomPacket::SetViewMatrix(const M3DMatrix44f& V)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ViewLocation, 1, GL_FALSE, V);


}

void  GeomPacket::SetProjectionMatrix(const M3DMatrix44f& P)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ProjectionLocation, 1, GL_FALSE, P);
}


//void GeomPacket::SetDiffuseTextureUnit(unsigned int TextureUnit)
void GeomPacket::SetDiffuseTextureUnit(GLenum TextureUnit)
{
	GLint ShaderProg;
	glGetIntegerv(GL_CURRENT_PROGRAM, &ShaderProg);

	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_diffuseTextureUnitLocation, SamplerID);
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::DiffuseMap_UNIT] = TextureUnit;
	std::cout << "Diffuse Map Uniform Location is " << m_diffuseTextureUnitLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: "<< SamplerID <<std::endl;
	//typeid(TextureUnit).name()
}

//should be inherited shared with both lightpacket and Raymarcher
void GeomPacket::SetMaterialMapUnit(GLenum TextureUnit)
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

void GeomPacket::SetMaterialsCount(unsigned int MatCount)
{
	//glUniform2f(m_screenSizeLocation, (float)Width, (float)Height);

	//Material::GenerateMaterialMap


	glUniform1i(m_MaterialCountUnitLocation, MatCount);

	std::cout << "Unifor Location for MatCount is " << m_MaterialCountUnitLocation << " Value is " << MatCount << std::endl;
}
*/