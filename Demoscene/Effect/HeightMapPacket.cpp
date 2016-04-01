#include "HeightMapPacket.h"

using namespace NS_EFF;
HeightMapPacket::HeightMapPacket()
{
}


bool HeightMapPacket::Init()
{
	if (!renderPacket::Init()) {
		return false;
	}

	if (!LoadShader(GL_VERTEX_SHADER, "Shaders/geometry_grid_pass.vs")) {
		return false;
	}

	if (!LoadShader(GL_GEOMETRY_SHADER, "Shaders/geometry_grid_pass.gs")) {
		return false;
	}

	if (!LoadShader(GL_FRAGMENT_SHADER, "Shaders/geometry_grid_pass.fs")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}

	m_WorldMatrixLocation = GetUniformLocation("gWorld");
	m_WVPLocation = GetUniformLocation("gWVP");
	f_halfSizLocation = GetUniformLocation("halfSize");
	//m_colorTextureUnitLocation = GetUniformLocation("gColorMap");

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION || 
		f_halfSizLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}

void HeightMapPacket::SetWVP(const M3DMatrix44f& WVP)
{
	//glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, WVP);

	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, WVP);
}


void HeightMapPacket::SetWorldMatrix(const M3DMatrix44f& W)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_FALSE, W);
}

void HeightMapPacket::SetHeightTextureUnit(unsigned int HeightUnit)
{
	glUniform1i(m_colorHeightUnitLocation, HeightUnit);
}
void HeightMapPacket::SetColorTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_colorTextureUnitLocation, TextureUnit);
}
void HeightMapPacket::SetHalfSize(float HalfSizeOrLoc)
{
	if (HalfSizeOrLoc == -1)
		glUniform1f(f_halfSizLocation, f_halfSize);
	else
		f_halfSize = HalfSizeOrLoc;
}