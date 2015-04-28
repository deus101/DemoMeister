#pragma once
#include "lightNode.h"
//#include "math3d.h"
namespace NS_SG
{
	class pointLightNode : public lightNode
	{
	public:
		pointLightNode(std::string name, NS_VEC::VEC3 _color, float _AmbientIntensity, float _DiffuseIntensity, float _Constant, float _Linear, float _Exp) : lightNode(name, _color, _AmbientIntensity, _DiffuseIntensity), Constant(_Constant), Linear(_Linear), Exp(_Exp){}
		virtual NodeType getType() { return NODE_LIGHT_POINT; }

	private:
		float Constant;
		float Linear;
		float Exp;

	};

}