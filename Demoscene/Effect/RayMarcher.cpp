#include "RayMarcher.h"
#include "../util.h"
#include <limits.h>

using namespace NS_EFF;


RayMarcher::RayMarcher()
{
}

bool RayMarcher::Init()
{
	if (!renderPacket::Init()) {
		return false;
	}

	if (!LoadShader(GL_VERTEX_SHADER, "Shaders/RayMarcher_vert.glsl")) {
		return false;
	}


	if (!LoadShader(GL_FRAGMENT_SHADER, "Shaders/RayMarcher_Frag.glsl")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}

	m_WVPLocation = GetUniformLocation("gWVP");
	//m_WorldMatrixLocation = GetUniformLocation("gWorld");
	m_ViewLocation = GetUniformLocation("gView");
	m_ProjectionLocation = GetUniformLocation("gProjection");
	m_ScreenSizeLoc = GetUniformLocation("gScreenSize");
	//m_colorTextureUnitLocation = GetUniformLocation("gColorMap");

	m_EyeWorldLoc = GetUniformLocation("gEyeWorldPos");


	if (//m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_ViewLocation == INVALID_UNIFORM_LOCATION ||
		m_EyeWorldLoc == INVALID_UNIFORM_LOCATION ||
		m_ScreenSizeLoc == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}



void  RayMarcher::SetViewMatrix(const M3DMatrix44f& V)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ViewLocation, 1, GL_FALSE, V);
}

void  RayMarcher::SetScreenSize(unsigned int Width, unsigned int Height)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniform2f(m_ScreenSizeLoc, (float)Width, (float)Height);
}
void RayMarcher::SetEyeWorldPos(const NS_VEC::VEC3& EyePos)
{
	glUniform3f(m_EyeWorldLoc, EyePos.X, EyePos.Y, EyePos.Z);
}



void  RayMarcher::SetProjectionMatrix(const M3DMatrix44f& P)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ProjectionLocation, 1, GL_FALSE, P);
}

//ugh why dont I virtualize these in the base class
void RayMarcher::SetWVP(const M3DMatrix44f& WVP)
{
//glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, WVP);

glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, WVP);
}

/*
void RayMarcher::SetWorldMatrix(const M3DMatrix44f& W)
{
//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_FALSE, W);
}



*/
void RayMarcher::SetColorTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_colorTextureUnitLocation, TextureUnit);
}
