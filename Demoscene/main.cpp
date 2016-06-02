#include "world.h"
#include <iostream>
#include "bass.h"

#include "sync.h"
//world as a scene object and going through a sceneloader?
#include "Rendrer\context.h"
#include "Engine\rendrer.h"
#include "Engine\GridPoints.h"
#include "SceneGraph\gridNode.h"

#include "SceneGraph\sceneparser.h"
#include "SceneGraph\assetNode.h"
#include "SceneGraph\modelNode.h"
#include "SceneGraph\dirLightNode.h"
#include "SceneGraph\pointLightNode.h"
#include "SceneGraph\dirLightNode.h"
#include "SceneGraph\targetNode.h"
//NS_REND::context *mContext = NULL;
//NS_ENG::rendrer *mRender = NULL;

//eh
#include "Effect\aoPacket.h"



HSTREAM stream;

sync_device *rocket;

const struct sync_track *plane_Pos_X, *plane_Pos_Y, *plane_Pos_Z, *plane_Rot_X, *plane_Rot_Y, *plane_Rot_Z, *plane_Sca_X, *plane_Sca_Y, *plane_Sca_Z;
const struct sync_track *lit_Pos_X, *lit_Pos_Y, *lit_Pos_Z;
const struct sync_track *cam_Pos_X, *cam_Pos_Y, *cam_Pos_Z, *cam_Rot_X, *cam_Rot_Y, *cam_Rot_Z;


//simple int
const struct sync_track *gridDrop;
const struct sync_track *dodoOpen;


const struct sync_track *TrackPart;

const struct sync_track *UtilityTrack;


int partCurrent = -1;

int GridEffCurr = 0;
float DodoOpenCurr;


NS_SG::objectAnim PlaneSync, CameraSync;

NS_SG::composite *ptrComp;
NS_SG::objTransform *ptrCamTran;
NS_SG::objTransform *ptrLitPlan;

NS_SG::objTransform *ptrTranProt;
NS_SG::objTransform *ptrE_1_6;
NS_SG::objTransform *ptrE_1_04;
NS_SG::objTransform *ptrE_1_08;

//on 1_6
NS_SG::objTransform *ptrE_2_10;
NS_SG::objTransform *ptrE_2_02;

//on 2_02
NS_SG::objTransform *ptrE_3_02;
//on 3_02
NS_SG::objTransform *ptrE_4_04;

//on 2_10
NS_SG::objTransform *ptrE_3_10;

//on 3_10
NS_SG::objTransform *ptrE_4_08;


//fuck it half is normal
//top lid
NS_SG::objTransform *ptrE_4_02_half;
NS_SG::objTransform *ptrE_2_08_half;




NS_SG::objTransform *Ptr_t_grid;

NS_SG::gridNode *ptrGridNode;




NS_SG::objTransform * Ptr_t_ShowPiece;


static const float bpm = 150.0f; /* beats per minute */
static const int rpb = 8; /* rows per beat */
static const double row_rate = (double(bpm) / 60) * rpb;


static double bass_get_row(HSTREAM h)
{
	QWORD pos = BASS_ChannelGetPosition(h, BASS_POS_BYTE);
	//add a small delay here
	double time = BASS_ChannelBytes2Seconds(h, pos);
	return time * row_rate;
}

#ifndef SYNC_PLAYER

static void bass_pause(void *d, int flag)
{
	HSTREAM h = *((HSTREAM *)d);
	if (flag)
		BASS_ChannelPause(h);
	else
		BASS_ChannelPlay(h, false);
}

static void bass_set_row(void *d, int row)
{
	HSTREAM h = *((HSTREAM *)d);
	QWORD pos = BASS_ChannelSeconds2Bytes(h, row / row_rate);
	BASS_ChannelSetPosition(h, pos, BASS_POS_BYTE);
}

static int bass_is_playing(void *d)
{
	HSTREAM h = *((HSTREAM *)d);
	return BASS_ChannelIsActive(h) == BASS_ACTIVE_PLAYING;
}

static struct sync_cb bass_cb = {
	bass_pause,
	bass_set_row,
	bass_is_playing
};

#endif


void ActionPart(int part)
{
	if (partCurrent != part)
	{
		partCurrent = part;


		if( part == 0)
		{
			//ptrLitField->setPosition(NS_VEC::VEC3(0.0, -100.0f, 40.0f));
			//Ptr_t_grid->setPosition(NS_VEC::VEC3(0.0, 100.0f, 40.0f));
		
		}

		if (part == 1)
		{
			//Ptr_t_grid->setPosition(NS_VEC::VEC3(0.0, -4, 40.0f));
			//ptrLitField->setPosition(NS_VEC::VEC3(0, -4, 40));


		}

		if (part == 2)
		{
			//Ptr_t_grid->setPosition(NS_VEC::VEC3(0.0, -4, 40.0f));
			//ptrLitField->setPosition(NS_VEC::VEC3(0, -4, 40));
			
			Ptr_t_ShowPiece->setPosition(NS_VEC::VEC3(0.0f, 200.0f, 0.0f));

		}

		if (part == 3)
		{
			//Ptr_t_grid->setPosition(NS_VEC::VEC3(0.0, -4, 40.0f));
			//ptrLitField->setPosition(NS_VEC::VEC3(0, -4, 40));

			Ptr_t_ShowPiece->setPosition(NS_VEC::VEC3(0.0f, 0.0f, 0.0f));


			

		}


		if (part == 6)
		{
			#ifdef SYNC_PLAYER
			LeaveMainLoop();
			#endif


		}



	}


}


void GridBeat(int func)
{
	if (GridEffCurr != func)
	{
		//1 is red
		GridEffCurr = func;
		if (func == 1)
		{
		ptrGridNode->Grid->CreateGridActor(NS_VEC::VEC2(5.5f, 5.5f), NS_VEC::VEC3(1.0f, 0.0f, 0.0f), 1.0f);

		}
		//2 is blue
		if (func == 2)
		{
			ptrGridNode->Grid->CreateGridActor(NS_VEC::VEC2(-6.0f, 16.0f), NS_VEC::VEC3(0.0f, 0.0f, 1.0f), 1.0f);

		}
		//3 is green
		if (func == 3)
		{
			ptrGridNode->Grid->CreateGridActor(NS_VEC::VEC2(5.0f, -18.0f), NS_VEC::VEC3(0.0f, 1.0f, 0.0f), 1.0f);
			
		}

		//4 is yellow
		if (func == 4)
		{
			ptrGridNode->Grid->CreateGridActor(NS_VEC::VEC2(-5.0f, -5.0f), NS_VEC::VEC3(1.0f, 1.0f, 0.0f), 1.0f);

		}

		else if (func == 0)
		{
			//ehm pass

		}
	}



}



void Sync()
{
	
	double row = bass_get_row(stream);
#ifndef SYNC_PLAYER
	sync_update(rocket, (int)floor(row), &bass_cb, (void *)&stream);
#endif
		
		//sync_connect(rocket, "localhost", SYNC_DEFAULT_PORT);


	ActionPart(int(sync_get_val(TrackPart, row)));




	//float(sync_get_val(cam_rot, row))
	//NS_VEC::VEC3 test =  NS_VEC::VEC3(float(sync_get_val(cam_Pos_X, row)), float(sync_get_val(cam_Pos_Y, row)), float(sync_get_val(cam_Pos_Z, row)));
	//cout << "testXYZ cam pos" << test.X << "-" << test.Y << "-" << test.Z << endl;

	//NS_VEC::VEC3 teasdst = NS_VEC::VEC3(float(sync_get_val(plane_Sca_X, row)), float(sync_get_val(plane_Sca_X, row)), float(sync_get_val(plane_Sca_X, row)));
	//cout << "testXYZ plan sca" << teasdst.X << "-" << teasdst.Y << "-" << teasdst.Z << endl;
	//CameraSync.setPosKeyFrame(row, NS_VEC::VEC3(float(sync_get_val(cam_Pos_X, row)), float(sync_get_val(cam_Pos_Y, row)), float(sync_get_val(cam_Pos_Z, row))));
	//CameraSync.setRotKeyFrame(row, NS_VEC::QUAT(0.0f, 0.0f, 0.0f));
	//CameraSync.setScaleKeyFrame(row, NS_VEC::VEC3(1.0f, 1.0f, 1.0f));
	//PlaneSync.setPosKeyFrame(row, NS_VEC::VEC3(float(sync_get_val(plane_Pos_X, row)), float(sync_get_val(plane_Pos_Y, row)), float(sync_get_val(plane_Pos_Z, row))));
	//PlaneSync.setRotKeyFrame(row, NS_VEC::QUAT(float(sync_get_val(plane_Rot_X, row)), float(sync_get_val(plane_Rot_Y, row)), float(sync_get_val(plane_Rot_Z, row))));

	//ptrTranProt->setPosition(NS_VEC::VEC3(float(sync_get_val(plane_Pos_X, row)), float(sync_get_val(plane_Pos_Y, row)), float(sync_get_val(plane_Pos_Z, row))));
	//
	ptrCamTran->setPosition(NS_VEC::VEC3(float(sync_get_val(cam_Pos_X, row)), float(sync_get_val(cam_Pos_Y, row)), float(sync_get_val(cam_Pos_Z, row))));
	ptrCamTran->setRotation(NS_VEC::QUAT(float(sync_get_val(cam_Rot_X, row)), float(sync_get_val(cam_Rot_Y, row)), float(sync_get_val(cam_Rot_Z, row))));

	ptrTranProt->setRotation(NS_VEC::QUAT(float(sync_get_val(plane_Rot_X, row)), float(sync_get_val(plane_Rot_Y, row)), float(sync_get_val(plane_Rot_Z, row))));
	ptrTranProt->setPosition(NS_VEC::VEC3(float(sync_get_val(plane_Pos_X, row)), float(sync_get_val(plane_Pos_Y, row)), float(sync_get_val(plane_Pos_Z, row))));
	ptrTranProt->setScale(NS_VEC::VEC3(float(sync_get_val(plane_Sca_X, row)), float(sync_get_val(plane_Sca_Y, row)), float(sync_get_val(plane_Sca_Z, row))));

	ptrLitPlan->setPosition(NS_VEC::VEC3(float(sync_get_val(lit_Pos_X, row)), float(sync_get_val(lit_Pos_Y, row)), float(sync_get_val(lit_Pos_Z, row))));

	


	if (partCurrent == 1)
	{
		
	}


	
	//GridBeat(int(sync_get_val(gridDrop, row)));


	//if (partCurrent == 3)
		
	
	
}





//I need some better timer func but leave it for now
void TimerFunction(int)
{
	
	//glutPostRedisplay();
	//glutTimerFunc(3, TimerFunction, 1);

}



//Dont really need this, kept in context.cpp
void ChangeSize(int w, int h)
{


	ChangeSize(w, h);
	//GLfloat fAspect;

	//if (h == 0)
	//	h = 1;
	ResizeBuffer = TRUE;
	//gl::vie
	//startskudd for omskriving 

	//gl::Viewport(0, 0, (GLsizei)w, (GLsizei)h);

	//fAspect = (GLfloat)w / (GLfloat)h;

	//cout << "Changed Screen size!" << endl;
	//std::

	//gluPerspective(35.0f, fAspect, 1.0f, 200.0f);


}




void SetupRC()
{
//I used to keep the OpenGL initialisers here
}

void KeyboardCB(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key) {
	case GLFW_KEY_ESCAPE:
	case GLFW_KEY_Q:
		LeaveMainLoop();
		break;
	case GLFW_KEY_SPACE:
		std::cout << "Space Pressed " <<  std::endl;
	//default:
	//	m_pGameCamera->OnKeyboard(OgldevKey);
	}
}




int main(int argc, char** argv)
{
	int Xres = 1280;
	int Yres = 720;

	bool FS = false;

	//mContext = new NS_REND::context();
	
	for (int i = 0; i < argc; i++)
	{
		string Argument = argv[i];

		if (Argument.compare("-X") == 0)
		{
			string s_X = argv[i + 1];
			Xres = stoi(s_X);

		}
		if (Argument.compare("-Y") == 0)
		{
			string s_Y = argv[i + 1];
			Yres = stoi(s_Y);
		}
		if (Argument.compare("-FS") == 0)
		{
			FS = true;
		}
	}
	
	//overide remember to remove
	std::cout << "Initialising at resolution " << Xres << "X" << Yres << "  Fullscreen: " << FS << std::endl;
	

#ifndef SYNC_PLAYER
	Xres = 1280;
	Yres = 720;
	FS = false;
#endif

	bool success = Init(argc, argv, true, false, Xres, Yres, FS, "Deus's Ex Machine");

	
	std::cout << "Result of init windows: " << success << std::endl;



	//1600 900

	//std::cout << "X! : " << pWidth  << std::endl;
	//std::cout << "Y! : " << pHeight  << std::endl;
	glViewport(0, 0, (GLsizei)Xres, (GLsizei)Yres);



	//SetupRC();
	//DO IT! TO IT!

//-------------------The effects packets 
	NS_EFF::GeomPacket e_geom = NS_EFF::GeomPacket();


	NS_EFF::PointLightPacket e_point = NS_EFF::PointLightPacket();

	NS_EFF::NullPacket e_null = NS_EFF::NullPacket();

	NS_EFF::DirLightPacket e_dir = NS_EFF::DirLightPacket();

	NS_EFF::HeightMapPacket e_hmap = NS_EFF::HeightMapPacket();


	NS_EFF::aoPacket e_ao_Pass = NS_EFF::aoPacket();



	std::cout << "Status of geometry effect is: " << e_geom.Init() << std::endl;

	e_geom.Enable();
	e_geom.SetColorTextureUnit(COLOR_TEXTURE_UNIT_INDEX);


	//ikke gi opp
	//std::cout << "Status of grid geometry effect is: " << e_hmap.Init() << std::endl;



	std::cout << "Status of Ambien Occulsion effect/pass is: " << e_ao_Pass.Init() << std::endl;
	e_ao_Pass.Enable();
	//e_ao_Pass.SetPositionTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	//e_ao_Pass.SetNormalTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);

	e_ao_Pass.SetScreenSize(Xres, Yres);

	e_ao_Pass.InitKernel();
	e_ao_Pass.InitNoise();

	e_ao_Pass.SetPositionTextureUnit((UINT32)0);
	e_ao_Pass.SetNormalTextureUnit((UINT32)2);
	e_ao_Pass.SetNoiseTextureUnit((UINT32)3);
	std::cout << "Status of point light effect is: " << e_point.Init() << std::endl;

	e_point.Enable();

	e_point.SetPositionTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	e_point.SetColorTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	e_point.SetNormalTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	e_point.SetScreenSize(Xres, Yres);

	//e_point.SetScreenSize(1600, 900);
	
	std::cout << "Status of dir light effect is: " << e_dir.Init() << std::endl;

	e_dir.Enable();
	e_dir.SetPositionTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	e_dir.SetColorTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	e_dir.SetNormalTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);

	
	//e_dir.SetScreenSize(1600, 900);
	e_dir.SetScreenSize(Xres, Yres);

	M3DMatrix44f WVP;
	m3dLoadIdentity44(WVP);
	e_dir.SetWVP(WVP);


	std::cout << "Status of null effect is: " << e_null.Init() << std::endl;

//--------------scene node that goes into scenerendrer
	//scene parser does not work because I suck at boost
	//NS_SG::composite  *test_Loader = NS_SG::parseScene("TestScene.xml");


	boost::shared_ptr<NS_SG::composite> o_loader(new NS_SG::composite("lader"));


//-------------Greets Assets



	//plane add as child later on the dodo

	NS_ENG::model m_fly("Mesh/fixedP38.obj", "Mesh/fixedP38.mtl");

	boost::shared_ptr<NS_SG::modelNode> mn_ShowPiece(new NS_SG::modelNode("ShowPiece", &m_fly, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> tran_ShowPiece(new NS_SG::objTransform("tran_ShowPiece"));

	tran_ShowPiece->addChild(mn_ShowPiece.get());

	Ptr_t_ShowPiece = tran_ShowPiece.get();


	tran_ShowPiece->setPosition(NS_VEC::VEC3(0.0f, 0.0f, 0.0f));
	tran_ShowPiece->setScale(NS_VEC::VEC3(1.0f, 1.0f, 1.0f));


//------------UnderGround Scene

	
	/*
	NS_ENG::model m_sponza("Mesh/sponza.obj", "Mesh/sponza.mtl");
	boost::shared_ptr<NS_SG::modelNode> mn_sponza(new NS_SG::modelNode("Scene_sponza", &m_sponza, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> tran_sponza(new NS_SG::objTransform("tran_sponza"));
	tran_sponza->addChild(mn_sponza.get());
	tran_sponza->setScale(NS_VEC::VEC3(1.0f, 1.0f, 1.0f));
	tran_sponza->setPosition(NS_VEC::VEC3(0.0f, 0.0f, 0.0f));

	o_loader->addChild(tran_sponza.get());
	*/
	

	
	NS_ENG::model m_sponza("Mesh/sti.obj", "Mesh/sti.mtl");
	boost::shared_ptr<NS_SG::modelNode> mn_sponza(new NS_SG::modelNode("Scene_sponza", &m_sponza, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> tran_sponza(new NS_SG::objTransform("tran_sponza"));
	tran_sponza->addChild(mn_sponza.get());
	tran_sponza->setScale(NS_VEC::VEC3(0.1f, 0.1f, 0.1f));
	tran_sponza->setPosition(NS_VEC::VEC3(0.0f, 0.0f, 0.0f));

	o_loader->addChild(tran_sponza.get());
	

//-------------------------------------me


	NS_ENG::model m_protagonist("Mesh/PentagonBase.obj", "Mesh/PentagonBase.mtl");

	NS_ENG::model m_P_Arm("Mesh/PentagonArm.obj", "Mesh/PentagonArm.mtl");

	//NS_ENG::model m_P_Half_Arm("Mesh/PentagonHalfArm.obj", "Mesh/PentagonHalfArm.mtl");



	//mn is for model node

	boost::shared_ptr<NS_SG::objTransform> tran_protagonist(new NS_SG::objTransform("tran_protoganist"));
	tran_protagonist->setPosition(NS_VEC::VEC3(0.0f, -1.0f, 0.0f));
	


	ptrTranProt = tran_protagonist.get();
	

	tran_protagonist->addChild(tran_ShowPiece.get());
	
	/*
	boost::shared_ptr<NS_SG::targetTransform> target_look(new NS_SG::targetTransform("tar_look"));
	boost::shared_ptr<NS_SG::objTransform> t_look(new NS_SG::objTransform("t_look"));


	boost::shared_ptr<NS_SG::modelNode> lookTest(new NS_SG::modelNode("looker", &m_protagonist, &e_geom));
	target_look->addChild(lookTest.get());
	t_look->setPosition(NS_VEC::VEC3(0.0f, 0.0f, -5.0f));
	t_look->setScale(NS_VEC::VEC3(1.0f, 1.0f, 1.0f));
	target_look->setTarget(tran_protagonist.get());
	
	t_look->addChild(target_look.get());

	o_loader->addChild(t_look.get());
	*/
//-----------------------------Grid


	/*
		boost::shared_ptr<NS_SG::objTransform> t_grid(new NS_SG::objTransform("t_grid"));
		t_grid->setPosition(NS_VEC::VEC3(0, 1, 0));
		NS_ENG::GridPoints m_grid10x10(90, 90, 1.0f);
		boost::shared_ptr<NS_SG::gridNode> mn_grid(new NS_SG::gridNode("grid", &m_grid10x10, &e_hmap));
		
		ptrGridNode = mn_grid.get();

		t_grid->addChild(mn_grid.get());

		Ptr_t_grid = t_grid.get();

		o_loader->addChild(t_grid.get());

		*/


//--------------------Camera 
	//1 for nowf
	

	boost::shared_ptr<NS_SG::camera> kambot(new NS_SG::camera("kambot"));


	boost::shared_ptr<NS_SG::objTransform> tran_kambot(new NS_SG::objTransform("tran_kambot"));
	boost::shared_ptr<NS_SG::targetTransform> target_kambot(new NS_SG::targetTransform("target_kambot"));
	boost::shared_ptr<NS_SG::objTransform> pivot_kambot(new NS_SG::objTransform("pivot_kambot"));

	
	
	//target_kambot->setTarget(mn_protoganist.get());

	target_kambot->addChild(kambot.get());
	//target_kambot->addChild(target_pivot.get());

	//target_pivot->addChild(kambot.get());





	tran_kambot->setPosition(NS_VEC::VEC3(0.0f, 4.0f, 4.0f));
	
	

	tran_kambot->addChild(target_kambot.get());
	
	
	o_loader->addChild(tran_kambot.get());
	 


	ptrCamTran = tran_kambot.get();









//------------------Lights



	//boost::shared_ptr<NS_SG::dirLightNode> n_dir_lys(new NS_SG::dirLightNode("DirLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f));

	//Cavern Follow Light
	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys(new NS_SG::pointLightNode("PointLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.8f, 0.8f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point(new NS_SG::objTransform("tran_PointLys"));
	tran_Point->setPosition(NS_VEC::VEC3(0.0f, 2.0f, 0.0f));
	tran_Point->addChild(n_point_lys.get());
	ptrLitPlan = tran_Point.get();
	o_loader->addChild(tran_Point.get());


	
//Light Orange Stalagmite

	
	//tran_Point2->addChild(tran_Point.get());


//Light Indigo Stalagmite



//Light Violet Stalagmite


	



	//Dir Light
	boost::shared_ptr<NS_SG::dirLightNode> n_dir_lys(new NS_SG::dirLightNode("DirLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f, &e_dir));

	boost::shared_ptr<NS_SG::objTransform> tran_Dir(new NS_SG::objTransform("tran_DirLys"));
	

	

	
	tran_Dir->setPosition(NS_VEC::VEC3(0.0f, 10.0f, 30.0f));


	tran_Dir->addChild(n_dir_lys.get());


	o_loader->addChild(tran_Dir.get());
	



	//ugh
	boost::shared_ptr<NS_ENG::model>  n_sphereL(new NS_ENG::model( "Mesh/sphere.obj", "Mesh/sphere.mtl"));
	boost::shared_ptr<NS_ENG::model>  n_sphereN(new NS_ENG::model("Mesh/sphere.obj", "Mesh/sphere.mtl"));
	//boost::shared_ptr<NS_ENG::model>  n_quad(new NS_ENG::model( "Mesh/quad_test.obj", "Mesh/quad_test.mtl"));
	boost::shared_ptr<NS_ENG::model>  n_quad(new NS_ENG::model("Mesh/quad.obj", "Mesh/quad.mtl"));

	
	
//---------load music into bass	
	if (!BASS_Init(-1, 44100, 0, 0, 0))
		std::cout << "failed to init bass" << std::endl;
	//stream = BASS_StreamCreateFile(false, "bf.ogg", 0, 0,
	stream = BASS_StreamCreateFile(false, "AF.mp3", 0, 0,
		BASS_STREAM_PRESCAN);
	if (!stream)
		std::cout << "failed to open tune" << std::endl;



//----------create rocket device
	//Should be up at first
	rocket = sync_create_device("sync");
	if (!rocket)
		std::cout << "failed to open device" << std::endl;

#ifndef SYNC_PLAYER
	if (sync_connect(rocket, "localhost", SYNC_DEFAULT_PORT))
		std::cout << "failed to connect to host" << std::endl;
#endif

	TrackPart = sync_get_track(rocket, "part");

	cam_Pos_X = sync_get_track(rocket, "cam.x"),
	cam_Pos_Y = sync_get_track(rocket, "cam.y");
	cam_Pos_Z = sync_get_track(rocket, "cam.z");

	cam_Rot_X = sync_get_track(rocket, "cam.Rot.x");
	cam_Rot_Y = sync_get_track(rocket, "cam.Rot.y");
	cam_Rot_Z = sync_get_track(rocket, "cam.Rot.z");

	plane_Pos_X = sync_get_track(rocket, "Ppos.x");
	plane_Pos_Y = sync_get_track(rocket, "Ppos.y");
	plane_Pos_Z = sync_get_track(rocket, "Ppos.z");
	plane_Rot_X = sync_get_track(rocket, "Prot.x");
	plane_Rot_Y = sync_get_track(rocket, "Prot.y");
	plane_Rot_Z = sync_get_track(rocket, "Prot.z");
	plane_Sca_X = sync_get_track(rocket, "Psca.x");
	plane_Sca_Y = sync_get_track(rocket, "Psca.y");
	plane_Sca_Z = sync_get_track(rocket, "Psca.z");


	

	lit_Pos_X = sync_get_track(rocket, "Lpos.x");
	lit_Pos_Y = sync_get_track(rocket, "Lpos.y");
	lit_Pos_Z = sync_get_track(rocket, "Lpos.z");
	/*
	e_1_6_Rot_X = sync_get_track(rocket, "e_1_6_rX");
	e_1_6_Rot_Y = sync_get_track(rocket, "e_1_6_rY");
	e_1_6_Rot_Z = sync_get_track(rocket, "e_1_6_rZ");

	e_1_04_Rot_X = sync_get_track(rocket, "e_1_04_rX");
	e_1_04_Rot_Y = sync_get_track(rocket, "e_1_04_rY");
	e_1_04_Rot_Z = sync_get_track(rocket, "e_1_04_rZ");

	e_1_08_Rot_X = sync_get_track(rocket, "e_1_08_rX");
	e_1_08_Rot_Y = sync_get_track(rocket, "e_1_08_rY");
	e_1_08_Rot_Z = sync_get_track(rocket, "e_1_08_rZ");

	e_2_10_Rot_X = sync_get_track(rocket, "e_2_10_rX");
	e_2_10_Rot_Y = sync_get_track(rocket, "e_2_10_rY");
	e_2_10_Rot_Z = sync_get_track(rocket, "e_2_10_rZ");

	e_2_02_Rot_X = sync_get_track(rocket, "e_2_02_rX");
	e_2_02_Rot_Y = sync_get_track(rocket, "e_2_02_rY");
	e_2_02_Rot_Z = sync_get_track(rocket, "e_2_02_rZ");

	e_3_02_Rot_X = sync_get_track(rocket, "e_3_02_rX");
	e_3_02_Rot_Y = sync_get_track(rocket, "e_3_02_rY");
	e_3_02_Rot_Z = sync_get_track(rocket, "e_3_02_rZ");

	e_3_10_Rot_X = sync_get_track(rocket, "e_3_10_rX");
	e_3_10_Rot_Y = sync_get_track(rocket, "e_3_10_rY");
	e_3_10_Rot_Z = sync_get_track(rocket, "e_3_10_rZ");

	e_4_04_Rot_X = sync_get_track(rocket, "e_4_04_rX");
	e_4_04_Rot_Y = sync_get_track(rocket, "e_4_04_rY");
	e_4_04_Rot_Z = sync_get_track(rocket, "e_4_04_rZ");

	e_4_08_Rot_X = sync_get_track(rocket, "e_4_08_rX");
	e_4_08_Rot_Y = sync_get_track(rocket, "e_4_08_rY");
	e_4_08_Rot_Z = sync_get_track(rocket, "e_4_08_rZ");


	e_4_02_Rot_X = sync_get_track(rocket, "e_4_02_rX");
	e_4_02_Rot_Y = sync_get_track(rocket, "e_4_02_rY");
	e_4_02_Rot_Z = sync_get_track(rocket, "e_4_02_rZ");

	e_2_08_Rot_X = sync_get_track(rocket, "e_2_08_rX");
	e_2_08_Rot_Y = sync_get_track(rocket, "e_2_08_rY");
	e_2_08_Rot_Z = sync_get_track(rocket, "e_2_08_rZ");
	
	ArmPos_X = sync_get_track(rocket, "armPos_X");
	ArmPos_Y = sync_get_track(rocket, "armPos_Y");
	ArmPos_Z = sync_get_track(rocket, "armPos_Z");
	*/


	

	gridDrop = sync_get_track(rocket, "gridFunc");


	UtilityTrack = sync_get_track(rocket, "Utility");



	PlaneSync = NS_SG::objectAnim();
	CameraSync = NS_SG::objectAnim();

	

//------adds node to scene  (should do this when created to help  sort shit out)
	o_loader->addChild(tran_protagonist.get());

	//o_loader->addChild()

	
	
	o_loader->addObjectAnime(tran_kambot.get(), CameraSync);



	ptrComp = o_loader.get();


	NS_ENG::rendrer* mRender = new NS_ENG::rendrer(o_loader.get(), kambot.get(), n_sphereL.get(), n_sphereN.get(), n_quad.get(), &e_ao_Pass);



	mRender->Run();


//#ifndef SYNC_PLAYER
//	sync_save_tracks(rocket);
//#endif

	sync_destroy_device(rocket);
	return 0;
}
