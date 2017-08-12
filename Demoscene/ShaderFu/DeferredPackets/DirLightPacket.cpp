

#include <limits.h>
#include <string.h>

#include "DirLightPacket.h"
using namespace NS_EFF;

DirLightPacket::DirLightPacket()
{

}

bool DirLightPacket::Init()
{
	if (!renderPacket::Init()) {
		return false;
	}
	
	if (!LoadShader(GL_VERTEX_SHADER, "shaders/IdentityPacket.vert")) {
		return false;
	}

	if (!LoadShader(GL_FRAGMENT_SHADER, "shaders/dir_light_pass.fs")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}

	m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
	m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
	m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
	m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
	
	if (m_dirLightLocation.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.Color == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.Direction == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return lightPacket::Init();
}



void DirLightPacket::SetDirectionalLight(const DirectionalLight& Light)
{

	glUniform3f(m_dirLightLocation.Color, Light.Color.X, Light.Color.Y, Light.Color.Z);
	glUniform1f(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
	NS_VEC::VEC3 Direction = Light.Direction;
	//Direction.NormIt();
	glUniform3f(m_dirLightLocation.Direction, Direction.X, Direction.Y, Direction.Z);
	glUniform1f(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
}


