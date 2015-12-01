
#ifndef DS_POINT_LIGHT_PASS_TECH_H
#define	DS_POINT_LIGHT_PASS_TECH_H

#include "lightPacket.h"
//#include "lights_common.h"
namespace NS_EFF{

	class PointLightPacket : public lightPacket
	{
	public:

		PointLightPacket();

		bool Init();

		void SetPointLight(const PointLight& Lights);

	private:

		struct {
			GLuint Color;
			GLuint AmbientIntensity;
			GLuint DiffuseIntensity;
			GLuint Position;
			struct {
				GLuint Constant;
				GLuint Linear;
				GLuint Exp;
			} Atten;
		} m_pointLightLocation;
	};

}
#endif