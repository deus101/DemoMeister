#ifndef WORLD_HPP
#define WORLD_HPP


//#include "Rendrer\gbuffer.h"
#include "util.h"
//#include "Rendrer\context.h"

#include "bass.h"

#include "sync.h"



#include "Rendrer\base_buffer.h"
#include "Rendrer\gbuffer.h"
#include "Rendrer\aobuffer.h"

#include "SceneGraph\node.h"
#include "SceneGraph\objTransform.h"

#include "SceneGraph\camera.h"
#include "SceneGraph\composite.h"
//#include "SceneGraph\modelNode.h"
#include "ShaderFu\renderPacket.h"
//namespace PassItem = boost::property_tree;
#include "tinyxml2.h"

class PassItemnator
{
	std::string RepoName;
	//std::string ProductioFolder;
public:
	PassItemnator();
	int load(const std::string &filename);
	void save();
	void deploy();

private:
	tinyxml2::XMLDocument xml_PassRepo;
	//PassItem::ptree  PassData;
	boost::filesystem::path HumbleXML;
	boost::filesystem::path AssetGlobalLocation;
	boost::filesystem::path AssetProduction;
	boost::filesystem::path ReleaseFolder;

public:
	std::string Name;
	int PassValue;
	std::string PacketType;
	std::string BufferType;
	int BufferLocalPassValue;



};



typedef boost::shared_ptr< NS_SG::composite >  compoPointer;

typedef std::vector< NS_EFF::renderPacket* > vec_EffectPackets;
typedef std::vector< base_buffer* > vec_BufferContainer;
typedef std::vector< PassItemnator* > vec_PassDefinitions;




class DemoMeister
{



public:

	//remember destructors, carefull with utilizing the constructor before opengl is initialized,
	//the way its setup no it wont.

	DemoMeister();

	virtual ~DemoMeister() {};

	//all these should be virtual


	void AddPass();

	void AddPass(const std::string &filename);

	void AddNode();

	void AddEffect();

	//This is one of the main reasons Im doing this, I want a material system
	void AddAsset();

	void RetriveAsset();
	//This is one of the main reasons Im doing this, I want a material system
	void AddMaterial();

	void RetriveMaterial();

	//I want something to check for duplicates, materials and textures(materials can be different but use the same)
	//at some point this might be what I need the DemoMeister class for, a hackers space so I dont have to create a class for
	//everything like procedural textures.

	//either initialization of passes, packets and loading on models can be done on the fly
	//virtual void PreInit() = 0;
	//virtual void Init() = 0;
	//virtual void AfterInit() = 0;
	//I could set the soundtrack setup here but leave that for later

	//with an id argument perhaps, thinking gnu rocket should sync up here
	//virtual void HackerSpace() = 0;


	virtual void PreInit() = 0;
	virtual void Init() = 0;
	virtual void AfterInit() = 0;
	//I could set the soundtrack setup here but leave that for later

	//with an id argument perhaps, thinking gnu rocket should sync up here
	virtual void HackerSpace() = 0;


//private:
	//containers for textures, assets, packets, buffers,

	
public:
	vec_BufferContainer  MasterList_Buffers;

	vec_EffectPackets MasterList_Packets;

	vec_PassDefinitions  MasterList_Passes;
	//int WindowID;
	boost::shared_ptr<NS_SG::composite>  o_loader;
	//boost::weak_ptr<NS_SG::node>  anchor;
	//NS_SG::composite o_loader;
	// void keyDown(int key, int x, int y);
	//
	// void keyRelease(int key, int x, int y);
	//




	unsigned int ResolutionX;
	unsigned int ResolutionY;

	//void AddCue();


};



#endif
