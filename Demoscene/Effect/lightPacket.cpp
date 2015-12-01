
#include <limits.h>
#include <string.h>

#include "lightPacket.h"

using namespace NS_EFF;
lightPacket::lightPacket()
{
}

bool lightPacket::Init()
{
	m_WVPLocation = GetUniformLocation("gWVP");
	m_posTextureUnitLocation = GetUniformLocation("gPositionMap");
	m_colorTextureUnitLocation = GetUniformLocation("gColorMap");
	m_normalTextureUnitLocation = GetUniformLocation("gNormalMap");
	m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
	m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
	m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");
	m_screenSizeLocation = GetUniformLocation("gScreenSize");
	
	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
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
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, WVP);
}


void lightPacket::SetPositionTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_posTextureUnitLocation, TextureUnit);
}


void lightPacket::SetColorTextureUnit(unsigned int TextureUnit)
{
	
	glUniform1i(m_colorTextureUnitLocation, TextureUnit);
}


void lightPacket::SetNormalTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_normalTextureUnitLocation, TextureUnit);
}


void lightPacket::SetEyeWorldPos(const NS_VEC::VEC3& EyePos)
{
	glUniform3f(m_eyeWorldPosLocation, EyePos.X, EyePos.Y, EyePos.Z);
}


void lightPacket::SetScreenSize(unsigned int Width, unsigned int Height)
{
	glUniform2f(m_screenSizeLocation, (float)Width, (float)Height);
}