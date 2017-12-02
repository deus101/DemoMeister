
#include <limits.h>
#include <string.h>

#include "lightPacket.h"

using namespace NS_EFF;
lightPacket::lightPacket()
{
}

bool lightPacket::Init()
{	

	//shouldnt i  initialize these with L for light, g for geometry etc?
	m_WVPLocation = GetUniformLocation("gWVP");

	m_WorldMatrixLocation = GetUniformLocation("commonWorldMatrix");
	m_ViewLocation = GetUniformLocation("commonViewMatrix");
	m_ProjectionLocation = GetUniformLocation("commonProjectionMatrix");

	m_posTextureUnitLocation = GetUniformLocation("gbPositionMap");
	m_AbedoTextureUnitLocation = GetUniformLocation("gbAbedoMap");
	m_normalTextureUnitLocation = GetUniformLocation("gbNormalMap");
	m_UvTextureUnitLocation = GetUniformLocation("gbUvMap");
	m_AoTextureUnitLocation = GetUniformLocation("aobAoMap");

	m_baseMaterialMapTextureUnitLocation = GetUniformLocation("baseMaterialMap");
	m_MaterialCountUnitLocation = GetUniformLocation("baseMaterialCount");
	m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
	//m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
	//m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");
	m_screenSizeLocation = GetUniformLocation("gScreenSize");
	
	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
		m_ViewLocation == INVALID_UNIFORM_LOCATION ||
		m_ProjectionLocation == INVALID_UNIFORM_LOCATION ||
		m_posTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
		m_AbedoTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
		m_normalTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
		m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
		//m_matSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
		//m_matSpecularPowerLocation == INVALID_UNIFORM_LOCATION ||
		m_screenSizeLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}

