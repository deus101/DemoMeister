

#include "GeomPacket.h"
#include "../util.h"
#include <limits.h>

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
	m_colorTextureUnitLocation = GetUniformLocation("gColorMap");

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
		m_colorTextureUnitLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}


void GeomPacket::SetWVP(const M3DMatrix44f& WVP)
{
	
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, WVP);
}


void GeomPacket::SetWorldMatrix(const M3DMatrix44f& W)
{
	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);
}


void GeomPacket::SetColorTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_colorTextureUnitLocation, TextureUnit);
}
