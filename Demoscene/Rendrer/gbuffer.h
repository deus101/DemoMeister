/*this is mine now*/

#ifndef GBUFFER_H
#define	GBUFFER_H

#include "base_buffer.h"
#include "../Math/vec.h"





class GBuffer : public Buffer_CRTP<GBuffer>
{
public:


	enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_ABEDO,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_UV,
		GBUFFER_NUM_TEXTURES
	};
	/*
	enum AO_TEXTURE_TYPE {
		AO_TEXTURE_TYPE_AO_MAP,
		//AO_TEXTURE_TYPE_NOISE,
		//AO_TEXTURE_TYPE_NORMAL,
		AO_NUM_TEXTURES
	};
	*/
	GBuffer();

	~GBuffer();

	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	//bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

	void EnablePass(int PassId);

	void StartFrame();
	void BindForGeomPass();
	//void BindForAoPass();
	void BindForStencilPass();
	void BindForLightPass();
	void BindForFinalPass();


	GLuint m_textures[GBUFFER_NUM_TEXTURES];
	GLuint m_depthTexture;
	GLuint m_finalTexture;
private:

	//GLuint m_fbo, geo_fbo, ao_fbo, light_fbo;
	//GLuint m_fbo;
	//GLuint m_uniforms[GBUFFER_NUM_UNIFORMS];
	

	//GLuint ao_textures[AO_NUM_TEXTURES];

	//GLuint m_AoTexture;

	

};

#endif	

