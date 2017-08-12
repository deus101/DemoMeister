

#include <limits.h>
#include <string.h>
#include "../../util.h"
#include "NullPacket.h"
using namespace NS_EFF;

NullPacket::NullPacket()
{
}

bool NullPacket::Init()
{
	if (!renderPacket::Init()) {
		return false;
	}

	if (!LoadShader(GL_VERTEX_SHADER, "shaders/null_technique.vs")) {
		return false;
	}

	if (!LoadShader(GL_FRAGMENT_SHADER, "shaders/null_technique.fs")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}

	m_WVPLocation = GetUniformLocation("gWVP");
	m_WorldMatrixLocation = GetUniformLocation("gWorld");
	m_ViewLocation = GetUniformLocation("gView");
	m_ProjectionLocation = GetUniformLocation("gProjection");

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_ViewLocation == INVALID_UNIFORM_LOCATION ||
			m_ProjectionLocation == INVALID_UNIFORM_LOCATION ||
			m_ProjectionLocation == INVALID_UNIFORM_LOCATION){
		return false;
	}

	return true;
}

/*
void NullPacket::SetWVP(const M3DMatrix44f& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, WVP);

	//glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, (const GLfloat*)WVP);
}
void NullPacket::SetWorldMatrix(const M3DMatrix44f& W)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_FALSE, W);
}


void  NullPacket::SetViewMatrix(const M3DMatrix44f& V)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ViewLocation, 1, GL_FALSE, V);
}
void  NullPacket::SetProjectionMatrix(const M3DMatrix44f& P)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ProjectionLocation, 1, GL_FALSE, P);
}
*/