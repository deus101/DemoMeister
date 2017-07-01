
#include "world.h"
//#include <iostream>

//#define DegToRad 0.01745329f

//GLfloat turn = 0.0;
//GLuint VertexArrayID;

//HSTREAM stream;

//boost::shared_ptr<NS_SG::modelNode> mn_ShowPiece
DemoMeister::DemoMeister() //public context()
{
	
	//BufferContainer.push_back()
	
	o_loader = compoPointer(new NS_SG::composite("root"));
	
	//o_loader->addChild(new NS_SG::objTransform("Test"));

}

void DemoMeister::AddPass()
{
	GBuffer *temp = new GBuffer();
	AoBuffer *temp2 = new AoBuffer();

	temp->Init(ResolutionX, ResolutionY);
	temp2->Init(ResolutionX, ResolutionY);
	BufferContainer.push_back(temp);
	BufferContainer.push_back(temp2);
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

void DemoMeister::HackerSpace()
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


	/* get tracks */
	//clear_r = sync_get_track(rocket, "clar.r");
	//clear_g = sync_get_track(rocket, "clear.g");
	//clear_b = sync_get_track(rocket, "clear.b");
	//cam_rot = sync_get_track(rocket, "cam.rot"),
	//cam_dist = sync_get_track(rocket, "cam.dist");

	/* let's roll! */
	


}
/*
void DemoMeister::InitLights()
{


}



void DemoMeister::RenderScene()
{


}
*/
