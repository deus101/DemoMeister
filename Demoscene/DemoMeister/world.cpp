
#include "world.h"
//#include "Rendrer\context.h"
//#include "util.h"
//#include <iostream>

//#define DegToRad 0.01745329f

//GLfloat turn = 0.0;
//GLuint VertexArrayID;

//HSTREAM stream;

//boost::shared_ptr<NS_SG::modelNode> mn_ShowPiece

#include "SceneGraph\sceneparser.h"
#include "SceneGraph\assetNode.h"
#include "SceneGraph\modelNode.h"
#include "SceneGraph\dirLightNode.h"
#include "SceneGraph\pointLightNode.h"
#include "SceneGraph\targetNode.h"

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>


PassItemnator::PassItemnator() {


}

int PassItemnator::load(const std::string &filename)
{
	HumbleXML = boost::filesystem::path(filename.c_str());

	HumbleXML.normalize();


	bool test = HumbleXML.is_complete();

	tinyxml2::XMLError Status = xml_PassRepo.LoadFile(HumbleXML.string().c_str());

	tinyxml2::XMLElement *el_PassInfo;
	if(Status == tinyxml2::XML_SUCCESS)
	{
		el_PassInfo = xml_PassRepo.FirstChildElement("pass");
	}
	else
	{
		return Status;
	}

	//<pass name="Gbuffer_Forward" packet="GeomPacket" PassValue="100" Buffer="GBuffer" BufferLocalPass="1">
	//One pass should handle multiple packets and the packets should be sorted by sub-groups, categories and intended properties.
	this->Name = el_PassInfo->Attribute("name");
	this->PacketType = el_PassInfo->Attribute("packet");
	this->PacketName = el_PassInfo->Attribute("packetInstance");
	this->PassValue = el_PassInfo->IntAttribute("PassValue");
	this->BufferType = el_PassInfo->Attribute("Buffer");
	this->BufferLocalPassValue = el_PassInfo->IntAttribute("BufferLocalPass");
	//PassItem::read_xml(HumbleXML.string(), PassData);


	size_t EffectIndex;
	EffectIndex = TheDisc->AddEffect(this->PacketType, this->PacketName);
	
	sp_RenderPacket Tmp_Packet_Ptr = TheDisc->RetriveEffect(EffectIndex);

	bool EffectAdded = false;
	bool EffectPassHandshake = false;




	if (Tmp_Packet_Ptr != NULL)
	{
		if (0 == this->PacketName.compare(Tmp_Packet_Ptr->GetName()))
			EffectAdded = true;

		Tmp_Packet_Ptr->SetPassName(this->Name);
		EffectPassHandshake = Tmp_Packet_Ptr->PacketPassHandshake();

	}

	//DemoMeister::g_factory.construct(this->PacketType);


	size_t BufferIndex;
	BufferIndex = TheDisc->AddBuffer(this->BufferType, this->BufferType);

	
	//template <class g_factory.construct(this->BufferType> <)>(BufferIndex);
	//sp_Buffer Tmp_Buffer_Ptr = TheDisc->RetriveBuffer<sp_Buffer>(BufferIndex);

	sp_Buffer Tmp_Buffer_Ptr = TheDisc->RetriveBuffer(BufferIndex);

	bool BufferAdded = false;
	bool BufferPassHandshake = false;

	if (Tmp_Buffer_Ptr != NULL)
	{
		if (0 == this->BufferType.compare(Tmp_Buffer_Ptr->GetName()))
			BufferAdded = true;


		//Tmp_Buffer_Ptr->(this->Name);
		//EffectPassHandshake = Tmp_Packet_Ptr->PacketPassHandshake();

	}


	tinyxml2::XMLElement *el_Requirements = el_PassInfo->FirstChildElement("requirements");

	if (el_Requirements)
	{
		tinyxml2::XMLElement *requireMentChildren;
		requireMentChildren = el_Requirements->FirstChildElement();
		int nr_Components = 0;
		
		
		while (requireMentChildren != NULL)
		{


			std::string Name = requireMentChildren->Attribute("Name");

			nr_Components++;
			requireMentChildren = requireMentChildren->NextSiblingElement();
		}
		
		



	}


	
	//tinyxml2::XMLElement *el_BaseShaders = el_PassInfo->FirstChildElement();
	tinyxml2::XMLElement *el_BaseShaders = el_PassInfo->FirstChildElement("Base_Shaders");
	
	if(el_BaseShaders)
	{
	hasVertexShader = el_BaseShaders->BoolAttribute("vertex");
	hasGeometryShader = el_BaseShaders->BoolAttribute("geometry");
	hasFragmentShader = el_BaseShaders->BoolAttribute("fragment");

	el_BaseShaders = el_BaseShaders->FirstChildElement();
	if (hasVertexShader) {
		

		if(0  == std::string("Base_Vert").compare(el_BaseShaders->Value()))
		{ 
			this->VertexCode = NS_ENG::NS_SHADER::BaseShaderItemPtr(new NS_ENG::NS_SHADER::BaseShaderItem(GL_VERTEX_SHADER,
				
				Squiddy.FindAndRegister( el_BaseShaders->Attribute("Path")),
					el_BaseShaders->Attribute("Target"), NS_ENG::NS_SHADER::Base
			));
		
		}

	}

	if (hasGeometryShader) {
		el_BaseShaders = el_BaseShaders->NextSiblingElement();

		if (0 == std::string("Base_Geom").compare(el_BaseShaders->Value()))
		{
			//this->GeometryCode = new NS_ENG::NS_SHADER::BaseShaderItem(
			this->GeometryCode = NS_ENG::NS_SHADER::BaseShaderItemPtr(new NS_ENG::NS_SHADER::BaseShaderItem(GL_GEOMETRY_SHADER,

				Squiddy.FindAndRegister(el_BaseShaders->Attribute("Path")),
				el_BaseShaders->Attribute("Target"), NS_ENG::NS_SHADER::Base));

		}
	}	
	if (hasFragmentShader) {
		el_BaseShaders = el_BaseShaders->NextSiblingElement();
		tinyxml2::XMLElement *fragMentChildren;

		if (0 == std::string("Base_Frag").compare(el_BaseShaders->Value()))
		{
			this->FragmentCode = NS_ENG::NS_SHADER::BaseShaderItemPtr(new NS_ENG::NS_SHADER::BaseShaderItem(GL_FRAGMENT_SHADER,

				Squiddy.FindAndRegister(el_BaseShaders->Attribute("Path")),
				el_BaseShaders->Attribute("Target"), NS_ENG::NS_SHADER::Base));
			///*
			//	<Include_Component Name = "SDF_Bounds" Path = "hd_sdf.glsl" Marker = "#MELD hg_sdf.glsl" / >
			fragMentChildren = el_BaseShaders->FirstChildElement();
			int nr_Components = 0;
			
			while(fragMentChildren != NULL)
			{
				if (0 == std::string("Include_Component").compare(fragMentChildren->Value()))
				{

					std::string Name = fragMentChildren->Attribute("Name");
					std::string Path = fragMentChildren->Attribute("Path");
					std::string SquidPath = Squiddy.FindAndRegister(Path.c_str());

					std::string Marker = fragMentChildren->Attribute("Marker");

					
					this->FragmentCode->AddShader(
						GL_FRAGMENT_SHADER, 
						SquidPath,
						Name, 
						NS_ENG::NS_SHADER::Include,
						Marker
					);
					
					


				}
				nr_Components++;
				fragMentChildren = el_BaseShaders->NextSiblingElement();
			}
		//*/
		}
	}
	}





	return Status;
}




DemoMeister::DemoMeister() //public context()
{
	
	//BufferContainer.push_back()
	
	//o_loader = compoPointer(new NS_SG::composite("root"));
	o_loader  = boost::make_shared<NS_SG::composite>("root");
	//o_loader->addChild(new NS_SG::objTransform("Test"));
	//typedef boost::shared_ptr< NS_SG::composite >  compoPointer;
}

/*
DemoMeister::~DemoMeister() //public context()
{

	//BufferContainer.push_back()

	//o_loader = compoPointer(new NS_SG::composite("root"));

	//o_loader->addChild(new NS_SG::objTransform("Test"));

}
*/

void DemoMeister::AddPass()
{
	//might be a nice addition to use as a callback for the Projects inheriting from demomeister

}



void DemoMeister::AddPass(const std::string &filename)
{
	
	//MasterList_Passes.push_back(sp_PassItemnator(new PassItemnator()));
	
	MasterList_Passes.push_back( boost::make_shared<PassItemnator>());

	MasterList_Passes.back()->load(filename);
	/*
	//MasterList_Passes.back()->
	boost::filesystem::path file_XML = boost::filesystem::path(filename.c_str());

	file_XML.normalize();


	bool test = file_XML.is_complete();

	tinyxml2::XMLDocument xml_Tmp;

	tinyxml2::XMLError Status = xml_Tmp.LoadFile(file_XML.string().c_str());

	tinyxml2::XMLElement *el_PassInfo;
	if (Status == tinyxml2::XML_SUCCESS)
	{
		el_PassInfo = xml_Tmp.FirstChildElement("pass");
	}
	else
	{
		//return Status;
		return;
	}

	//<pass name="Gbuffer_Forward" packet="GeomPacket" PassValue="100" Buffer="GBuffer" BufferLocalPass="1">
	//One pass should handle multiple packets and the packets should be sorted by sub-groups, categories and intended properties.
	this->Name = el_PassInfo->Attribute("name");
	this->PacketType = el_PassInfo->Attribute("packet");
	this->PacketName = el_PassInfo->Attribute("packetInstance");
	this->PassValue = el_PassInfo->IntAttribute("PassValue");
	this->BufferType = el_PassInfo->Attribute("Buffer");
	this->BufferLocalPassValue = el_PassInfo->IntAttribute("BufferLocalPass");

	*/
}

void DemoMeister::AddNode()
{

}


//UGH! This is going to shit. I'll just prototype it and find a better solution later.
void  DemoMeister::AddTexture(boost::filesystem::path argPath, GLint &MapId, NS_ENG::TextureDesc *Initial)
{
	
	//NS_ENG::ArrayTextureDesc *BindTo;
	NS_ENG::TextureDesc *BindTo;
	//first component in a filename
	std::string DomainTag;
	//Should be in the middle
	std::string TextureName;
	//Last Component is about the dimensions and depth 1024x24 f.eks.
	int dimension;
	int depth;

	std::string StrContent = "";
	int SortValue = 0;


	switch (Initial->MapContent)
	{

	case  NS_ENG::MAP_CONTENT_TYPE::DIFFUSE:
	{
		SortValue = 10;
		StrContent = "Diffuse";
		break;
	}
	case  NS_ENG::MAP_CONTENT_TYPE::BUMP: 
	{
		SortValue = 20;
		StrContent = "Normal";
		break;
	}
	}



	boost::filesystem::path fileName = argPath.filename();
	boost::filesystem::path Folder = argPath.parent_path();
	boost::filesystem::path fileNameNoSuffix = fileName.replace_extension();

	std::vector<std::string> tokens;
	
	boost::split(tokens, fileName.string(), std::bind2nd(std::equal_to<char>(), '_'));
	
	//boost::split(tokens, fileName.string(), boost::is_any_of("_"));
	int Nr_Attributes = tokens.size();


	//naturally its meant to be more rigid then this...ah fuck it...why not just make do with the filename format.
	bool AddToArray = false;
	if (Nr_Attributes == 3)
	{


		boost::regex expr("(\\d{1,4})(?:[x])(\\d{1,2})");
		boost::smatch match;

		std::string SearchString = tokens.back();


		if (boost::regex_search(SearchString, match, expr)) {
			dimension = boost::lexical_cast<int>(match[1]);
			depth = boost::lexical_cast<int>(match[2]);
			DomainTag = tokens.front();
			TextureName = tokens.at(1);
			




			//BindTo = new NS_ENG::ArrayTextureDesc();
			BindTo = new NS_ENG::TextureDesc();
			BindTo->h = dimension;
			BindTo->w = dimension;
			BindTo->internalFormat = Initial->internalFormat;
			BindTo->format = Initial->format;
			BindTo->type = Initial->type;
			BindTo->filter = Initial->filter;
			BindTo->MapContent = Initial->MapContent;

			//argPath.lexically_relative(boost::filesystem::path(Squiddy.ProjectFolder)).string()

			BindTo->Origin = std::string(__FUNCTION__) + 
				"Initialized by filename attributes: DomainTag: Seamless == " + DomainTag +
				"\n_NAME_: * == " +  StrContent + "\n" +
				"_SizeXDepth: 1024x24 == " + SearchString;


			BindTo->MapCategory = NS_ENG::MAP_ASSEMBLY_TYPE::ARRAY_TEXTURE;



			//BindTo->Name = DomainTag + "_" + StrContent + "_"+ (char*)dimension;
			BindTo->Name = DomainTag + "_" + StrContent + "_" + SearchString;

			AddToArray = true;

			//ArrayTextureDesc



		}
		



	}

	if(AddToArray == true)
		MapId = NS_ENG::MapAsset::LoadMaps(Initial, BindTo);
	else
		MapId = NS_ENG::MapAsset::LoadMaps(Initial, NULL);

	//if global
	if (AddToArray == true)
	{
		
		std::string GLSL_Variable = "baseArray" + StrContent + "0";

		base_buffer::AddGlobalTexture(GLSL_Variable, GL_TEXTURE_2D_ARRAY,
			NS_ENG::MapAsset::RetriveMap(MapId)->Map_TName,
			NS_ENG::MapAsset::RetriveMap(MapId)->Map_Layer, SortValue, true);


		base_buffer::DiffArrayMapTexure = NS_ENG::MapAsset::RetriveMap(MapId)->Map_TName;

	}


}

//I really REALLY want to add the same trick I did with the buffers to the packets, But not this year?!
size_t  DemoMeister::AddEffect(const std::string &TypeName,const std::string &Name)
{
	//Not to be overloaded, but work with tandem with the Production child.


	size_t idx = false;
	//Prototype names, Todo: look in declaration for links for possible solutions now just get on with it.
	
	
	idx = this->RetriveEffectID(TypeName, Name);
	
	
	if (idx == false)
	{

		NS_EFF::renderPacket* TemplateObject = (NS_EFF::renderPacket*)(g_factory.construct(TypeName));

		MasterList_Packets.push_back(sp_RenderPacket((TemplateObject)));
		//MasterList_Packets.push_back(sp_RenderPacket((TemplateObject->clone())));
		//MasterList_Packets.push_back(sp_RenderPacket(new NS_EFF::GeomPacket()));
		MasterList_Packets.back()->SetName(Name);
		//MasterList_Packets.back()->Init(ResolutionX, ResolutionY);
		idx = MasterList_Packets.size();

	}

	/*
	if (idx == false)
	{

	if(TypeName.compare("GeomPacket") == 0)
	{

		//MasterList_Packets.push_back(sp_RenderPacket(temp2));
		MasterList_Packets.push_back(sp_RenderPacket(new NS_EFF::GeomPacket()));
		//MasterList_Packets.push_back(sp_RenderPacket(new sp_RenderPacket(g_factory.construct(TypeName))));
		//MasterList_Packets.push_back(  *boost::make_shared()	<g_factory.construct("TypeName")>());
		MasterList_Packets.back()->SetName(Name);
		idx = MasterList_Packets.size();
	}
	if (TypeName.compare("RayMarcher") == 0)
	{

		
		MasterList_Packets.push_back(sp_RenderPacket(new NS_EFF::RayMarcher()));
		MasterList_Packets.back()->SetName(Name);
		idx = MasterList_Packets.size();
	}
	if (TypeName.compare("NullPacket") == 0)
	{

		
		MasterList_Packets.push_back(sp_RenderPacket(new NS_EFF::NullPacket()));
		MasterList_Packets.back()->SetName(Name);
		idx = MasterList_Packets.size();
	}
	if (TypeName.compare("PointLightPacket") == 0)
	{

		
		MasterList_Packets.push_back(sp_RenderPacket(new NS_EFF::PointLightPacket()));
		MasterList_Packets.back()->SetName(Name);
		idx = MasterList_Packets.size();
	}
	if (TypeName.compare("DirLightPacket") == 0)
	{
		
		
		MasterList_Packets.push_back(sp_RenderPacket(new NS_EFF::DirLightPacket()));
		MasterList_Packets.back()->SetName(Name);
		idx = MasterList_Packets.size();
	}
	if (TypeName.compare("aoPacket") == 0)
	{

		
		MasterList_Packets.push_back(sp_RenderPacket(new NS_EFF::aoPacket()));
		MasterList_Packets.back()->SetName(Name);
		idx = MasterList_Packets.size();
	}


	}
	*/
	return idx;

}


//some of the cleverest things I've ever done...should replicate....Even the Asset Monstrosity?!
//NOT THIS DECADE!
//But the ShaderPackets really should have the same thing
size_t DemoMeister::AddBuffer(const std::string & TypeName, const std::string & Name)
{
	size_t idx = false;

	idx = this->RetriveBufferID(TypeName, Name);

	if (idx == false)
	{

		base_buffer* TemplateObject = (base_buffer*)(g_factory.construct(TypeName));


		MasterList_Buffers.push_back(sp_Buffer((TemplateObject->clone())));
		MasterList_Buffers.back()->SetName(Name);
		MasterList_Buffers.back()->Init(ResolutionX, ResolutionY);
		idx = MasterList_Buffers.size();

	}
	return idx;
}

//Do we really need type?
size_t  DemoMeister::RetriveEffectID(const std::string &TypeName, const std::string &Name)
{
	//Need to specify both type and name
	//I should also have one that returns an array

	size_t idx = false;
	size_t idxCounter = 0;
	for (std::vector<sp_RenderPacket>::iterator iter = this->MasterList_Packets.begin(); iter != this->MasterList_Packets.end(); iter++)
	{
		std::string CurrName = (*iter)->GetName();
		idxCounter++;
		//if (0 == std::string("Base_Vert").compare(el_BaseShaders->Value()))
		if(0  ==  CurrName.compare(Name))
		{
			idx = idxCounter;
			break;
		}
		
		
	}

	return idx;
	//((NS_EFF::DeferredPipeMother*)(this->MasterList_Packets.at(PackID).get()))->;

}

//Yes I should use template A few different versions of Retrive and use the Container Type,
//Maybe even the concrete type as return

//Would that mean these has to be static methods?
//Might as well actually, would be nice to have direct call to the containers in BaseBuffer
//But the architecture(mess) I made means it really should not have public acces to those.

//stupid name, Packets are Packets Effects is a term I want to use elsewhere.
//or wait...eh...NOT THIS YEAR!
sp_RenderPacket  DemoMeister::RetriveEffect(size_t idx)
{
	
	if (this->MasterList_Packets.size() < idx || idx == 0)
		return NULL;
	//Should put the idx in an assert.



	return this->MasterList_Packets.at(idx-1);

}



//Experiments I did before I learned the CRTP trick, the factory works well with that...add to packets...
//BUT NOT THIS YEAR!
/*
template <class T>
T*  DemoMeister::RetriveEffect(const std::string & TypeName, const std::string & Name)
{


	size_t idx = this->RetriveEffectID(TypeName, Name);
	//there are better ways then this.
	if (this->MasterList_Packets.size() < idx || idx == 0)
		return NULL;
	//Should put the idx in an assert.


	//DemoMeister::g_factory.construct(TypeName);
	

	T* Test = boost::static_pointer_cast<DemoMeister::g_factory.construct(TypeName)>this->MasterList_Packets.at(idx - 1);

	//return boost::static_pointer_cast<DemoMeister::g_factory.construct(TypeName)>this->MasterList_Packets.at(idx - 1);

	return boost::static_pointer_cast<T*>(this->MasterList_Packets.at(idx - 1).get());
	//boost::static_pointer_cast<NS_EFF::RayMarcher>
	//return this->MasterList_Packets.at(idx - 1);
	//((NS_EFF::DeferredPipeMother*)(this->MasterList_Packets.at(PackID).get()))->;

}
*/



//TEMPLATES MOTHER FUCKERS! Bah, I got 3 monster containers must find a way to unite the getters and setters
sp_RenderPacket  DemoMeister::RetriveEffect(const std::string & TypeName, const std::string & Name)
{


	size_t idx = this->RetriveEffectID(TypeName, Name);
	//there are better ways then this.
	if (this->MasterList_Packets.size() < idx || idx == 0)
		return NULL;
	//Should put the idx in an assert.



	return this->MasterList_Packets.at(idx - 1);

}


size_t DemoMeister::RetrivePassID(const std::string & TypeName, const std::string & Name)
{
	size_t idx = false;
	size_t idxCounter = 0;
	for (std::vector<sp_PassItemnator>::iterator iter = this->MasterList_Passes.begin(); iter != this->MasterList_Passes.end(); iter++)
	{
		std::string CurrName = (*iter)->GetName();
		idxCounter++;
		
		if (0 == CurrName.compare(Name))
		{
			idx = idxCounter;
			break;
		}


	}

	return idx;
}


/* ugh...sorry i was drunk and tired...and again 3 seperate getters per! 3 seperater containers for 3 seperate classes......I'M AN IDIOT!
sp_b  DemoMeister::RetrivePass(const std::string & TypeName, const std::string & Name)
{
VARIDIC!

	size_t idx = this->RetriveEffectID(TypeName, Name);
	//there are better ways then this.
	if (this->MasterList_Packets.size() < idx || idx == 0)
		return NULL;
	//Should put the idx in an assert.


	//return this->MasterList_Packets.at(idx);
	return this->MasterList_Packets.at(idx - 1);
	//((NS_EFF::DeferredPipeMother*)(this->MasterList_Packets.at(PackID).get()))->;

}
*/


/* TEMPLATE YOU MOTHER FUCKER! Getters and setters are for the WEAK! especially with 3 containers containing 3 seperate classes!

sp_RenderPacket  DemoMeister::RetriveEffect(const std::string & TypeName, const std::string & Name)
{


size_t idx = this->RetriveEffectID(TypeName, Name);
//there are better ways then this.
if (this->MasterList_Packets.size() < idx || idx == 0)
return NULL;
//Should put the idx in an assert.


//return this->MasterList_Packets.at(idx);
return this->MasterList_Packets.at(idx - 1);
//((NS_EFF::DeferredPipeMother*)(this->MasterList_Packets.at(PackID).get()))->;

}
*/


sp_PassItemnator DemoMeister::RetrivePass(size_t idx)
{
	if (this->MasterList_Passes.size() < idx || idx == 0)
		return NULL;


	return this->MasterList_Passes.at(idx - 1);
}

sp_PassItemnator DemoMeister::RetrivePass(const std::string & TypeName, const std::string & Name)
{

	size_t idx;
	idx = this->RetrivePassID(TypeName, Name);

	if (this->MasterList_Passes.size() < idx || idx == 0)
		return NULL;

	return this->MasterList_Passes.at(idx - 1);
}



size_t DemoMeister::RetriveBufferID(const std::string & TypeName, const std::string & Name)
{
	size_t idx = false;
	size_t idxCounter = 0;
	for (std::vector<sp_Buffer>::iterator iter = this->MasterList_Buffers.begin(); iter != this->MasterList_Buffers.end(); iter++)
	{
		std::string CurrName = (*iter)->GetName();
		idxCounter++;
		if (0 == CurrName.compare(Name))
		{
			idx = idxCounter;
			break;
		}


	}

	return idx;
}


sp_Buffer DemoMeister::RetriveBuffer(size_t idx)
{
	if (this->MasterList_Buffers.size() < idx || idx == 0)
	{
		return NULL;
	}

	return this->MasterList_Buffers.at(idx - 1);
}

/*
void DemoMeister::AddAsset()
{
}

void DemoMeister::RetriveAsset()
{
}

void DemoMeister::AddMaterial()
{
}

void DemoMeister::RetriveMaterial()
{
}
*/
//bool DemoMeister::InitEffects(const std::string & Type = "", const std::string & Name = "", size_t idx = 0)

//https://en.wikipedia.org/wiki/Variadic_template#C.2B.2B11
//Must have

bool DemoMeister::InitEffects(const std::string &TypeName = "", const std::string &Name = "", size_t idx = 0)
{
	
	bool Result = false;
	bool All = false;

	//bool ByName = Name.empty() ? true : false;
	//bool ByType = Type.empty() ? true : false;

	bool ByName = Name.empty() ? false : true;
	bool ByType = TypeName.empty() ? false : true;


	std::string CurrName = "";
	std::string CurrType = "";

	size_t idxCounter = 0;

	if (idx != 0)
	{
		CurrName = RetriveEffect(idx)->GetName();
		CurrType = RetriveEffect(idx)->GetType();

		std::cout << idx <<
		"===Effect Init====================" << std::endl <<
		"Initialising : " << CurrType << "::" << CurrName << std::endl << 
		"==================================" << std::endl << std::endl;


		Result = RetriveEffect(idx)->Init();

		std::cout << "Status of: " << CurrType << "::" << CurrName << " is = " << Result << std::endl << std::endl << std::endl;

	}
	else
	{ 
	
		
		if (ByName == false && ByType == false)
			All = true;


	
		for (std::vector<sp_RenderPacket>::iterator iter = this->MasterList_Packets.begin(); iter != this->MasterList_Packets.end(); iter++)
	
		{
			idxCounter++;
			CurrName = (*iter)->GetName();
			CurrType = (*iter)->GetType();

			if (All == true)
			{
				std::cout << idxCounter <<
				"===Effect Init====================" << std::endl <<
				"Initialising : " << CurrType << "::" << CurrName << std::endl <<
				"==================================" << std::endl << std::endl;

				Result = (*iter)->Init();

				std::cout << "Status of: " << CurrType << "::" << CurrName << " is = " << Result << std::endl << std::endl << std::endl;
				continue;
			}


		
			idxCounter++;
		
			//if (0 == std::string("Base_Vert").compare(el_BaseShaders->Value()))
		
			if (ByName == true && 0 == CurrName.compare(Name))
			{
				std::cout << idxCounter <<
					"===Effect Init====================" << std::endl <<
					"Initialising : " << CurrType << "::" << CurrName << std::endl <<
					"==================================" << std::endl << std::endl;

				Result = (*iter)->Init();
				std::cout << "Status of: " << CurrType << "::" << CurrName << " is = " << Result << std::endl << std::endl << std::endl;
				break;
		
			}
			
			if (ByType == true && 0 == CurrName.compare(Name))
			{
				std::cout << idxCounter <<
				"===Effect Init====================" << std::endl <<
				"Initialising : " << CurrType << "::" << CurrName << std::endl <<
				"==================================" << std::endl << std::endl;

				Result = (*iter)->Init();
				std::cout << "Status of: " << CurrType << "::" << CurrName << " is = " << Result << std::endl << std::endl << std::endl;

				continue;

			}


	}
	}



	return Result;
}


/*


void DemoMeister::HackerSpace()
{
}





void DemoMeister::PreInit()
{
}

void DemoMeister::Init()
{
}

//hmm Maybe needed
void DemoMeister::AfterInit()
{


	//sync_device *pRocket = stuff.rocket;

	//rocket 


	//if (!(::rocket))
	//	cout << "out of memory?" << endl;



//#ifndef SYNC_PLAYER
//	(sync_connect(stuff.rocket, "localhost", SYNC_DEFAULT_PORT));
//	//	cout << "failed to connect to host" << endl;
//#endif
	
	//stuff.SortTracks();
	}
	*/
	/* get tracks */
	//clear_r = sync_get_track(rocket, "clar.r");
	//clear_g = sync_get_track(rocket, "clear.g");
	//clear_b = sync_get_track(rocket, "clear.b");
	//cam_rot = sync_get_track(rocket, "cam.rot"),
	//cam_dist = sync_get_track(rocket, "cam.dist");

	/* let's roll! */
	







/*
void DemoMeister::InitLights()
{


}



void DemoMeister::RenderScene()
{


}
*/
