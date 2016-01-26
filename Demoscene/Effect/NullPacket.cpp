

#include <limits.h>
#include <string.h>
#include "../util.h"
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

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}


void NullPacket::SetWVP(const M3DMatrix44f& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, WVP);

	//glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, (const GLfloat*)WVP);
}

