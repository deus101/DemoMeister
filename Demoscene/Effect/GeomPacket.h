#ifndef GEOMPACKET_HPP
#define GEOMPACKET_HPP

#include "renderPacket.h"

//Jeg tror jeg overforbruker
namespace NS_EFF{

	class GeomPacket : public renderPacket {
	public:

		GeomPacket();

		virtual bool Init();

		void SetWVP(const M3DMatrix44f& WVP);
		void SetWorldMatrix(const M3DMatrix44f& W);

		void SetViewMatrix(const M3DMatrix44f& V);

		void SetProjectionMatrix(const M3DMatrix44f& P);


		void SetColorTextureUnit(unsigned int TextureUnit);



	private:


		GLuint m_WVPLocation;
		GLuint m_ProjectionLocation;
		GLuint m_ViewLocation;
		GLuint m_WorldMatrixLocation;
		
		
		GLuint v4_FarNearLocation;
		GLuint m_colorTextureUnitLocation;
	};
}

#endif