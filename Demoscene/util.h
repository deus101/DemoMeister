
#ifndef UTIL_HPP
#define	UTIL_HPP


#include "math/math3d.h"
//#include "math/vec.h"
//#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <typeinfo>
#include <set>
#include <map>
//#include <Windows.h>
//#include <Shlwapi.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>



//using namespace std; JESUS!
void EngError(const char* fn, unsigned int ln, const char* msg);
void EngFileError(const char* fn, unsigned int ln, const char* fmsg);


#define ENG_ERROR(s_err) EngError(__FILE__, __LINE__, s_err);
#define ENG_FILE_ERROR(s_file_err) EngFileError(__FILE__, __LINE__, s_file_err);


/*
template <class T> void* constructor() { return (void*)new T(); }
struct factory
{
	typedef void*(*constructor_t)();
	typedef std::map<std::string, constructor_t> map_type;
	map_type m_classes;

	template <class T>
	void register_class(std::string const& n)
	{
		m_classes.insert(std::make_pair(n, &constructor<T>));
	}

	void* construct(std::string const& n)
	{
		map_type::iterator i = m_classes.find(n);
		if (i == m_classes.end()) return 0; // or throw or whatever you want
		return i->second();
	}
};

factory g_factory;

#define REGISTER_CLASS(n) g_factory.register_class<n>(#n)
*/
#include <vector>
/*

template<typename T>
class X
{
    public:
        T const& operator[](std::size_t index) const    {return const_cast<X&>(*this)[index];}
        T&       operator[](std::size_t index)          {return data[index];}
        void        remove(std::size_t index)           {unused.push_back(index);}

        
		std::size_t insert(T  value);
    private:
        std::vector<T>                  data;
        std::vector<std::size_t>        unused;
};

template<typename T>
std::size_t X<T>::insert(T  value)
{
    if (unused.empty())
    {
        data.push_back(value);
        return data.size() - 1;
    }
    std::size_t result  = unused.back();
    unused.pop_back();
    data[result]    = value;
    return result;
}

*/





//used as a singleton on Extern Squiddy
struct DeploymentOrganizer
{
	




	std::string ProjectFolder;              
	std::string ProductionName;
	std::string ProductioFolder;

	std::set<std::string> Resource_Paths;


	
	//std::set<boost::filesystem::path> Resource_Paths;
	void load(const std::string &filename);
	void save();
	void deploy();


	std::string FindAndRegister(const std::string &Item);

	boost::filesystem::path HumbleIni;

	boost::filesystem::path AssetGlobal;
	boost::filesystem::path AssetProduction;

	boost::filesystem::path ReleaseFolder;

	boost::filesystem::path Util_CurrentFolder;
	//boost::filesystem::path HumbleIni;

};


extern DeploymentOrganizer Squiddy;

enum TypeOfTexture
{
	ActiveTexture,
	DiffuseMap_UNIT,
	BumpMap_UNIT,
	MaterialMap_UNIT,

	GBuffer_WorldPos_UNIT,
	GBuffer_Albedo_UNIT,
	GBuffer_Normal_UNIT,
	GBuffer_UV_UNIT,

	AOBuffer_NOISE,
	AOBuffer_AO_UNIT,
	AOBuffer_Blur_UNIT,     
   
	Size 


};

/*
char* AssetCategoryPath[3][3]{ {"Materials", "Models","Shaders",



	
	}
}

*/

enum e_InstructionActors {
	Self, Rendrer, PassInit, BufferInit, AssetInit, EffectInit,RocketInit,TransFormNode,AssetNode




};

struct PipelineTask {
	e_InstructionActors target;
	std::string TarType, TarName;
	int TarID;
	e_InstructionActors Supplicant;
	std::string SupType, SupName;
	int SupID;
	std::string PropertyName;
	float Return;

};

struct EffectStage
{
	bool bReqComplete;
	int iStageValue;
	//GLint TextureUnits[Size];
	GLenum TextureUnits[Size];
	//GLUint TextureUnits[Size];
};

typedef boost::shared_ptr< struct EffectStage > EffectStagePtr;
typedef boost::shared_ptr<const struct EffectStage> EffectStageConstPtr;

struct BaseLight
{
	NS_VEC::VEC3 Color;
	float AmbientIntensity;
	float DiffuseIntensity;

	BaseLight()
	{
		Color = NS_VEC::VEC3(0.0f, 0.0f, 0.0f);
		AmbientIntensity = 0.0f;
		DiffuseIntensity = 0.0f;
	}
};

struct DirectionalLight : public BaseLight
{
	NS_VEC::VEC3 Direction;

	DirectionalLight()
	{
		Direction = NS_VEC::VEC3(0.0f, 0.0f, 0.0f);
	}
};

struct PointLight : public BaseLight
{
	NS_VEC::VEC3 Position;

	struct
	{
		float Constant;
		float Linear;
		float Exp;
	} Attenuation;

	PointLight()
	{
		Position = NS_VEC::VEC3(0.0f, 0.0f, 0.0f);
		Attenuation.Constant = 0.0f;
		Attenuation.Linear = 0.0f;
		Attenuation.Exp = 0.0f;
	}
};

struct SpotLight : public PointLight
{
	NS_VEC::VEC3 Direction;
	float Cutoff;

	SpotLight()
	{
		Direction = NS_VEC::VEC3(0.0f, 0.0f, 0.0f);
		Cutoff = 0.0f;
	}
};
//float fmax(float a, float b);
#define COLOR_WHITE Vector3f(1.0f, 1.0f, 1.0f)
#define COLOR_RED Vector3f(1.0f, 0.0f, 0.0f)
#define COLOR_GREEN Vector3f(0.0f, 1.0f, 0.0f)
#define COLOR_CYAN Vector3f(0.0f, 1.0f, 1.0f)
#define COLOR_BLUE Vector3f(0.0f, 0.0f, 1.0f)


#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

#define INVALID_UNIFORM_LOCATION 0xffffffff
#define INVALID_OGL_VALUE 0xffffffff


//slett dette
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

#endif	