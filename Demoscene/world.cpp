
#include "world.h"
//#include <iostream>

//#define DegToRad 0.01745329f

//GLfloat turn = 0.0;
//GLuint VertexArrayID;

//HSTREAM stream;

//boost::shared_ptr<NS_SG::modelNode> mn_ShowPiece



PassItemnator::PassItemnator() {


}

int PassItemnator::load(const std::string &filename)
{
	HumbleXML = boost::filesystem::path(filename.c_str());
	//HumbleXML.remove_leaf();
	//HumbleXML.append("DemoMeister.ini");

	HumbleXML.normalize();
	//if (!HumbleIni.is_complete());
	//return;
	bool test = HumbleXML.is_complete();
	// Create empty property tree object
	//using boost::property_tree::ptree;
	//ptree pt;
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
	
	this->Name = el_PassInfo->Attribute("name");
	this->PacketType = el_PassInfo->Attribute("packet");
	this->PassValue = el_PassInfo->IntAttribute("PassValue");
	this->BufferType = el_PassInfo->Attribute("Buffer");
	this->BufferLocalPassValue = el_PassInfo->IntAttribute("BufferLocalPass");
	//PassItem::read_xml(HumbleXML.string(), PassData);


	tinyxml2::XMLElement *el_BaseShaders = el_PassInfo->FirstChildElement();

	

	hasVertexShader = el_BaseShaders->BoolAttribute("vertex");
	hasGeometryShader = el_BaseShaders->BoolAttribute("geometry");
	hasFragmentShader = el_BaseShaders->BoolAttribute("fragment");

	el_BaseShaders = el_BaseShaders->FirstChildElement();
	if (hasVertexShader) {
		

		if(0  == std::string("Base_Vert").compare(el_BaseShaders->Value()))
		{ 
			this->VertexCode = new NS_ENG::NS_SHADER::BaseShaderItem(
				
				Squiddy.FindAndRegister( el_BaseShaders->Attribute("Path")),
					el_BaseShaders->Attribute("Target"), NS_ENG::NS_SHADER::BaseVertex
			);
		
		}

	}

	if (hasGeometryShader) {
		el_BaseShaders = el_BaseShaders->NextSiblingElement();

		if (0 == std::string("Base_Geom").compare(el_BaseShaders->Value()))
		{
			this->GeometryCode = new NS_ENG::NS_SHADER::BaseShaderItem(

				Squiddy.FindAndRegister(el_BaseShaders->Attribute("Path")),
				el_BaseShaders->Attribute("Target"), NS_ENG::NS_SHADER::BaseGeometry);

		}
	}	
	if (hasFragmentShader) {
		el_BaseShaders = el_BaseShaders->NextSiblingElement();

		if (0 == std::string("Base_Frag").compare(el_BaseShaders->Value()))
		{
			this->FragmentCode = new NS_ENG::NS_SHADER::BaseShaderItem(

				Squiddy.FindAndRegister(el_BaseShaders->Attribute("Path")),
				el_BaseShaders->Attribute("Target"), NS_ENG::NS_SHADER::BaseFragment);

		}

	}





	return Status;
}




DemoMeister::DemoMeister() //public context()
{
	
	//BufferContainer.push_back()
	
	o_loader = compoPointer(new NS_SG::composite("root"));
	
	//o_loader->addChild(new NS_SG::objTransform("Test"));

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
	GBuffer *temp = new GBuffer();
	AoBuffer *temp2 = new AoBuffer();
	//boost::shared_ptr < MapAsset >(new FileTexture)
	temp->Init(ResolutionX, ResolutionY);
	temp2->Init(ResolutionX, ResolutionY);
	MasterList_Buffers.push_back(sp_Buffer(temp));
	MasterList_Buffers.push_back(sp_Buffer(temp2));


}



void DemoMeister::AddPass(const std::string &filename)
{
	
	MasterList_Passes.push_back(sp_PassItemnator(new PassItemnator()));
	
	MasterList_Passes.back()->load(filename);

	//MasterList_Passes.back()->



}

void DemoMeister::AddNode()
{

}



size_t  DemoMeister::AddEffect(const std::string &Type,const std::string &Name)
{
	size_t idx = false;
	//Prototype names, Todo: look in declaration for links for possible solutions now just get on with it.
	if(Type.compare("GeomPacket") == 0)
	{
	
	
	}


	return idx;

}


size_t  DemoMeister::RetriveEffectID(const std::string &Type, const std::string &Name)
{
	size_t idx;
	for (std::vector<sp_RenderPacket>::iterator iter = this->MasterList_Packets.begin(); iter != this->MasterList_Packets.end(); iter++)
	{

		*(*iter);
	}

	return false;
	//((NS_EFF::DeferredPipeMother*)(this->MasterList_Packets.at(PackID).get()))->;

}

//Yes I should use template A few different versions of Retrive and use the Container Type,
//Maybe even the concrete type as return

//Would that mean these has to be static methods?
//Might as well actually, would be nice to have direct call to the containers in BaseBuffer
//But the architecture(mess) I made means it really should not have public acces to those.


sp_RenderPacket  DemoMeister::RetriveEffect(size_t idx)
{

	//there are better ways then this.
	if (this->MasterList_Packets.size() <= idx)
		return NULL;

	return this->MasterList_Packets.at(idx);

	//((NS_EFF::DeferredPipeMother*)(this->MasterList_Packets.at(PackID).get()))->;

}


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
