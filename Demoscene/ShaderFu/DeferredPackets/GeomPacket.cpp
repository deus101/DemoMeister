

#include "GeomPacket.h"

//#include "../util.h"

#include <limits.h>
#include "../../Rendrer/context.h"
using namespace NS_EFF;


GeomPacket::GeomPacket()
{
	//renderPacket::EffectName =
	renderPacket::EffectName = "GeomPacket";
	renderPacket::EffectType = "GeomPacket";

}

bool GeomPacket::Init()
{
	if (!renderPacket::Init()) {
		return false;
	}

	if (!DeferredPipeMother::Init()) {
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
	m_WorldMatrixLocation = GetUniformLocation("commonWorldMatrix");
	m_ViewLocation = GetUniformLocation("commonViewMatrix");
	m_ProjectionLocation = GetUniformLocation("commonProjectionMatrix");


	m_diffuseTextureUnitLocation = GetUniformLocation("geomDiffuseSkin0");
	m_DeferredDiffuseTextureUnitLocation = GetUniformLocation("baseArrayDiffuse0");

	m_baseMaterialMapTextureUnitLocation = GetUniformLocation("basebaseMaterialMap");
	m_MaterialCountUnitLocation = GetUniformLocation("baseMaterialCount");
	//NS_ENG::Material::

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
		m_baseMaterialMapTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
		m_diffuseTextureUnitLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}

