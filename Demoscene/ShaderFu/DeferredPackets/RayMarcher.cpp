#include "RayMarcher.h"
#include "../../util.h"
#include <limits.h>

using namespace NS_EFF;


RayMarcher::RayMarcher()
{
	renderPacket::EffectName = "RayMarcher";
	renderPacket::EffectType = "RayMarcher";
}

bool RayMarcher::Init()
{
	if (!renderPacket::Init()) {
		return false;
	}
	
	if (!DeferredPipeMother::Init()) {
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
	//m_WorldMatrixLocation = GetUniformLocation("commonWorldMatrix");
	m_ViewLocation = GetUniformLocation("commonViewMatrix");
	m_ProjectionLocation = GetUniformLocation("commonProjectionMatrix");
	m_screenSizeLocation = GetUniformLocation("gScreenSize");
	//m_colorTextureUnitLocation = GetUniformLocation("gColorMap");




	
	m_DeferredDiffuseTextureUnitLocation = GetUniformLocation("baseArrayDiffuse_0");

	
	m_baseMaterialMapTextureUnitLocation = GetUniformLocation("baseMaterialMap");
	m_MaterialCountUnitLocation = GetUniformLocation("MaterialCount");
	//m_diffuseTextureUnitLocation


	m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");


	if (//m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_ViewLocation == INVALID_UNIFORM_LOCATION ||
		m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
		m_baseMaterialMapTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
		m_screenSizeLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}

