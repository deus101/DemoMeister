/*

Copyright 2011 Etay Meiri

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
	gl::UniformMatrix4fv(m_WVPLocation, 1, gl::TRUE_, WVP);
}


void lightPacket::SetPositionTextureUnit(unsigned int TextureUnit)
{
	gl::Uniform1i(m_posTextureUnitLocation, TextureUnit);
}


void lightPacket::SetColorTextureUnit(unsigned int TextureUnit)
{
	
	gl::Uniform1i(m_colorTextureUnitLocation, TextureUnit);
}


void lightPacket::SetNormalTextureUnit(unsigned int TextureUnit)
{
	gl::Uniform1i(m_normalTextureUnitLocation, TextureUnit);
}


void lightPacket::SetEyeWorldPos(const NS_VEC::VEC3& EyePos)
{
	gl::Uniform3f(m_eyeWorldPosLocation, EyePos.X, EyePos.Y, EyePos.Z);
}


void lightPacket::SetScreenSize(unsigned int Width, unsigned int Height)
{
	gl::Uniform2f(m_screenSizeLocation, (float)Width, (float)Height);
}