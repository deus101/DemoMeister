#pragma once

//#include "../Engine/map.h"
#include "../Engine/AssetMapClasses/map.h"


#include "../util.h"
#include "../ShaderFu/renderPacket.h"

#include <string>
#include <list>


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

struct S_PassDependencies {
	std::string PassName;
	int PassIDX;
	int PassValue;
};

struct S_LocalBuffer {
	std::list<S_PassDependencies*> LocalDependencyList;
	int PassRangeMin, PassRangeMax;
};

class base_buffer{

public:

	virtual ~base_buffer() {};

	virtual base_buffer *clone() const = 0;


	virtual bool Init(unsigned int WindowWidth, unsigned int WindowHeight) = 0;
	virtual void EnablePass(int PassId) = 0;

	
	
	//virtual boost::shared_ptr<base_buffer> clone() const = 0;
	

	void SetName(std::string arg) { BufferName = arg; }
	std::string GetName() { return BufferName; }

	
	void SetType(std::string arg) { BufferType = arg; }
	std::string GetType() { return BufferType; }

	int GetNumberOfSamples() { return Nr_Samples; };
	void SetNumberOfSamples(int var) { Nr_Samples = var;};

	enum TARGET_BUFFERS_TYPE
	{
		PASS_GBUFFER,
		PASS_AOBUFFER,
		PASS_BLURBUFFER
	};


protected:
	std::string BufferName;
	std::string BufferType;
	std::list<S_PassDependencies> RegionalPassList;
	std::list<S_LocalBuffer> LocalPassProperties;
	GLuint m_fbo;
	int Nr_Samples;
	size_t Nr_LocalPasses;
	//S_LocalBuffer LocalPasses[];
};


template <typename ConcreteBuffer>
class Buffer_CRTP : public base_buffer {
public:
	virtual base_buffer *clone()const {
		return  new ConcreteBuffer(static_cast<ConcreteBuffer const&>(*this));
	}
};


//#define Derive_Buffer_CRTP(Type) class Type: public Buffer_CRTP<Type>


//Derive_Buffer_CRTP(AoBuffer) {};
//Derive_Buffer_CRTP(GBuffer) {};