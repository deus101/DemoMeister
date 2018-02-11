#ifndef RAYMARCHER_HPP
#define RAYMARCHER_HPP

#include "../renderPacket.h"
#include "../DeferredPipeMother.h"
//Jeg tror jeg overforbruker
namespace NS_EFF {

	//class RayMarcher : public renderPacket {
	//class RayMarcher : public DeferredPipeMother<RayMarcher> {
    class RayMarcher : public DeferredPipeMother {
	public:

		RayMarcher();

		virtual bool Init();
		/*
		void SetWVP(const M3DMatrix44f& WVP);
		//void SetWorldMatrix(const M3DMatrix44f& W);

		void SetViewMatrix(const M3DMatrix44f& V);

		void SetProjectionMatrix(const M3DMatrix44f& P);

		void SetMaterialMapUnit(GLenum TextureUnit);

		//array
		void SetColorTextureUnit(GLenum TextureUnit);

		void SetEyeWorldPos(const NS_VEC::VEC3& EyeWorldPos);

		void SetScreenSize(unsigned int Width, unsigned int Height);
		*/
	private:

		/*
		GLuint m_WVPLocation;
		GLuint m_ProjectionLocation;
		GLuint m_ViewLocation;
		GLuint m_WorldMatrixLocation;

		GLuint m_EyeWorldLoc;
		GLuint m_ScreenSizeLoc;

		GLuint m_MaterialMapTextureUnitLocation;

		GLuint v4_FarNearLocation;
		GLuint m_colorTextureUnitLocation;

		*/
	};
}

#endif