#pragma once
#include "lightNode.h"
#include "../Effect/PointLightPacket.h"
#include "../Effect/NullPacket.h"
//#include "math3d.h"
namespace NS_SG
{
	class pointLightNode : public lightNode
	{
	public:
		pointLightNode(std::string name, NS_VEC::VEC3 _color, 
			float _AmbientIntensity, float _DiffuseIntensity, float _Constant, float _Linear, float _Exp,
			NS_EFF::PointLightPacket *_LightMagic, NS_EFF::NullPacket *_NullMagic) : 
			lightNode(name, _color, _AmbientIntensity, _DiffuseIntensity), Constant(_Constant), Linear(_Linear), Exp(_Exp),
			LightMagic(_LightMagic), NullMagic(_NullMagic)
			{}
		virtual NodeType getType() { return NODE_LIGHT_POINT; }

		
		PointLight GetPointLight()  {
			M3DMatrix44f world;
			
			getAbsoluteTransform(world);
			BaseLight s_bl = GetLight();
			PointLight s_pl;
			s_pl.Position = NS_VEC::VEC3(world[12], world[13], world[14]);
			s_pl.Color = s_bl.Color;
			s_pl.AmbientIntensity = s_bl.AmbientIntensity;
			s_pl.DiffuseIntensity = s_bl.DiffuseIntensity;

			s_pl.Attenuation.Constant = this->Constant;
			s_pl.Attenuation.Exp = this->Exp;
			s_pl.Attenuation.Linear = this->Linear;

			return s_pl;


		}
		

		NS_EFF::PointLightPacket *LightMagic;
		NS_EFF::NullPacket *NullMagic;
	private:
		float Constant;
		float Linear;
		float Exp;

	};

}