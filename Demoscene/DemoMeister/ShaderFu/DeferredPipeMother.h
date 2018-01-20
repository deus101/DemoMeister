#ifndef DEFERREDMOTHERPACKET_HPP
#define DEFERREDMOTHERPACKET_HPP

#include "renderPacket.h"


namespace NS_EFF {


	class DeferredPipeMother : public renderPacket {


	public:
		DeferredPipeMother();
		~DeferredPipeMother();

		bool RecivePassHandshake();

		virtual bool Init();

		void SetWVP(const M3DMatrix44f& WVP);
		void SetWorldMatrix(const M3DMatrix44f& W);

		void SetViewMatrix(const M3DMatrix44f& V);

		void SetProjectionMatrix(const M3DMatrix44f& P);

		void SetEyeWorldPos(const NS_VEC::VEC3& EyeWorldPos);

		void SetScreenSize(unsigned int Width, unsigned int Height);


		void SetTasks();

		//void SetDiffuseTextureUnit(unsigned int TextureUnit);
		void SetDiffuseTextureUnit(GLenum TextureUnit);


		void SetDeferreDiffuseTextureUnit(GLenum TextureUnit);
		void SetDeferreBumpTextureUnit(GLenum TextureUnit);



		//void SetDiffuseTextureUnit(GLint TextureUnit);
		//void SetBumpTextureUnit(unsigned int TextureUnit);

		void SetPositionTextureUnit(GLenum TextureUnit);
		//void SetIdTextureUnit(unsigned int TextureUnit);
		void SetAbedoTextureUnit(GLenum TextureUnit);
		void SetNormalTextureUnit(GLenum TextureUnit);
		void SetUvTextureUnit(GLenum TextureUnit);
		void SetAoTextureUnit(GLenum TextureUnit);





		void SetbaseMaterialMapUnit(GLenum TextureUnit);
		//void SetbaseMaterialMapUnit(GLint TextureUnit);
		void SetMaterialsCount(unsigned int MatCount);

	protected:



		//Forward loaded textures
		GLuint m_diffuseTextureUnitLocation;
		GLuint m_bumpTextureUnitLocation;
		//Should put these in a tupple 

		//New Array textures
		GLuint m_DeferredDiffuseTextureUnitLocation;
		GLuint m_DeferredBumpTextureUnitLocation;


		//Result from FBO
		GLuint m_posTextureUnitLocation;
		GLuint m_AbedoTextureUnitLocation;
		GLuint m_normalTextureUnitLocation;
		GLuint m_UvTextureUnitLocation;
		GLuint m_AoTextureUnitLocation;
		//how about t for Target or RT





		GLuint m_baseMaterialMapTextureUnitLocation;
		GLuint m_MaterialCountUnitLocation;
		//I need a better way to name my uniforms, why did i put m infront of everything


	};

}

#endif