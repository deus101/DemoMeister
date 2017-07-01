#pragma once
#include "lightNode.h"
#include "../Effect/DirLightPacket.h"
namespace NS_SG
{
	class dirLightNode : public lightNode
	{
	public:
		dirLightNode(std::string name, NS_VEC::VEC3 _color, float _AmbientIntensity, float _DiffuseIntensity, NS_EFF::DirLightPacket *_LightMagic) : lightNode(name, _color, _AmbientIntensity, _DiffuseIntensity), LightMagic(_LightMagic){}
		virtual NodeType getType() { return NODE_LIGHT_DIR; }
		
		DirectionalLight GetDirLight()
		{
			
			M3DMatrix44f world;
			getAbsoluteTransform(world);

			NS_VEC::VEC3 dir(-0.6, 2.8, 2.2);
			//NS_VEC::VEC3 dir(-0.5f, -0.5f, -0.5f);
			dir.NormIt();

			BaseLight s_bl = GetLight();
			DirectionalLight s_dl;
			s_dl.Color = s_bl.Color;
			s_dl.AmbientIntensity = s_bl.AmbientIntensity;
			s_dl.DiffuseIntensity = s_bl.DiffuseIntensity;
			s_dl.Direction = dir;
			
			return s_dl;

		}


		NS_EFF::DirLightPacket *LightMagic;




	};

}