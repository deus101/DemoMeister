#pragma once
#include "renderPacket.h"

namespace NS_EFF{


	class HeightMapPacket : public renderPacket
	{
		public:
			HeightMapPacket();

			virtual bool Init();

			void SetWVP(const M3DMatrix44f& WVP);
			void SetWorldMatrix(const M3DMatrix44f& W);
			void SetColorTextureUnit(unsigned int TextureUnit);
		private:

			GLuint m_WVPLocation;
			GLuint m_WorldMatrixLocation;
			GLuint m_colorTextureUnitLocation;
		
	
	};
}





