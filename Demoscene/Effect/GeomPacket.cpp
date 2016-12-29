

#include "GeomPacket.h"
#include "../util.h"
#include <limits.h>
#include "../Rendrer/context.h"
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
	m_colorTextureUnitLocation = GetUniformLocation("gColorMap");

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
		m_colorTextureUnitLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}

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

void GeomPacket::SetColorTextureUnit(unsigned int TextureUnit)
{
	
	glUniform1i(m_colorTextureUnitLocation, TextureUnit);
}
