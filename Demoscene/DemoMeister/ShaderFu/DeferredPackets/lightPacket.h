#ifndef LIGHTPACKET_HPP
#define	LIGHTPACKET_HPP
//I think this should be move out of the gbuffer
#include <string>

#include "../renderPacket.h"
#include "../DeferredPipeMother.h"
#include "../../util.h"

namespace NS_EFF {

	/*
	template <typename T>
	class lightPacket : public DeferredPipeMother<T> {
	*/

	class lightPacket : public DeferredPipeMother {
	public:

		lightPacket();

		virtual bool Init();

		/*
		void SetWVP(const M3DMatrix44f& WVP);

		void SetWorldMatrix(const M3DMatrix44f& W);

		void SetViewMatrix(const M3DMatrix44f& V);

		void SetProjectionMatrix(const M3DMatrix44f& P);

		void SetPositionTextureUnit(unsigned int TextureUnit);
		//void SetIdTextureUnit(unsigned int TextureUnit);
		void SetColorTextureUnit(unsigned int TextureUnit);
		void SetNormalTextureUnit(unsigned int TextureUnit);
		void SetUvTextureUnit(unsigned int TextureUnit);
		void SetAoTextureUnit(unsigned int TextureUnit);

		void SetMaterialMapUnit(unsigned int TextureUnit);
		void SetMaterialsCount(unsigned int MatCount);


		void SetPositionTextureUnit(GLenum TextureUnit);
		//void SetIdTextureUnit(unsigned int TextureUnit);
		void SetColorTextureUnit(GLenum TextureUnit);
		void SetNormalTextureUnit(GLenum TextureUnit);
		void SetUvTextureUnit(GLenum TextureUnit);
		void SetAoTextureUnit(GLenum TextureUnit);

		void SetMaterialMapUnit(GLenum TextureUnit);
		void SetMaterialsCount(GLenum MatCount);



		//void SetSSAOTextureUnit(unsigned int TextureUnit);

		void SetEyeWorldPos(const NS_VEC::VEC3& EyeWorldPos);

		void SetMatSpecularIntensity(float Intensity);
		void SetMatSpecularPower(float Power);
		void SetScreenSize(unsigned int Width, unsigned int Height);
		*/
	private:
		/*
		GLuint m_WVPLocation;
		GLuint m_ProjectionLocation;
		GLuint m_ViewLocation;
		GLuint m_WorldMatrixLocation;

		GLuint m_posTextureUnitLocation;
		GLuint m_normalTextureUnitLocation;
		GLuint m_colorTextureUnitLocation;

		GLuint m_IdTextureUnitLocation;

		//I should create a new abstract class for this
		GLuint m_MaterialMapTextureUnitLocation;
		GLuint m_MaterialCountUnitLocation;

		GLuint m_UvTextureUnitLocation;
		GLuint m_AoTextureUnitLocation;


		GLuint m_eyeWorldPosLocation;
		GLuint m_matSpecularIntensityLocation;
		GLuint m_matSpecularPowerLocation;
		GLuint m_screenSizeLocation;
		*/
	};

}

#endif