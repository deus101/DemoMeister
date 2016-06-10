#ifndef LIGHTPACKET_HPP
#define	LIGHTPACKET_HPP

#include <string>

#include "renderPacket.h"
#include "../util.h"
namespace NS_EFF{
	class lightPacket : public renderPacket {
	public:

		lightPacket();

		virtual bool Init();

		void SetWVP(const M3DMatrix44f& WVP);
		
		void SetWorldMatrix(const M3DMatrix44f& W);

		void SetViewMatrix(const M3DMatrix44f& V);

		void SetProjectionMatrix(const M3DMatrix44f& P);

		void SetPositionTextureUnit(unsigned int TextureUnit);
		void SetColorTextureUnit(unsigned int TextureUnit);
		void SetNormalTextureUnit(unsigned int TextureUnit);
		void SetAoTextureUnit(unsigned int TextureUnit);
		
		//void SetSSAOTextureUnit(unsigned int TextureUnit);

		void SetEyeWorldPos(const NS_VEC::VEC3& EyeWorldPos);
		void SetMatSpecularIntensity(float Intensity);
		void SetMatSpecularPower(float Power);
		void SetScreenSize(unsigned int Width, unsigned int Height);

	private:

		GLuint m_WVPLocation;
		GLuint m_ProjectionLocation;
		GLuint m_ViewLocation;
		GLuint m_WorldMatrixLocation;

		GLuint m_posTextureUnitLocation;
		GLuint m_normalTextureUnitLocation;
		GLuint m_colorTextureUnitLocation;
		GLuint m_AoTextureUnitLocation;

		GLuint m_eyeWorldPosLocation;
		GLuint m_matSpecularIntensityLocation;
		GLuint m_matSpecularPowerLocation;
		GLuint m_screenSizeLocation;
	};

}

#endif