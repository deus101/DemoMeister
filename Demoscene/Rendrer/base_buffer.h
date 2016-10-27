#pragma once

class base_buffer
{
public:

	enum TARGET_BUFFERS_TYPE{
		PASS_GBUFFER,
		PASS_AOBUFFER,
		PASS_BLURBUFFER,
		PASS_LIGHT
	};


	//I could use enums to identify the specific components, but I was wondering if I should create a struct type 
	//that has all the relevant informations for binding...and to get a proper overview 
	//virtual void SetAttachments();
	//virtual void GetSampler();


	base_buffer();

	~base_buffer();

	virtual int Init(unsigned int WindowWidth, unsigned int WindowHeight) { return 0; };
	virtual void EnablePass(int PassId) {};


};


class composite_buffer : public base_buffer
{


	
public:

	composite_buffer(void);



	void NewBuffer(int);




};