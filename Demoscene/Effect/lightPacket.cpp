
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
	m_colorTextureUnitLocation = GetUniformLocation("gColorMap");
	m_normalTextureUnitLocation = GetUniformLocation("gNormalMap");
	m_UvTextureUnitLocation = GetUniformLocation("gUvMap");
	m_AoTextureUnitLocation = GetUniformLocation("gAoPass");

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

void lightPacket::SetPositionTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_posTextureUnitLocation, TextureUnit);
	std::cout << "Light postex Uniform Location is " << m_posTextureUnitLocation << " Sampler Id is " << TextureUnit << std::endl;

}


void lightPacket::SetColorTextureUnit(unsigned int TextureUnit)
{
	
	glUniform1i(m_colorTextureUnitLocation, TextureUnit);
	std::cout << "Light colTex Uniform Location is " << m_colorTextureUnitLocation << " Sampler Id is " << TextureUnit << std::endl;

}


void lightPacket::SetNormalTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_normalTextureUnitLocation, TextureUnit);
	std::cout << "Light normal tex Uniform Location is " << m_normalTextureUnitLocation << " Sampler Id is " << TextureUnit << std::endl;

}

void lightPacket::SetUvTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_UvTextureUnitLocation, TextureUnit);
	std::cout << "Light normal tex Uniform Location is " << m_normalTextureUnitLocation << " Sampler Id is " << TextureUnit << std::endl;

}

void lightPacket::SetAoTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_AoTextureUnitLocation, TextureUnit);

	std::cout << "Light AO Uniform Location is " << m_AoTextureUnitLocation << " Sampler Id is " << TextureUnit << std::endl;

}

void lightPacket::SetEyeWorldPos(const NS_VEC::VEC3& EyePos)
{
	glUniform3f(m_eyeWorldPosLocation, EyePos.X, EyePos.Y, EyePos.Z);
}


void lightPacket::SetScreenSize(unsigned int Width, unsigned int Height)
{
	glUniform2f(m_screenSizeLocation, (float)Width, (float)Height);
}