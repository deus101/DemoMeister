
#ifndef NULL_PACKET_HPP
#define	NULL_PACKET_HPP

#include "renderPacket.h"

namespace NS_EFF{
	class NullPacket : public renderPacket {
	public:

		NullPacket();

		virtual bool Init();

		void SetWVP(const M3DMatrix44f& WVP);
		void SetWorldMatrix(const M3DMatrix44f& W);

		void SetViewMatrix(const M3DMatrix44f& V);

		void SetProjectionMatrix(const M3DMatrix44f& P);
	private:

		GLuint m_WVPLocation;
		GLuint m_ProjectionLocation;
		GLuint m_ViewLocation;
		GLuint m_WorldMatrixLocation;

	};

}
#endif