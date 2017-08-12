
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
	
	temp->Init(ResolutionX, ResolutionY);
	temp2->Init(ResolutionX, ResolutionY);
	MasterList_Buffers.push_back(temp);
	MasterList_Buffers.push_back(temp2);
}



void DemoMeister::AddPass(const std::string &filename)
{
	
	MasterList_Passes.push_back(new PassItemnator());
	
	MasterList_Passes.back()->load(filename);





}

void DemoMeister::AddNode()
{
}

void DemoMeister::AddEffect()
{
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
