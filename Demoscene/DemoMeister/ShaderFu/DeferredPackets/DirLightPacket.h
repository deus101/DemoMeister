

#ifndef DIRLIGHTPACKET_HPP
#define	DIRLIGHTPACKET_HPP

#include "../renderPacket.h"
#include "../DeferredPipeMother.h"
#include "lightPacket.h"
//#include "lights_common.h"
namespace NS_EFF{

	class DirLightPacket : public lightPacket<DirLightPacket>{
	public:

		DirLightPacket();

		virtual bool Init();

		void SetDirectionalLight(const DirectionalLight& Light);

	private:

		struct {
			GLuint Color;
			GLuint AmbientIntensity;
			GLuint DiffuseIntensity;
			GLuint Direction;
		} m_dirLightLocation;
	};

}
#endif