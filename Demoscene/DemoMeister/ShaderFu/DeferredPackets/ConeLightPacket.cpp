#include <limits.h>
#include <string.h>

#include "ConeLightPacket.h"

using namespace NS_EFF;

SpotLightPacket::SpotLightPacket()
{
}

bool SpotLightPacket::Init()
{
	if (!renderPacket::Init()) {
		return false;
	}

	if (!LoadShader(GL_VERTEX_SHADER, "shaders/light_pass.vs")) {
		return false;
	}


	if (!LoadShader(GL_FRAGMENT_SHADER, "shaders/point_light_pass.fs")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}

	m_spotLightLocation.Color = GetUniformLocation("gPointLight.Base.Color");
	m_spotLightLocation.AmbientIntensity = GetUniformLocation("gPointLight.Base.AmbientIntensity");
	m_spotLightLocation.Position = GetUniformLocation("gPointLight.Position");
	m_spotLightLocation.DiffuseIntensity = GetUniformLocation("gPointLight.Base.DiffuseIntensity");
	m_spotLightLocation.Atten.Constant = GetUniformLocation("gPointLight.Atten.Constant");
	m_spotLightLocation.Atten.Linear = GetUniformLocation("gPointLight.Atten.Linear");
	m_spotLightLocation.Atten.Exp = GetUniformLocation("gPointLight.Atten.Exp");

	if (m_spotLightLocation.Color == INVALID_UNIFORM_LOCATION ||
		m_spotLightLocation.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
		m_spotLightLocation.Position == INVALID_UNIFORM_LOCATION ||
		m_spotLightLocation.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
		m_spotLightLocation.Atten.Constant == INVALID_UNIFORM_LOCATION ||
		m_spotLightLocation.Atten.Linear == INVALID_UNIFORM_LOCATION ||
		m_spotLightLocation.Atten.Exp == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return lightPacket::Init();
}


void SpotLightPacket::SetSpotLight(const SpotLight& Light)
{
	glUniform3f(m_spotLightLocation.Color, Light.Color.X, Light.Color.Y, Light.Color.Z);
	glUniform1f(m_spotLightLocation.AmbientIntensity, Light.AmbientIntensity);
	glUniform1f(m_spotLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
	glUniform3f(m_spotLightLocation.Position, Light.Position.X, Light.Position.Y, Light.Position.Z);
	glUniform1f(m_spotLightLocation.Atten.Constant, Light.Attenuation.Constant);
	glUniform1f(m_spotLightLocation.Atten.Linear, Light.Attenuation.Linear);
	glUniform1f(m_spotLightLocation.Atten.Exp, Light.Attenuation.Exp);
}
