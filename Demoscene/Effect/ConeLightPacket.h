#ifndef CONELIGHTPACKET_HPP
#define CONELIGHTPACKET_HPP

#include "pointLightPacket.h"
namespace NS_EFF{

	class SpotLightPacket : public PointLightPacket
	{
	public:

		SpotLightPacket();

		bool Init();

		void SetSpotLight(const SpotLight& Lights);

	private:
		
		struct {
			GLuint Direction;
			GLuint Color;
			GLuint AmbientIntensity;
			GLuint DiffuseIntensity;
			GLuint Position;
			struct {
				GLuint Constant;
				GLuint Linear;
				GLuint Exp;
			} Atten;
		} m_spotLightLocation;
	
	};


}
#endif




