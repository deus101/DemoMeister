
#ifndef AOBUFFER_H
#define	AOBUFFER_H

#include "../Math/vec.h"
//plan is to inherit base_buffer
class AOBUFFER
{
public:
	/*
	enum PRIMITIVE_COLOR_INPUT {
		GBUFFER_MATERIAL_DIF_UNILOC,
		GBUFFER_MATERIAL_SPECINT_UNILOC,
		GBUFFER_MATERIAL_SPECPOW_UNILOC,
		GBUFFER_NUM_UNIFORMS
	};
	*/

	enum AO_TEXTURE_TYPE {
		AO_TEXTURE_TYPE_AO_MAP,
		//AO_TEXTURE_TYPE_NOISE,
		//AO_TEXTURE_TYPE_NORMAL,
		AO_NUM_TEXTURES
	};

	AOBUFFER();

	~AOBUFFER();
	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	//bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

	//void StartFrame();
	//void BindForGeomPass();
	void BindForAoPass();
	//void BindForStencilPass();
	//void BindForLightPass();
	//void BindForFinalPass();


	
private:

	GLuint m_fbo, ao_fbo;
	
	//GLuint m_uniforms[GBUFFER_NUM_UNIFORMS];
	//GLuint m_textures[GBUFFER_NUM_TEXTURES];

	GLuint ao_textures[AO_NUM_TEXTURES];


	//ReadAttachments
	GLuint gb_PosDepth;
	GLuint gb_Normal;
	GLuint gb_Noise;
	

};

#endif	

