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


HSTREAM stream;

sync_device *rocket;

const struct sync_track *plane_Pos_X, *plane_Pos_Y, *plane_Pos_Z, *plane_Rot_X, *plane_Rot_Y, *plane_Rot_Z, *plane_Sca_X, *plane_Sca_Y, *plane_Sca_Z;
const struct sync_track *lit_Pos_X, *lit_Pos_Y, *lit_Pos_Z;
const struct sync_track *cam_Pos_X, *cam_Pos_Y, *cam_Pos_Z;

/*
const struct sync_track *e_1_6_Rot_X, *e_1_6_Rot_Y, *e_1_6_Rot_Z;
const struct sync_track *e_1_04_Rot_X, *e_1_04_Rot_Y, *e_1_04_Rot_Z;
const struct sync_track *e_1_08_Rot_X, *e_1_08_Rot_Y, *e_1_08_Rot_Z;

const struct sync_track *ArmPos_X, *ArmPos_Y, *ArmPos_Z;


const struct sync_track *e_2_10_Rot_X, *e_2_10_Rot_Y, *e_2_10_Rot_Z;
const struct sync_track *e_2_02_Rot_X, *e_2_02_Rot_Y, *e_2_02_Rot_Z;

const struct sync_track *e_3_10_Rot_X, *e_3_10_Rot_Y, *e_3_10_Rot_Z;
const struct sync_track *e_3_02_Rot_X, *e_3_02_Rot_Y, *e_3_02_Rot_Z;


const struct sync_track *e_4_08_Rot_X, *e_4_08_Rot_Y, *e_4_08_Rot_Z;
const struct sync_track *e_4_04_Rot_X, *e_4_04_Rot_Y, *e_4_04_Rot_Z;


//Was meant to be 4 more if we split the rest in half  Now its one whole pentagon on each side 
const struct sync_track *e_4_02_Rot_X, *e_4_02_Rot_Y, *e_4_02_Rot_Z;
const struct sync_track *e_2_08_Rot_X, *e_2_08_Rot_Y, *e_2_08_Rot_Z;
*/

const struct sync_track *litG_Pos_X, *litG_Pos_Y, *litG_Pos_Z;
const struct sync_track *litY_Pos_X, *litY_Pos_Y, *litY_Pos_Z;
const struct sync_track *litR_Pos_X, *litR_Pos_Y, *litR_Pos_Z;
const struct sync_track *litB_Pos_X, *litB_Pos_Y, *litB_Pos_Z;

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



NS_SG::objTransform *ptrLitPLG;
NS_SG::objTransform *ptrLitPLY;
NS_SG::objTransform *ptrLitPLR;
NS_SG::objTransform *ptrLitPLB;



NS_SG::objTransform *Ptr_t_grid;

NS_SG::gridNode *ptrGridNode;

NS_SG::objTransform *ptrLitField;


NS_SG::objTransform *Ptr_t_greets;

NS_SG::objTransform *Ptr_t_a_greets;


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
			ptrLitField->setPosition(NS_VEC::VEC3(0.0, -100.0f, 40.0f));
			Ptr_t_grid->setPosition(NS_VEC::VEC3(0.0, 100.0f, 40.0f));
		
		}

		if (part == 1)
		{
			Ptr_t_grid->setPosition(NS_VEC::VEC3(0.0, -4, 40.0f));
			ptrLitField->setPosition(NS_VEC::VEC3(0, -4, 40));


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


			Ptr_t_a_greets->setPosition(NS_VEC::VEC3(2.0f, -3.0f, 40.0f));

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

		//4 is green
		if (func == 4)
		{
			ptrGridNode->Grid->CreateGridActor(NS_VEC::VEC2(-5.0f, -5.0f), NS_VEC::VEC3(0.0f, 1.0f, 0.0f), 1.0f);

		}

		else if (func == 0)
		{
			//ehm pass

		}
	}



}

void DodoOpen(float degree)
{
	
	

	if (DodoOpenCurr != degree)
	{
		DodoOpenCurr = degree;

		float DegX_104 = -117.0 - degree;
		float DegY_104 = 216.0; 



		float DegX_108 = -63.0 + degree;
		float DegY_108 = -36.0;

		float DegX_106 = -117.0 - degree;
		float DegY_106 = 0.0f;

		//float DegX_106 = -117.0 + degree;
		//float DegY_106 = 0;

		float DegX_202 = 63.0 - degree;
		float DegY_202 = -36.0;
		
		float DegX_210 = 63.0 - degree;
		float DegY_210 = 36.0;
		


		float DegX_302 = 63.0 - degree;
		float DegY_302 = -36.0;

		
		float DegX_310 = 63.0 - degree;
		float DegY_310 = 36.0; 

		float DegX_404 = 63.0 - degree;
		float DegY_404 = -108.0;

		float DegX_408 = 63.0 - degree;
		float DegY_408 = 108.0f;

		//really 304?
		float DegX_402_half = 64.0 - degree;
		float DegY_402_half = 36.0f;

		
		float DegX_208_half = -63.0f + degree;
		float DegY_208_half = 36.0f;


		ptrE_1_6->setRotation(NS_VEC::QUAT(DegX_106, DegY_106, 0.0f));
		ptrE_1_04->setRotation(NS_VEC::QUAT(DegX_104, DegY_104, 0.0f));
		ptrE_1_08->setRotation(NS_VEC::QUAT(DegX_108, DegY_108, 0.0f));



		ptrE_2_02->setRotation(NS_VEC::QUAT(DegX_202, DegY_202, 0.0f));
		ptrE_2_10->setRotation(NS_VEC::QUAT(DegX_210, DegY_210, 0.0f));

		ptrE_3_02->setRotation(NS_VEC::QUAT(DegX_302, DegY_302, 0.0f));
		ptrE_3_10->setRotation(NS_VEC::QUAT(DegX_310, DegY_310, 0.0f));


		ptrE_4_04->setRotation(NS_VEC::QUAT(DegX_404, DegY_404, 0.0f));

		ptrE_4_08->setRotation(NS_VEC::QUAT(DegX_408, DegY_408, 0.0f));

		ptrE_4_02_half->setRotation(NS_VEC::QUAT(DegX_402_half, DegY_402_half, 0.0f));
		ptrE_2_08_half->setRotation(NS_VEC::QUAT(DegX_208_half, DegY_208_half, 0.0f));



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
	//v3_tmpCamPos NS_VEC::VEC3(float(sync_get_val(cam_Pos_X, row)), float(sync_get_val(cam_Pos_Y, row)), float(sync_get_val(cam_Pos_Z, row)));
	

	//CameraSync.setPosKeyFrame(row, NS_VEC::VEC3(float(sync_get_val(cam_Pos_X, row)), float(sync_get_val(cam_Pos_Y, row)), float(sync_get_val(cam_Pos_Z, row))));
	//CameraSync.setRotKeyFrame(row, NS_VEC::QUAT(0.0f, 0.0f, 0.0f));
	//CameraSync.setScaleKeyFrame(row, NS_VEC::VEC3(1.0f, 1.0f, 1.0f));
	//PlaneSync.setPosKeyFrame(row, NS_VEC::VEC3(float(sync_get_val(plane_Pos_X, row)), float(sync_get_val(plane_Pos_Y, row)), float(sync_get_val(plane_Pos_Z, row))));
	//PlaneSync.setRotKeyFrame(row, NS_VEC::QUAT(float(sync_get_val(plane_Rot_X, row)), float(sync_get_val(plane_Rot_Y, row)), float(sync_get_val(plane_Rot_Z, row))));

	//ptrTranProt->setPosition(NS_VEC::VEC3(float(sync_get_val(plane_Pos_X, row)), float(sync_get_val(plane_Pos_Y, row)), float(sync_get_val(plane_Pos_Z, row))));
	//
	ptrCamTran->setPosition(NS_VEC::VEC3(float(sync_get_val(cam_Pos_X, row)), float(sync_get_val(cam_Pos_Y, row)), float(sync_get_val(cam_Pos_Z, row))));
	ptrTranProt->setRotation(NS_VEC::QUAT(float(sync_get_val(plane_Rot_X, row)), float(sync_get_val(plane_Rot_Y, row)), float(sync_get_val(plane_Rot_Z, row))));
	ptrTranProt->setPosition(NS_VEC::VEC3(float(sync_get_val(plane_Pos_X, row)), float(sync_get_val(plane_Pos_Y, row)), float(sync_get_val(plane_Pos_Z, row))));
	ptrTranProt->setScale(NS_VEC::VEC3(float(sync_get_val(plane_Sca_X, row)), float(sync_get_val(plane_Sca_Y, row)), float(sync_get_val(plane_Sca_Z, row))));

	ptrLitPlan->setPosition(NS_VEC::VEC3(float(sync_get_val(lit_Pos_X, row)), float(sync_get_val(lit_Pos_Y, row)), float(sync_get_val(lit_Pos_Z, row))));

	/*
	ptrE_1_6->setRotation(NS_VEC::QUAT(float(sync_get_val(e_1_6_Rot_X, row)), float(sync_get_val(e_1_6_Rot_Y, row)), float(sync_get_val(e_1_6_Rot_Z, row))));
	//really its 10oclock and 2oClock
	ptrE_1_08->setRotation(NS_VEC::QUAT(float(sync_get_val(e_1_08_Rot_X, row)), float(sync_get_val(e_1_08_Rot_Y, row)), float(sync_get_val(e_1_08_Rot_Z, row))));
	ptrE_1_04->setRotation(NS_VEC::QUAT(float(sync_get_val(e_1_04_Rot_X, row)), float(sync_get_val(e_1_04_Rot_Y, row)), float(sync_get_val(e_1_04_Rot_Z, row))));

	

	ptrE_2_10->setRotation(NS_VEC::QUAT(float(sync_get_val(e_2_10_Rot_X, row)), float(sync_get_val(e_2_10_Rot_Y, row)), float(sync_get_val(e_2_10_Rot_Z, row))));
	ptrE_2_02->setRotation(NS_VEC::QUAT(float(sync_get_val(e_2_02_Rot_X, row)), float(sync_get_val(e_2_02_Rot_Y, row)), float(sync_get_val(e_2_02_Rot_Z, row))));

	ptrE_3_10->setRotation(NS_VEC::QUAT(float(sync_get_val(e_3_10_Rot_X, row)), float(sync_get_val(e_3_10_Rot_Y, row)), float(sync_get_val(e_3_10_Rot_Z, row))));
	ptrE_3_02->setRotation(NS_VEC::QUAT(float(sync_get_val(e_3_02_Rot_X, row)), float(sync_get_val(e_3_02_Rot_Y, row)), float(sync_get_val(e_3_02_Rot_Z, row))));


	//ptrE_4_08->setPosition(NS_VEC::VEC3(float(sync_get_val(ArmPos_X, row)), float(sync_get_val(ArmPos_Y, row)), float(sync_get_val(ArmPos_Z, row))));
	ptrE_4_08->setRotation(NS_VEC::QUAT(float(sync_get_val(e_4_08_Rot_X, row)), float(sync_get_val(e_4_08_Rot_Y, row)), float(sync_get_val(e_4_08_Rot_Z, row))));
	
	
	//ptrE_4_04->setPosition(NS_VEC::VEC3(float(sync_get_val(ArmPos_X, row)), float(sync_get_val(ArmPos_Y, row)), float(sync_get_val(ArmPos_Z, row))));
	ptrE_4_04->setRotation(NS_VEC::QUAT(float(sync_get_val(e_4_04_Rot_X, row)), float(sync_get_val(e_4_04_Rot_Y, row)), float(sync_get_val(e_4_04_Rot_Z, row))));


	//ptrE_4_02_half->setPosition(NS_VEC::VEC3(float(sync_get_val(ArmPos_X, row)), float(sync_get_val(ArmPos_Y, row)), float(sync_get_val(ArmPos_Z, row))));
	ptrE_4_02_half->setRotation(NS_VEC::QUAT(float(sync_get_val(e_4_02_Rot_X, row)), float(sync_get_val(e_4_02_Rot_Y, row)), float(sync_get_val(e_4_02_Rot_Z, row))));
	
	//ptrE_2_08_half->setPosition(NS_VEC::VEC3(float(sync_get_val(ArmPos_X, row)), float(sync_get_val(ArmPos_Y, row)), float(sync_get_val(ArmPos_Z, row))));
	ptrE_2_08_half->setRotation(NS_VEC::QUAT(float(sync_get_val(e_2_08_Rot_X, row)), float(sync_get_val(e_2_08_Rot_Y, row)), float(sync_get_val(e_2_08_Rot_Z, row))));
	*/
	float ExpandValue = float(sync_get_val(dodoOpen, row));

	DodoOpen(ExpandValue);

	if (partCurrent == 1)
	{
		float ExpandLight = ExpandValue / 65.0f;

			ptrLitField->setScale(NS_VEC::VEC3(ExpandLight, ExpandLight, ExpandLight));
			
			//Ptr_t_grid
	}


	ptrLitPLG->setPosition(NS_VEC::VEC3(float(sync_get_val(litG_Pos_X, row)), float(sync_get_val(litG_Pos_Y, row)), float(sync_get_val(litG_Pos_Z, row))));
	ptrLitPLY->setPosition(NS_VEC::VEC3(float(sync_get_val(litY_Pos_X, row)), float(sync_get_val(litY_Pos_Y, row)), float(sync_get_val(litY_Pos_Z, row))));
	ptrLitPLR->setPosition(NS_VEC::VEC3(float(sync_get_val(litR_Pos_X, row)), float(sync_get_val(litR_Pos_Y, row)), float(sync_get_val(litR_Pos_Z, row))));
	ptrLitPLB->setPosition(NS_VEC::VEC3(float(sync_get_val(litB_Pos_X, row)), float(sync_get_val(litB_Pos_Y, row)), float(sync_get_val(litB_Pos_Z, row))));

	GridBeat(int(sync_get_val(gridDrop, row)));


	if (partCurrent == 3)
		Ptr_t_greets->setPosition(NS_VEC::VEC3(0.0f, 0.0f, float(sync_get_val(UtilityTrack, row))));
	
	
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
			FS = true;
	}
	
	//overide remember to remove

	Xres = 1280;
	Yres = 720;
	FS = true;

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



	std::cout << "Status of geometry effect is: " << e_geom.Init() << std::endl;

	e_geom.Enable();
	e_geom.SetColorTextureUnit(COLOR_TEXTURE_UNIT_INDEX);

	std::cout << "Status of grid geometry effect is: " << e_hmap.Init() << std::endl;

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

	NS_ENG::model m_greets("Mesh/LazyGreets.obj", "Mesh/LazyGreets.mtl");


	boost::shared_ptr<NS_SG::modelNode> mn_greets(new NS_SG::modelNode("Greets", &m_greets, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> tran_angle_greets(new NS_SG::objTransform("tran_angle_greets"));


	boost::shared_ptr<NS_SG::objTransform> tran_greets(new NS_SG::objTransform("tran_greets"));

	tran_greets->addChild(mn_greets.get());

	tran_angle_greets->addChild(tran_greets.get());

	tran_angle_greets->setPosition(NS_VEC::VEC3(100.0f, -3.0f, 40.0f));

	tran_angle_greets->setRotation(NS_VEC::QUAT(0.0f, 200.0f, 0.0f));

	tran_greets->setPosition(NS_VEC::VEC3(0.0f, 0, 100.0f));
	tran_greets->setRotation(NS_VEC::QUAT(0.0f, 0.0f, 0.0f));

	Ptr_t_a_greets = tran_angle_greets.get();

	Ptr_t_greets = tran_greets.get();


	o_loader->addChild(tran_angle_greets.get());


	//plane add as child later on the dodo

	NS_ENG::model m_fly("Mesh/fixedP38.obj", "Mesh/newP38.mtl");

	boost::shared_ptr<NS_SG::modelNode> mn_ShowPiece(new NS_SG::modelNode("ShowPiece", &m_fly, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> tran_ShowPiece(new NS_SG::objTransform("tran_ShowPiece"));

	tran_ShowPiece->addChild(mn_ShowPiece.get());

	Ptr_t_ShowPiece = tran_ShowPiece.get();


	tran_ShowPiece->setPosition(NS_VEC::VEC3(0.0f, 200.0f, 0.0f));
	tran_ShowPiece->setScale(NS_VEC::VEC3(0.25f, 0.25f, 0.25f));


//------------UnderGround Scene

	




	//m is for mesh/model  texture is included. 
	NS_ENG::model m_cavern("Mesh/cave.obj", "Mesh/cave.mtl");



	//NS_ENG::model fly( "Mesh/fixedP38.obj", "Mesh/newP38.mtl");


	//mn is for model node
	boost::shared_ptr<NS_SG::modelNode> mn_cavern(new NS_SG::modelNode("Scene_Cavern", &m_cavern, &e_geom));


	boost::shared_ptr<NS_SG::objTransform> tran_cavern(new NS_SG::objTransform("tran_cavern"));

	tran_cavern->setPosition(NS_VEC::VEC3(0.0f, 0.0f, 0.0f));
	tran_cavern->setRotation(NS_VEC::QUAT(0.0f, -90.0f, 0.0f));

	tran_cavern->addChild(mn_cavern.get());


	//details to Scene
	NS_ENG::model m_stalagmite("Mesh/Stalagmite.obj", "Mesh/Stalagmite.mtl");



	//a node can only have one parent
	//green
	boost::shared_ptr<NS_SG::modelNode> mn_stalagmite_1(new NS_SG::modelNode("Scene_Stalagmite_1", &m_stalagmite, &e_geom));
	boost::shared_ptr<NS_SG::objTransform> tran_stalagmite_1(new NS_SG::objTransform("tran_stalagmite_1"));
	tran_stalagmite_1->setScale(NS_VEC::VEC3(5.0f, 5.0f, 5.0f));
	tran_stalagmite_1->setPosition(NS_VEC::VEC3(5.0f, 30.0f, 22.0f));
	tran_stalagmite_1->setRotation(NS_VEC::QUAT(0.0f, 0.0f, 0.0f));
	tran_stalagmite_1->addChild(mn_stalagmite_1.get());
	//yellow
	boost::shared_ptr<NS_SG::modelNode> mn_stalagmite_2(new NS_SG::modelNode("Scene_Stalagmite_2", &m_stalagmite, &e_geom));
	boost::shared_ptr<NS_SG::objTransform> tran_stalagmite_2(new NS_SG::objTransform("tran_stalagmite_2"));
	tran_stalagmite_2->addChild(mn_stalagmite_2.get());
	tran_stalagmite_2->setScale(NS_VEC::VEC3(5.0f, 5.0f, 5.0f));

	tran_stalagmite_2->setPosition(NS_VEC::VEC3(-5.0f, 30.0f, 35.0f));
	tran_stalagmite_2->setRotation(NS_VEC::QUAT(0.0f, 90.0f, 0.0f));
	//red
	boost::shared_ptr<NS_SG::modelNode> mn_stalagmite_3(new NS_SG::modelNode("Scene_Stalagmite_3", &m_stalagmite, &e_geom));
	boost::shared_ptr<NS_SG::objTransform> tran_stalagmite_3(new NS_SG::objTransform("tran_stalagmite_3"));
	tran_stalagmite_3->addChild(mn_stalagmite_3.get());
	tran_stalagmite_3->setScale(NS_VEC::VEC3(5.0f, 5.0f, 5.0f));
	tran_stalagmite_3->setPosition(NS_VEC::VEC3(5.5f, 30.0f, 45.5f));
	tran_stalagmite_3->setRotation(NS_VEC::QUAT(0.0f, -90.0f, 0.0f));
	//blue
	boost::shared_ptr<NS_SG::modelNode> mn_stalagmite_4(new NS_SG::modelNode("Scene_Stalagmite_4", &m_stalagmite, &e_geom));
	boost::shared_ptr<NS_SG::objTransform> tran_stalagmite_4(new NS_SG::objTransform("tran_stalagmite_4"));
	tran_stalagmite_4->addChild(mn_stalagmite_4.get());
	tran_stalagmite_4->setScale(NS_VEC::VEC3(5.0f, 5.0f, 5.0f));
	tran_stalagmite_4->setPosition(NS_VEC::VEC3(-6.0f, 30.0f, 56.0f));
	tran_stalagmite_4->setRotation(NS_VEC::QUAT(0.0f, 45.0f, 0.0f));
	/*
	//orange
	boost::shared_ptr<NS_SG::modelNode> mn_stalagmite_5(new NS_SG::modelNode("Scene_Stalagmite_5", &m_stalagmite, &e_geom));
	boost::shared_ptr<NS_SG::objTransform> tran_stalagmite_5(new NS_SG::objTransform("tran_stalagmite_5"));
	tran_stalagmite_5->addChild(mn_stalagmite_5.get());
	tran_stalagmite_5->setScale(NS_VEC::VEC3(5.0f, 5.0f, 5.0f));
	tran_stalagmite_5->setPosition(NS_VEC::VEC3(-2.0f, 30.0f, 66.0f));
	tran_stalagmite_5->setRotation(NS_VEC::QUAT(0.0f, 120.0f, 0.0f));
	*/


	o_loader->addChild(tran_stalagmite_1.get());
	o_loader->addChild(tran_stalagmite_2.get());
	o_loader->addChild(tran_stalagmite_3.get());
	o_loader->addChild(tran_stalagmite_4.get());
//-------------------------------------me


	NS_ENG::model m_protagonist("Mesh/PentagonBase.obj", "Mesh/PentagonBase.mtl");

	NS_ENG::model m_P_Arm("Mesh/PentagonArm.obj", "Mesh/PentagonArm.mtl");

	//NS_ENG::model m_P_Half_Arm("Mesh/PentagonHalfArm.obj", "Mesh/PentagonHalfArm.mtl");



	//mn is for model node
	boost::shared_ptr<NS_SG::modelNode> mn_protoganist(new NS_SG::modelNode("protoganist", &m_protagonist, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> tran_protagonist(new NS_SG::objTransform("tran_protoganist"));
		
	tran_protagonist->setPosition(NS_VEC::VEC3(0.0f, 0.0f, 0.0f));
	
	tran_protagonist->addChild(mn_protoganist.get());


	//t_1_6
	boost::shared_ptr<NS_SG::modelNode> m_1_6(new NS_SG::modelNode("1_6", &m_P_Arm, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> t_1_6(new NS_SG::objTransform("t1_6"));

	//xrot=-114.0 yrot=0
	t_1_6->setPosition(NS_VEC::VEC3(0.0f, 0.0f, 0.81f));

	t_1_6->addChild(m_1_6.get());

	//t_1_02
	boost::shared_ptr<NS_SG::modelNode> m_1_04(new NS_SG::modelNode("1_04", &m_P_Arm, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> t_1_04(new NS_SG::objTransform("t1_04"));
	//really t_1_02(or 10)  xrot=-117.0 Yrot=216 or something  VEC3(0.48, 0.0f, -0.66f)
	t_1_04->setPosition(NS_VEC::VEC3(0.48, 0.0f, -0.66f));
	t_1_04->addChild(m_1_04.get());
	ptrE_1_04 = t_1_04.get();


	//t_1_10
	boost::shared_ptr<NS_SG::modelNode> m_1_08(new NS_SG::modelNode("1_08", &m_P_Arm, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> t_1_08(new NS_SG::objTransform("t1_08"));
	//really t_1_10 xrot=-36.0  YRot= 63.0  
	t_1_08->setPosition(NS_VEC::VEC3(-0.48, 0.0f, -0.66f));
	t_1_08->addChild(m_1_08.get());
	ptrE_1_08 = t_1_08.get();


	//t_1_10->halfarm   Half is normal fuck it two on each side each end
	//boost::shared_ptr<NS_SG::modelNode> m_4_02_half(new NS_SG::modelNode("4_02_half", &m_P_Half_Arm, &e_geom));
	boost::shared_ptr<NS_SG::modelNode> m_2_08_half(new NS_SG::modelNode("2_08_half", &m_P_Arm, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> t_2_08_half(new NS_SG::objTransform("t4_02_half"));
	// xrot=63 Yrot=-36.0 
	t_2_08_half->setPosition(NS_VEC::VEC3(0.48028, 0.0f, -1.47909f));
	t_2_08_half->addChild(m_2_08_half.get());
	ptrE_2_08_half = t_2_08_half.get();


	//t_2_10
	boost::shared_ptr<NS_SG::modelNode> m_2_10(new NS_SG::modelNode("2_10", &m_P_Arm, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> t_2_10(new NS_SG::objTransform("t2_10"));
	//xrot=63.0 yrot=36
	t_2_10->setPosition(NS_VEC::VEC3(0.48028, 0.0f, -1.47909f));
	t_2_10->addChild(m_2_10.get());

	ptrE_2_10 = t_2_10.get();




	//t_2_02
	boost::shared_ptr<NS_SG::modelNode> m_2_02(new NS_SG::modelNode("2_02", &m_P_Arm, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> t_2_02(new NS_SG::objTransform("t2_02"));
	// xrot=63 Yrot=-36.0 
	t_2_02->setPosition(NS_VEC::VEC3(-0.48028, 0.0f, -1.47909f));
	t_2_02->addChild(m_2_02.get());
	ptrE_2_02 = t_2_02.get();




	//t_3_02
	boost::shared_ptr<NS_SG::modelNode> m_3_02(new NS_SG::modelNode("3_02", &m_P_Arm, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> t_3_02(new NS_SG::objTransform("t3_02"));
	// xrot=63 Yrot=-36.0 
	t_3_02->setPosition(NS_VEC::VEC3(-0.48028, 0.0f, -1.47909f));
	t_3_02->addChild(m_3_02.get());
	ptrE_3_02 = t_3_02.get();


	//WRONG its halfarm is in third echelon
	//t_3_02->halfarm   Half is normal fuck it two on each side each end
	//boost::shared_ptr<NS_SG::modelNode> m_4_02_half(new NS_SG::modelNode("4_02_half", &m_P_Half_Arm, &e_geom));
	boost::shared_ptr<NS_SG::modelNode> m_4_02_half(new NS_SG::modelNode("4_02_half", &m_P_Arm, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> t_4_02_half(new NS_SG::objTransform("t4_02_half"));
	// xrot=63 Yrot=-36.0 
	t_4_02_half->setPosition(NS_VEC::VEC3(0.48028, 0.0f, -1.47909f));
	t_4_02_half->addChild(m_4_02_half.get());
	ptrE_4_02_half = t_4_02_half.get();


	//t_3_02 -> t_4_04 //Where 104 should be

	boost::shared_ptr<NS_SG::modelNode> m_4_04(new NS_SG::modelNode("4_04", &m_P_Arm, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> t_4_04(new NS_SG::objTransform("t4_04"));
	// xrot=63 Yrot=-36.0 
	t_4_04->setPosition(NS_VEC::VEC3(-0.77, 0.0f, -0.565));
	t_4_04->addChild(m_4_04.get());
	ptrE_4_04 = t_4_04.get();


	//t_3_10
	boost::shared_ptr<NS_SG::modelNode> m_3_10(new NS_SG::modelNode("3_10", &m_P_Arm, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> t_3_10(new NS_SG::objTransform("t3_10"));
	//xrot=63.0 yrot=36
	t_3_10->setPosition(NS_VEC::VEC3(0.48028, 0.0f, -1.47909f));
	t_3_10->addChild(m_3_10.get());

	ptrE_3_10 = t_3_10.get();


	//t_3_10 -> t_4_08 //Where 108 should be

	boost::shared_ptr<NS_SG::modelNode> m_4_08(new NS_SG::modelNode("4_08", &m_P_Arm, &e_geom));

	boost::shared_ptr<NS_SG::objTransform> t_4_08(new NS_SG::objTransform("t4_08"));
	// xrot=63 Yrot=-36.0 
	t_4_08->setPosition(NS_VEC::VEC3(0.77, 0.0f, -0.565));
	t_4_08->addChild(m_4_08.get());
	ptrE_4_08 = t_4_08.get();



	t_1_6->addChild(t_2_10.get());
	t_1_6->addChild(t_2_02.get());

	//add two steps of pentagons to each
	t_2_10->addChild(t_3_10.get());
	t_2_02->addChild(t_3_02.get());

	t_3_10->addChild(t_4_08.get());
	t_3_02->addChild(t_4_04.get());
	

	//whatever Really an 3_08
	t_2_02->addChild(t_4_02_half.get());

	//lastly
	tran_protagonist->addChild(t_1_6.get());
	tran_protagonist->addChild(t_1_08.get());
	tran_protagonist->addChild(t_1_04.get());

	//from before
	tran_protagonist->addChild(tran_ShowPiece.get());

	t_1_08->addChild(t_2_08_half.get());

	//and
	ptrTranProt = tran_protagonist.get();
	//ptr
	ptrE_1_6 = t_1_6.get();


	/*
	boost::shared_ptr<NS_SG::targetTransform> target_look(new NS_SG::targetTransform("tar_look"));
	boost::shared_ptr<NS_SG::objTransform> t_look(new NS_SG::objTransform("t_look"));


	boost::shared_ptr<NS_SG::modelNode> lookTest(new NS_SG::modelNode("looker", &m_P_Arm, &e_geom));

	t_look->setPosition(NS_VEC::VEC3(-2.0f, 0.0f, 2.0f));
	target_look->setTarget(mn_protoganist.get());
	
	t_look->addChild(target_look.get());

	o_loader->addChild(t_look.get());
	*/
//-----------------------------Grid

		boost::shared_ptr<NS_SG::objTransform> t_grid(new NS_SG::objTransform("t_grid"));
		t_grid->setPosition(NS_VEC::VEC3(0, -4, 40));
		NS_ENG::GridPoints m_grid10x10(90, 90, 0.5f);
		boost::shared_ptr<NS_SG::gridNode> mn_grid(new NS_SG::gridNode("grid", &m_grid10x10, &e_hmap));
		
		ptrGridNode = mn_grid.get();

		t_grid->addChild(mn_grid.get());

		Ptr_t_grid = t_grid.get();

		o_loader->addChild(t_grid.get());




//--------------------Camera 
	//1 for nowf
	

	boost::shared_ptr<NS_SG::camera> kambot(new NS_SG::camera("kambot"));


	boost::shared_ptr<NS_SG::objTransform> tran_kambot(new NS_SG::objTransform("tran_kambot"));
	boost::shared_ptr<NS_SG::targetTransform> target_kambot(new NS_SG::targetTransform("target_kambot"));
	boost::shared_ptr<NS_SG::objTransform> pivot_kambot(new NS_SG::objTransform("pivot_kambot"));

	
	
	target_kambot->setTarget(mn_protoganist.get());

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
	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys(new NS_SG::pointLightNode("PointLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point(new NS_SG::objTransform("tran_PointLys"));
	tran_Point->setPosition(NS_VEC::VEC3(0.0f, 2.0f, 0.0f));
	tran_Point->addChild(n_point_lys.get());
	ptrLitPlan = tran_Point.get();
	o_loader->addChild(tran_Point.get());



	boost::shared_ptr<NS_SG::pointLightNode> n_pl_g(new NS_SG::pointLightNode("PointLys_G", NS_VEC::VEC3(0.0f, 1.0f, 0.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_pl_g(new NS_SG::objTransform("tran_PointLys_G"));
	tran_pl_g->setPosition(NS_VEC::VEC3(0.0f, 2.0f, 0.0f));
	tran_pl_g->addChild(n_pl_g.get());
	ptrLitPLG = tran_pl_g.get();
	o_loader->addChild(tran_pl_g.get());

	boost::shared_ptr<NS_SG::pointLightNode> n_pl_y(new NS_SG::pointLightNode("PointLys_Y", NS_VEC::VEC3(1.0f, 1.0f, 0.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_pl_y(new NS_SG::objTransform("tran_PointLys_Y"));
	tran_pl_g->setPosition(NS_VEC::VEC3(0.0f, 2.0f, 0.0f));
	tran_pl_y->addChild(n_pl_y.get());
	ptrLitPLY = tran_pl_y.get();
	o_loader->addChild(tran_pl_y.get());

	boost::shared_ptr<NS_SG::pointLightNode> n_pl_r(new NS_SG::pointLightNode("PointLys_R", NS_VEC::VEC3(1.0f, 0.0f, 0.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_pl_r(new NS_SG::objTransform("tran_PointLys_R"));
	tran_pl_r->setPosition(NS_VEC::VEC3(0.0f, 2.0f, 0.0f));
	tran_pl_r->addChild(n_pl_r.get());
	ptrLitPLR = tran_pl_r.get();
	o_loader->addChild(tran_pl_r.get());

	boost::shared_ptr<NS_SG::pointLightNode> n_pl_b(new NS_SG::pointLightNode("PointLys_B", NS_VEC::VEC3(0.0f, 0.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_pl_b(new NS_SG::objTransform("tran_PointLys_B"));
	tran_pl_b->setPosition(NS_VEC::VEC3(0.0f, 2.0f, 0.0f));
	tran_pl_b->addChild(n_pl_b.get());
	ptrLitPLB = tran_pl_b.get();
	o_loader->addChild(tran_pl_b.get());

//Light Green Stalagmite
	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_GW_1(new NS_SG::pointLightNode("G_White_PointLys_1", NS_VEC::VEC3(0.0f, 1.0f, 0.0f), 1.5f, 4.0f, 0.01f, 0.8f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_GW_1(new NS_SG::objTransform("tran_G_White_PointLys_1"));
	tran_Point_GW_1->addChild(n_point_lys_GW_1.get());
	tran_Point_GW_1->setPosition(NS_VEC::VEC3(5.0f, 10.0f, 22.0f));
	o_loader->addChild(tran_Point_GW_1.get());

	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_GW_2(new NS_SG::pointLightNode("G_White_PointLys_2", NS_VEC::VEC3(0.0f, 1.0f, 0.0f), 1.5f, 4.0f, 0.01f, 0.8f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_GW_2(new NS_SG::objTransform("tran_G_White_PointLys_2"));
	tran_Point_GW_2->addChild(n_point_lys_GW_2.get());
	tran_Point_GW_2->setPosition(NS_VEC::VEC3(5.0f, 20.0f, 22.0f));
	o_loader->addChild(tran_Point_GW_2.get());

	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_GW_3(new NS_SG::pointLightNode("G_White_PointLys_3", NS_VEC::VEC3(0.0f, 1.0f, 0.0f), 1.5f, 4.0f, 0.01f, 0.8f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_GW_3(new NS_SG::objTransform("tran_G_White_PointLys_3"));
	tran_Point_GW_3->addChild(n_point_lys_GW_3.get());
	tran_Point_GW_3->setPosition(NS_VEC::VEC3(5.0f, 30.0f, 22.0f));
	o_loader->addChild(tran_Point_GW_3.get());

	
//Light Yellow Stalagmite
	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_YW_1(new NS_SG::pointLightNode("Y_White_PointLys_1", NS_VEC::VEC3(1.0f, 1.0f, 0.0f), 1.5f, 4.0f, 0.01f, 0.8f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_YW_1(new NS_SG::objTransform("tran_Y_White_PointLys_1"));
	tran_Point_YW_1->addChild(n_point_lys_YW_1.get());
	tran_Point_YW_1->setPosition(NS_VEC::VEC3(-5.0f, 10.0f, 35.0f));
	o_loader->addChild(tran_Point_YW_1.get());

	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_YW_2(new NS_SG::pointLightNode("Y_White_PointLys_2", NS_VEC::VEC3(1.0f, 1.0f, 0.0f), 1.5f, 4.0f, 0.01f, 0.8f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_YW_2(new NS_SG::objTransform("tran_Y_White_PointLys_2"));
	tran_Point_YW_2->addChild(n_point_lys_YW_2.get());
	tran_Point_YW_2->setPosition(NS_VEC::VEC3(-5.0f, 20.0f, 35.0f));
	o_loader->addChild(tran_Point_YW_2.get());

	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_YW_3(new NS_SG::pointLightNode("Y_White_PointLys_3", NS_VEC::VEC3(1.0f, 1.0f, 0.0f), 1.5f, 4.0f, 0.01f, 0.8f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_YW_3(new NS_SG::objTransform("tran_Y_White_PointLys_3"));
	tran_Point_YW_3->addChild(n_point_lys_YW_3.get());
	tran_Point_YW_3->setPosition(NS_VEC::VEC3(-5.0f, 30.0f, 35.0f));
	o_loader->addChild(tran_Point_YW_3.get());
	
//Light Red Stalagmite
	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_RW_1(new NS_SG::pointLightNode("R_White_PointLys_1", NS_VEC::VEC3(1.0f, 0.0f, 0.0f), 1.5f, 4.0f, 0.01f, 0.8f, 0.5f,  &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_RW_1(new NS_SG::objTransform("tran_R_White_PointLys_1"));
	tran_Point_RW_1->addChild(n_point_lys_RW_1.get());
	tran_Point_RW_1->setPosition(NS_VEC::VEC3(5.5f, 10.0f, 45.5f));
	o_loader->addChild(tran_Point_RW_1.get());

	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_RW_2(new NS_SG::pointLightNode("R_White_PointLys_2", NS_VEC::VEC3(1.0f, 0.0f, 0.0f),1.5f, 4.0f, 0.01f, 0.8f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_RW_2(new NS_SG::objTransform("tran_R_White_PointLys_2"));
	tran_Point_RW_2->addChild(n_point_lys_RW_2.get());
	tran_Point_RW_2->setPosition(NS_VEC::VEC3(5.5f, 20.0f, 45.5f));
	o_loader->addChild(tran_Point_RW_2.get());

	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_RW_3(new NS_SG::pointLightNode("R_White_PointLys_3", NS_VEC::VEC3(1.0f, 0.0f, 0.0f), 1.5f, 4.0f, 0.01f, 0.8f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_RW_3(new NS_SG::objTransform("tran_R_White_PointLys_3"));
	tran_Point_RW_3->addChild(n_point_lys_RW_3.get());
	tran_Point_RW_3->setPosition(NS_VEC::VEC3(5.5f, 30.0f, 45.5f));
	o_loader->addChild(tran_Point_RW_3.get());

//Light Blue Stalagmite
	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_BW_1(new NS_SG::pointLightNode("B_White_PointLys_1", NS_VEC::VEC3(0.0f, 0.0f, 1.0f), 1.5f, 4.0f, 0.01f, 0.8f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_BW_1(new NS_SG::objTransform("tran_B_White_PointLys_1"));
	tran_Point_BW_1->addChild(n_point_lys_BW_1.get());
	tran_Point_BW_1->setPosition(NS_VEC::VEC3(-6.0f, 10.0f, 56.0f));
	o_loader->addChild(tran_Point_BW_1.get());

	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_BW_2(new NS_SG::pointLightNode("B_White_PointLys_2", NS_VEC::VEC3(0.0f, 0.0f, 1.0f), 1.5f, 4.0f, 0.01f, 0.8f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_BW_2(new NS_SG::objTransform("tran_B_White_PointLys_2"));
	tran_Point_BW_2->addChild(n_point_lys_BW_2.get());
	tran_Point_BW_2->setPosition(NS_VEC::VEC3(-6.0f, 20.0f, 56.0f));
	o_loader->addChild(tran_Point_BW_2.get());

	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys_BW_3(new NS_SG::pointLightNode("B_White_PointLys_3", NS_VEC::VEC3(0.0f, 0.0f, 1.0f), 1.5f, 4.0f, 0.01f, 0.8f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point_BW_3(new NS_SG::objTransform("tran_B_White_PointLys_3"));
	tran_Point_BW_3->addChild(n_point_lys_BW_3.get());
	tran_Point_BW_3->setPosition(NS_VEC::VEC3(-6.0f, 30.0f, 56.0f));
	o_loader->addChild(tran_Point_BW_3.get());


//------------Lightfield because I have neither cone nor dir light...I fucking suck
	/*
	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys(new NS_SG::pointLightNode("PointLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point(new NS_SG::objTransform("tran_PointLys"));
	tran_Point->setPosition(NS_VEC::VEC3(0.0f, 2.0f, 0.0f));
	tran_Point->addChild(n_point_lys.get());
	ptrLitPlan = tran_Point.get();
	o_loader->addChild(tran_Point.get());
	
	*/
	boost::shared_ptr<NS_SG::objTransform> t_lightField(new NS_SG::objTransform("t_lightField"));
	t_lightField->setPosition(NS_VEC::VEC3(0, -4, 40));

	boost::shared_ptr<NS_SG::pointLightNode> UL_point_lys(new NS_SG::pointLightNode("PointLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_UL_Point(new NS_SG::objTransform("tran_PointLys"));
	tran_UL_Point->setPosition(NS_VEC::VEC3(6.0f, 2.0f, -6.0f));
	tran_UL_Point->addChild(UL_point_lys.get());

	t_lightField->addChild(tran_UL_Point.get());

	//between blue and yellow
	boost::shared_ptr<NS_SG::pointLightNode> UR_point_lys(new NS_SG::pointLightNode("PointLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_UR_Point(new NS_SG::objTransform("tran_PointLys"));
	tran_UR_Point->setPosition(NS_VEC::VEC3(-6.0f, 2.0f, 6.0f));
	tran_UR_Point->addChild(UR_point_lys.get());
	t_lightField->addChild(tran_UR_Point.get());

	//between green and yellow
	boost::shared_ptr<NS_SG::pointLightNode> CEN_point_lys(new NS_SG::pointLightNode("PointLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_CEN_Point(new NS_SG::objTransform("tran_PointLys"));
	tran_CEN_Point->setPosition(NS_VEC::VEC3(0.0f, 2.0f, -11.0f));
	tran_CEN_Point->addChild(CEN_point_lys.get());
	//ptrLitPlan = tran_Point.get();
	t_lightField->addChild(tran_CEN_Point.get());

	//between red and blue
	boost::shared_ptr<NS_SG::pointLightNode> LR_point_lys(new NS_SG::pointLightNode("PointLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_LR_Point(new NS_SG::objTransform("tran_PointLys"));
	tran_LR_Point->setPosition(NS_VEC::VEC3(0.0f, 2.0f, 12.0f));
	tran_LR_Point->addChild(LR_point_lys.get());
	t_lightField->addChild(tran_LR_Point.get());


	boost::shared_ptr<NS_SG::pointLightNode> LL_point_lys(new NS_SG::pointLightNode("PointLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_LL_Point(new NS_SG::objTransform("tran_PointLys"));
	tran_LL_Point->setPosition(NS_VEC::VEC3(4.0f, 2.0f, -6.0f));
	tran_LL_Point->addChild(LL_point_lys.get());
	//t_lightField->addChild(tran_LL_Point.get());

	boost::shared_ptr<NS_SG::pointLightNode> Stal_Green_point_lys(new NS_SG::pointLightNode("PointLys_Green_Grid", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_SG_Point(new NS_SG::objTransform("tran_Green_Grid_PointLys"));
	tran_SG_Point->setPosition(NS_VEC::VEC3(5.0f, 2.0f, -18.0f));
	tran_SG_Point->addChild(Stal_Green_point_lys.get());
	t_lightField->addChild(tran_SG_Point.get());

	//NS_VEC::VEC3(5.0f, 30.0f, 22.0fw
	//fuck it legg til 4 point lys til for hver stalagmitt...call det...intentional occulsion
	boost::shared_ptr<NS_SG::pointLightNode> Stal_Yellow_point_lys(new NS_SG::pointLightNode("PointLys_Yellow_Grid", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_SY_Point(new NS_SG::objTransform("tran_Yellow_Grid_PointLys"));
	tran_SY_Point->setPosition(NS_VEC::VEC3(-5.0f, 2.0f, -5.0f));
	tran_SY_Point->addChild(Stal_Yellow_point_lys.get());
	t_lightField->addChild(tran_SY_Point.get());

	boost::shared_ptr<NS_SG::pointLightNode> Stal_Red_point_lys(new NS_SG::pointLightNode("PointLys_Red_Grid", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_SR_Point(new NS_SG::objTransform("tran_Red_Grid_PointLys"));
	tran_SR_Point->setPosition(NS_VEC::VEC3(5.5f, 2.0f, 5.5f));
	tran_SR_Point->addChild(Stal_Red_point_lys.get());
	t_lightField->addChild(tran_SR_Point.get());

	boost::shared_ptr<NS_SG::pointLightNode> Stal_Blue_point_lys(new NS_SG::pointLightNode("PointLys_Blue_Grid", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_SB_Point(new NS_SG::objTransform("tran_Blue_Grid_PointLys"));
	tran_SB_Point->setPosition(NS_VEC::VEC3(-6.0f, 2.0f, 16.0f));
	tran_SB_Point->addChild(Stal_Blue_point_lys.get());
	t_lightField->addChild(tran_SB_Point.get());



	ptrLitField = t_lightField.get();

	o_loader->addChild(t_lightField.get());
	
//Light Orange Stalagmite

	
	//tran_Point2->addChild(tran_Point.get());


//Light Indigo Stalagmite



//Light Violet Stalagmite


	




	//Dir Light
	boost::shared_ptr<NS_SG::dirLightNode> n_dir_lys(new NS_SG::dirLightNode("DirLys", NS_VEC::VEC3(1.0f, 1.0f, 0.612f), 0.1f, 0.5f, &e_dir));

	boost::shared_ptr<NS_SG::objTransform> tran_Dir(new NS_SG::objTransform("tran_DirLys"));
	



	
	tran_Dir->setPosition(NS_VEC::VEC3(0.0f, 0.0f, 0.0f));


	tran_Dir->addChild(n_dir_lys.get());


	o_loader->addChild(tran_Dir.get());
	



	//ugh
	boost::shared_ptr<NS_ENG::model>  n_sphereL(new NS_ENG::model( "Mesh/sphere.obj", "Mesh/sphere.mtl"));
	boost::shared_ptr<NS_ENG::model>  n_sphereN(new NS_ENG::model("Mesh/sphere.obj", "Mesh/sphere.mtl"));
	boost::shared_ptr<NS_ENG::model>  n_quad(new NS_ENG::model( "Mesh/quad.obj", "Mesh/quad.mtl"));
	
	
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
	rocket = sync_create_device("Nasa/sync");
	if (!rocket)
		std::cout << "failed to open device" << std::endl;

#ifndef SYNC_PLAYER
	if (sync_connect(rocket, "localhost", SYNC_DEFAULT_PORT))
		std::cout << "failed to connect to host" << std::endl;
#endif

	TrackPart = sync_get_track(rocket, "part");


	plane_Pos_X = sync_get_track(rocket, "Ppos.x");
	plane_Pos_Y = sync_get_track(rocket, "Ppos.y");
	plane_Pos_Z = sync_get_track(rocket, "Ppos.z");
	plane_Rot_X = sync_get_track(rocket, "Prot.x");
	plane_Rot_Y = sync_get_track(rocket, "Prot.y");
	plane_Rot_Z = sync_get_track(rocket, "Prot.z");
	plane_Sca_X = sync_get_track(rocket, "Psca.x");
	plane_Sca_Y = sync_get_track(rocket, "Psca.y");
	plane_Sca_Z = sync_get_track(rocket, "Psca.z");
	



	cam_Pos_X = sync_get_track(rocket, "cam.x"),
	cam_Pos_Y = sync_get_track(rocket, "cam.y");
	cam_Pos_Z = sync_get_track(rocket, "cam.z");
	

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


	litG_Pos_X = sync_get_track(rocket, "GLpos.x");
	litG_Pos_Y = sync_get_track(rocket, "GLpos.y");
	litG_Pos_Z = sync_get_track(rocket, "GLpos.z");

	litY_Pos_X = sync_get_track(rocket, "YLpos.x");
	litY_Pos_Y = sync_get_track(rocket, "YLpos.y");
	litY_Pos_Z = sync_get_track(rocket, "YLpos.z");

	litR_Pos_X = sync_get_track(rocket, "RLpos.x");
	litR_Pos_Y = sync_get_track(rocket, "RLpos.y");
	litR_Pos_Z = sync_get_track(rocket, "RLpos.z");

	litB_Pos_X = sync_get_track(rocket, "BLpos.x");
	litB_Pos_Y = sync_get_track(rocket, "BLpos.y");
	litB_Pos_Z = sync_get_track(rocket, "BLpos.z");

	gridDrop = sync_get_track(rocket, "gridFunc");

	dodoOpen = sync_get_track(rocket, "dodo_Open_Deg");
	UtilityTrack = sync_get_track(rocket, "Utility");



	PlaneSync = NS_SG::objectAnim();
	CameraSync = NS_SG::objectAnim();

	

//------adds node to scene  (should do this when created to help  sort shit out)
	o_loader->addChild(tran_protagonist.get());

	//o_loader->addChild()

	o_loader->addChild(tran_cavern.get());
	
	o_loader->addObjectAnime(tran_kambot.get(), CameraSync);



	ptrComp = o_loader.get();


	NS_ENG::rendrer* mRender = new NS_ENG::rendrer(o_loader.get(), kambot.get(), n_sphereL.get(), n_sphereN.get(), n_quad.get());



	mRender->Run();


//#ifndef SYNC_PLAYER
//	sync_save_tracks(rocket);
//#endif

	sync_destroy_device(rocket);
	return 0;
}
