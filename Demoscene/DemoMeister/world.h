#ifndef WORLD_HPP
#define WORLD_HPP


//#include "Rendrer\gbuffer.h"

//#include "Rendrer\context.h"

//#include "bass.h"

//#include "sync.h"

#include "util.h"
#include "Engine\asset.h"
#include <DemoMeister\BufferFu\base_buffer.h>
#include <DemoMeister\BufferFu\gbuffer.h>
#include <DemoMeister\BufferFu\aobuffer.h>

#include "SceneGraph\node.h"
#include "SceneGraph\objTransform.h"

#include "SceneGraph\camera.h"
#include "SceneGraph\composite.h"
//#include "SceneGraph\modelNode.h"

/*SG*/






#include <DemoMeister\ShaderFu\renderPacket.h>
#include <DemoMeister\ShaderFu\DeferredPackets\aoPacket.h>
#include <DemoMeister\ShaderFu\DeferredPackets\RayMarcher.h>


#include "Engine\ShaderItem.h"
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

	void SetName(std::string arg) { Name = arg; }
	
	
	std::string GetName() { return Name; }
	
	//NS_ENG::NS_SHADER::ShaderItemPtr GetShaderComposition(GLenum Type)
	NS_ENG::NS_SHADER::BaseShaderItemPtr GetShaderComposition(GLenum Type) { 
		if(hasVertexShader && Type == GL_VERTEX_SHADER)
			return VertexCode;
		if (hasGeometryShader && Type == GL_GEOMETRY_SHADER)
			return GeometryCode;
		if (hasFragmentShader  && Type == GL_FRAGMENT_SHADER)
			return FragmentCode;

	}
	//std::string GetParsed

private:
	tinyxml2::XMLDocument xml_PassRepo;
	//PassItem::ptree  PassData;
	boost::filesystem::path HumbleXML;
	boost::filesystem::path AssetGlobalLocation;
	boost::filesystem::path AssetProduction;
	boost::filesystem::path ReleaseFolder;
	//NS_ENG::NS_SHADER::ShaderItem *VertexCode, *GeometryCode, *FragmentCode;
	//NS_ENG::NS_SHADER::BaseShaderItem *VertexCode, *GeometryCode, *FragmentCode;

	//NS_ENG::NS_SHADER::ShaderItemPtr VertexCode, GeometryCode, FragmentCode;
	NS_ENG::NS_SHADER::BaseShaderItemPtr VertexCode, GeometryCode, FragmentCode;


public:
	std::string Name;
	std::string Description;
	int PassValue;

	//I should consider using GUID
	std::string PacketType;
	std::string PacketName;
	int PacketIndex;

	std::string BufferType;
	std::string BufferName;
	int BufferIndex;

	std::string BufferLocalPassType;
	int BufferLocalIndex;
	int BufferLocalPassValue;



	bool hasVertexShader, hasGeometryShader, hasFragmentShader;
	


};





typedef boost::shared_ptr< NS_EFF::renderPacket >  sp_RenderPacket;
//typedef boost::shared_ptr< base_buffer >  sp_Buffer;
typedef boost::shared_ptr< base_buffer >  sp_Buffer;
typedef boost::shared_ptr< PassItemnator >  sp_PassItemnator;

typedef boost::shared_ptr< NS_EFF::RayMarcher >  sp_RaymarchPacket;
typedef boost::shared_ptr< NS_EFF::GeomPacket >  sp_GeomPacket;


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


extern factory g_factory;
//#define REGISTER_CLASS(n) g_factory.register_class<n>(#n)



//Not just a lazy singleton.
class DemoMeister //would inheriting from the Composite/Root Node be a good idea?
{





//public:



//All Initialisation data, custom or no clutters up the main or where ever.
//For each prod I'm working on I'll create a template in the Production Folder with a 
//simple concrete version of this class in a similarly named c++/h.


//If I want to add custom models, experiment, overload a few classes and generally fuck about then the Base code and Assets don't have
//to be modified.
//My idea is to be able to create demos with only two tabs open in the IDE.

//Further more as this is a singelton its a safe place to add and implement runtime libraries like GUIs, Bass and a place to deal with those damn.
//sync objects


//There will also be a deploy function for release using data gathered and saved with DeployDebug build.
public:

	//remember destructors, carefull with utilizing the constructor before opengl is initialized,
	//the way its setup no it wont.
	
	
	//should be protected or private, but this is only a base class...
	DemoMeister();

	virtual ~DemoMeister() {};

	//all these should be virtual, the Accessors will have one set of global classes and prototyes for the base function
	//If I want to add more in the production Zones Ill just overload it and make sure Ill call the original.

	//These must have error codes.
	void AddPass();


	void AddPass(const std::string &filename);

	

	

	//returns the index which it was placed, if type is not found, it returns -2, if name is not found returns -1.
	//If the Name and Type(better just make it Name) allready exsist, its index is returned.
	//Just remember to catch them.
	//int AddEffect(std::string Type, std::string Name);
	size_t  AddEffect(const std::string& TypeName, const std::string& Name);
	//Should rename to AddPacket

	size_t  AddBuffer(const std::string& TypeName, const std::string& Name);

	//Strings for now, these are used for initialization anyway so speed is no issue.
	//things are gonna get confusing pretty quick however. Which Is why I plan to use a prototype pattern 
	//and a quantifiable identifier. 
	//This is one of the main reasons Im doing this, I want a material system
	
	void AddNode();
	
	void AddAsset();

	void AddMaterial();


	//void AddTexture(boost::filesystem::path argPath, GLint &SamplerId, GLint &MapId, NS_ENG::TextureDesc);
	void AddTexture(boost::filesystem::path argPath, GLint &MapId, NS_ENG::TextureDesc *Initial);




	




	//Use default argument for both of these, error if both are not filled in.
	//The way I'm doing it now you only need one instance of each RenderPacket so type would be enough.
	//However even though I've gone to the trouble making them individual packets can be repurpused depending on the pass
	size_t RetriveEffectID(const std::string &TypeName, const std::string &Name);
	//http://boost-spirit.com/dl_more/fusion_v2/libs/fusion/doc/html/fusion/container/map.html
	//https://stackoverflow.com/questions/4195100/templates-for-setters-and-getters
	//http://www.boost.org/doc/libs/1_62_0/doc/html/boost_typeindex/getting_started.html


	//I sorely need a more durable and conscice ID, what more it should store a direct access index.
	//http://en.cppreference.com/w/cpp/types/ptrdiff_t
	//Need a solution to this, I should use size_t but I really want my negatives for error.
	//Eh pass by reference.

	//sp_RenderPacket RetriveEffect(const std::string &Type, const std::string &Name);



	sp_RenderPacket RetriveEffect(size_t idx);


	//template <class T>
	//boost::shared_ptr<T> getParent() const {
	//	return boost::dynamic_pointer_cast<T>(parent.lock());
	//}
	template <class T>
	T* RetriveEffect(const std::string &TypeName, const std::string &Name) {

		size_t idx = this->RetriveEffectID(TypeName, Name);
		//there are better ways then this.
		if (this->MasterList_Packets.size() < idx || idx == 0)
			return NULL;

	

		return &*(boost::static_pointer_cast<T>(this->MasterList_Packets.at(idx - 1)));
	}


	sp_RenderPacket RetriveEffect(const std::string &TypeName, const std::string &Name);



	size_t RetrivePassID(const std::string &TypeName, const std::string &Name);



	sp_PassItemnator RetrivePass(size_t idx);

	sp_PassItemnator RetrivePass(const std::string &TypeName, const std::string &Name);



	//These really should be templated  
	size_t RetriveBufferID(const std::string &Type, const std::string &Name);

	
	sp_Buffer RetriveBuffer(size_t idx);


	void RetriveAsset();

	void RetriveMaterial();


	//Actually it all should start with the first material.
	bool InitEffects(const std::string &Type , const std::string &Name, size_t idx);

	void InitBuffers();

	//Mesh 

	//Model

	//Texture

	//Shader

	//EffectGraph

	//I want something to check for duplicates, materials and textures(materials can be different but use the same)
	//at some point this might be what I need the DemoMeister class for, a hackers space so I dont have to create a class for
	//everything like procedural textures.

	//with an id argument perhaps, thinking gnu rocket should sync up here
	//virtual void HackerSpace() = 0;


	virtual void PreInit() = 0;
	virtual void Init() = 0;
	virtual void AfterInit() = 0;
	//I could set the soundtrack setup here but leave that for later

	//with an id argument perhaps, thinking gnu rocket should sync up here
	virtual void HackerSpace() = 0;



//Should be private, need Getters and prototypes
public:
	typedef std::vector< sp_RenderPacket > vec_EffectPackets;
	typedef std::vector< sp_Buffer > vec_BufferContainer;
	typedef std::vector< sp_PassItemnator > vec_PassDefinitions;


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
