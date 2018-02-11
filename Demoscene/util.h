#ifndef UTIL_HPP_876BA70D_0A2B_48DE_BA9C_D6BAA8BF7DCE
#define	UTIL_HPP_876BA70D_0A2B_48DE_BA9C_D6BAA8BF7DCE


//#include "Engine\asset.h"
//#include <stdlib.h>
//#include <stdio.h>

#include <typeinfo>
#include <set>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <vector>

//ikke riktig
typedef boost::tuple< std::string, std::size_t, bool> tup_PassLookup;
typedef std::list<tup_PassLookup> LookupList;


#include <math/math3d.h>


typedef boost::tuple< std::string, GLenum, GLint, int, int, int, bool> tup_Samplers;
//typedef std::list<tup_Samplers> SamplerList;
typedef std::vector<tup_Samplers> SamplerList;


class DemoMeister;
extern DemoMeister * TheDisc;

//used as a singleton on Extern Squiddy
struct DeploymentOrganizer
{
	
	std::string ProjectFolder;              
	std::string ProductionName;
	std::string ProductioFolder;

	std::set<std::string> Resource_Paths;


	//std::set<boost::filesystem::path> Resource_Paths;

public:
	void load(const std::string &filename);
	void save();
	void deploy();


	std::string FindAndRegister(std::string Path);
	//std::string FindAndRegister(const std::string &Item);

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
	DiffuseArrayMap_UNIT,
	BumpArrayMap_UNIT,
	baseMaterialMap_UNIT,
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

#endif

