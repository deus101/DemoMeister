#pragma once
#include "node.h"
//#include "math3d.h"
namespace NS_SG
{
	class lightNode : public node
	{
	public:
		lightNode(std::string name, NS_VEC::VEC3 _color, float _AmbientIntensity, float _DiffuseIntensity) : node(name), Color(_color), AmbientIntensity(_AmbientIntensity), DiffuseIntensity(_DiffuseIntensity){}
		//virtual NodeType getType() { return NODE_LIGHT_DIR; }
		
		
		virtual BaseLight GetLight() {
			BaseLight s_BL;
			s_BL.Color = this->Color;
			s_BL.AmbientIntensity = this->AmbientIntensity;
			s_BL.DiffuseIntensity = this->DiffuseIntensity;
			return s_BL;
		}

	private:
		NS_VEC::VEC3 Color;
		float AmbientIntensity;
		float DiffuseIntensity;

	};

}