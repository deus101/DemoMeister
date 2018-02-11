#pragma once


#include "../renderPacket.h"
#include "../DeferredPipeMother.h"


namespace NS_EFF {


	//class aoPacket : public renderPacket {
	//class aoPacket : public DeferredPipeMother<aoPacket>{
	class aoPacket : public DeferredPipeMother {
	public:


		aoPacket();
		~aoPacket();

		virtual bool Init();


		/*
		void SetWVP(const M3DMatrix44f& WVP);
		void SetWorldMatrix(const M3DMatrix44f& W);

		void SetViewMatrix(const M3DMatrix44f& V);

		void SetProjectionMatrix(const M3DMatrix44f& P);

		void SetScreenSize(unsigned int Width, unsigned int Height);



		//void SetPositionTextureUnit(unsigned int TextureUnit);
		//void SetNormalTextureUnit(unsigned int TextureUnit);
		//void SetNoiseTextureUnit(unsigned int TextureUnit);

		void SetPositionTextureUnit(GLenum TextureUnit);
		void SetNormalTextureUnit(GLenum TextureUnit);
		*/
		
		void SetNoiseTextureUnit(GLenum TextureUnit);


		void InitKernel();
		void InitNoise();

		const static unsigned int KERNEL_SIZE = 64;



		//samplers
		GLuint NoiseTexure;

		GLuint m_NoiseLocation;

		//GLuint m_posTextureUnitLocation;
		//GLuint m_normalTextureUnitLocation;
		


		GLuint m_KernelLocation;

		//GLuint m_WVPLocation;
		//GLuint m_ProjectionLocation;
		//GLuint m_ViewLocation;
		//GLuint m_WorldMatrixLocation;


		//gScreenSize
		//GLuint m_ScreenSizeLocation;


	};
}