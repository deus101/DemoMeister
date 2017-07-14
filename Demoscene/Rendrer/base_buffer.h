#pragma once

#include "../Engine/map.h"

#include "../util.h"
#include "../ShaderFu/renderPacket.h"

#include <string>

//#include "../FreeImage.h"
struct Pass_Sample
{

	Pass_Sample()
	{
		name = " ";
		TextureID = -0;
		Attachment = -0;

	}
std::string name;
int TextureID;
int Attachment;



};


class base_buffer
{
public:
/*
#define COLOR_TEXTURE_UNIT              GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX        0
#define SHADOW_TEXTURE_UNIT             GL_TEXTURE1
#define SHADOW_TEXTURE_UNIT_INDEX       1
#define NORMAL_TEXTURE_UNIT             GL_TEXTURE2
#define NORMAL_TEXTURE_UNIT_INDEX       2
#define RANDOM_TEXTURE_UNIT             GL_TEXTURE3
#define RANDOM_TEXTURE_UNIT_INDEX       3
#define DISPLACEMENT_TEXTURE_UNIT       GL_TEXTURE4
#define DISPLACEMENT_TEXTURE_UNIT_INDEX 4
#define MOTION_TEXTURE_UNIT             GL_TEXTURE5
#define MOTION_TEXTURE_UNIT_INDEX       5
*/
	
	//I want something that keeps track of the samplers not specific to an fbo
	enum TARGET_BUFFERS_TYPE{
		PASS_GBUFFER,
		PASS_AOBUFFER,
		PASS_BLURBUFFER
	};


	/*
	struct FBODesc
	
	
	struct SamplerDesc
	
	
	*/

	//I want the buffer objects to keep track of the packets or should it be reverse?


	//I could use enums to identify the specific components, but I was wondering if I should create a struct type 
	//that has all the relevant informations for binding...and to get a proper overview 
	//virtual void SetAttachments();
	//virtual void GetSampler();


	base_buffer() {};

	~base_buffer() {};

	virtual bool Init(unsigned int WindowWidth, unsigned int WindowHeight) = 0;
	virtual void EnablePass(int PassId) = 0;
	
	int GetNumberOfSamples() { return Nr_Samples; };
	void SetNumberOfSamples(int var) { Nr_Samples = var;};

	

protected:
	GLuint m_fbo;
	int Nr_Samples;

};

/*
class composite_buffer : public base_buffer
{


	
public:

	composite_buffer(void);



	void NewBuffer(int);




};
*/