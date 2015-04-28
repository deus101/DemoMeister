#pragma once
#include "lightNode.h"
//#include "math3d.h"
namespace NS_SG
{
	class dirLightNode : public lightNode
	{
	public:
		dirLightNode(std::string name, NS_VEC::VEC3 _color, float _AmbientIntensity, float _DiffuseIntensity) : lightNode(name ,_color, _AmbientIntensity, _DiffuseIntensity){}
		virtual NodeType getType() { return NODE_LIGHT_DIR; }



	};

}