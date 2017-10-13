
#ifndef AOBUFFER_H
#define	AOBUFFER_H

#include "../Math/vec.h"
#include "base_buffer.h"


//plan is to inherit base_buffer

//#define Derive_Buffer_CRTP(Type) class Type: public Buffer_CRTP<Type>
//class AoBuffer : public base_buffer
//Derive_Buffer_CRTP(AoBuffer)

class AoBuffer : public Buffer_CRTP<AoBuffer>
{
public:


	AoBuffer();

	~AoBuffer();


	/*~AoBuffer()
	{
	}
	*/
	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	//bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

	void EnablePass(int PassId);
	//bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	void BindForAoPass();
	//void StartFrame();
	//void BindForGeomPass();
	//void BindForStencilPass();
	//void BindForLightPass();
	//void BindForFinalPass();

	enum AO_TEXTURE_TYPE {
		AO_TEXTURE_TYPE_AO_MAP,
		//AO_TEXTURE_TYPE_NOISE,
		//AO_TEXTURE_TYPE_NORMAL,
		AO_NUM_TEXTURES
	};


	GLuint ao_textures[AO_NUM_TEXTURES];


	//ReadAttachments <- no not Attachment these are textures.
	GLuint gb_PosDepth;
	GLuint gb_Normal;
	GLuint gb_Noise;

private:

	//GLuint  ao_fbo;
	//GLuint m_fbo;
	//GLuint m_uniforms[GBUFFER_NUM_UNIFORMS];
	//GLuint m_textures[GBUFFER_NUM_TEXTURES];



};

#endif	

