#pragma once


//#include "../util.h"
#include <string>

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

	

	enum TARGET_BUFFERS_TYPE{
		PASS_GBUFFER,
		PASS_AOBUFFER,
		PASS_BLURBUFFER
	};


	//I could use enums to identify the specific components, but I was wondering if I should create a struct type 
	//that has all the relevant informations for binding...and to get a proper overview 
	//virtual void SetAttachments();
	//virtual void GetSampler();


	base_buffer() {};

	~base_buffer() {};

	virtual bool Init(unsigned int WindowWidth, unsigned int WindowHeight) = 0;
	virtual void EnablePass(int PassId) = 0;
	
	int GetNumberOfSamples() { return Nr_Samples; };
	void SetNumberOfSamples(int var) { Nr_Samples = var; };

	

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