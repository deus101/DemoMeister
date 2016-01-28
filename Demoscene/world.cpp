
#include "world.h"
#include <iostream>

#define DegToRad 0.01745329f

GLfloat turn = 0.0;
GLuint VertexArrayID;

HSTREAM stream;


world::world() //public context()
{


}



void world::DrawStage()
{


}




void world::HyperHex()
{



	GLfloat S;
	GLfloat h;


}


void world::AfterInit()
{

	if (!BASS_Init(-1, 44100, 0, 0, 0))
		std::cout << "failed to init bass" << std::endl;
	stream = BASS_StreamCreateFile(false, "bf.ogg", 0, 0,
		BASS_STREAM_PRESCAN);
	if (!stream)
		std::cout << "failed to open tune" << std::endl;

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
	BASS_Start();
	BASS_ChannelPlay(stream, false);


}
void world::InitLights()
{


}



void world::RenderScene()
{


}

