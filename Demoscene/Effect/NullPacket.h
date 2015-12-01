
#ifndef NULL_PACKET_HPP
#define	NULL_PACKET_HPP

#include "renderPacket.h"

namespace NS_EFF{
	class NullPacket : public renderPacket {
	public:

		NullPacket();

		virtual bool Init();

		void SetWVP(const M3DMatrix44f& WVP);

	private:

		GLuint m_WVPLocation;
	};

}
#endif