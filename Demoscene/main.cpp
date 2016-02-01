#include "world.h"
#include <iostream>
#include "bass.h"

#include "sync.h"
//world as a scene object and going through a sceneloader?
#include "Rendrer\context.h"
#include "Engine\rendrer.h"
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

NS_SG::objectAnim PlaneSync, CameraSync;

NS_SG::composite *ptrComp;
NS_SG::objTransform *ptrCamTran;
NS_SG::objTransform *ptrTranProt;
NS_SG::objTransform *ptrLitPlan;



static const float bpm = 150.0f; /* beats per minute */
static const int rpb = 8; /* rows per beat */
static const double row_rate = (double(bpm) / 60) * rpb;


static double bass_get_row(HSTREAM h)
{
	QWORD pos = BASS_ChannelGetPosition(h, BASS_POS_BYTE);
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


void Sync()
{
	
	double row = bass_get_row(stream);
	
	if (sync_update(rocket, (int)floor(row), &bass_cb, (void *)&stream))
		sync_connect(rocket, "localhost", SYNC_DEFAULT_PORT);


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
	
	//mContext = new NS_REND::context();
	
	
	


	bool success = Init(argc, argv, true, false, 1600, 900, false, "Deus's Ex Machine");

	
	std::cout << "Result of init windows: " << success << std::endl;



	std::cout << "X! : " << pWidth  << std::endl;
	std::cout << "Y! : " << pHeight  << std::endl;
	glViewport(0, 0, (GLsizei)1600, (GLsizei)900);


	//SetupRC();
	//DO IT! TO IT!

//-------------------The effects packets 
	NS_EFF::GeomPacket e_geom = NS_EFF::GeomPacket();


	NS_EFF::PointLightPacket e_point = NS_EFF::PointLightPacket();

	NS_EFF::NullPacket e_null = NS_EFF::NullPacket();

	NS_EFF::DirLightPacket e_dir = NS_EFF::DirLightPacket();



	std::cout << "Status of geometry effect is: " << e_geom.Init() << std::endl;

	e_geom.Enable();
	e_geom.SetColorTextureUnit(COLOR_TEXTURE_UNIT_INDEX);


	std::cout << "Status of point light effect is: " << e_point.Init() << std::endl;

	e_point.Enable();

	e_point.SetPositionTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	e_point.SetColorTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	e_point.SetNormalTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	e_point.SetScreenSize(1600, 900);
	
	std::cout << "Status of dir light effect is: " << e_dir.Init() << std::endl;

	e_dir.Enable();
	e_dir.SetPositionTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	e_dir.SetColorTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	e_dir.SetNormalTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);

	e_dir.SetScreenSize(1600, 900);

	M3DMatrix44f WVP;
	m3dLoadIdentity44(WVP);
	e_dir.SetWVP(WVP);


	std::cout << "Status of null effect is: " << e_null.Init() << std::endl;

//--------------scene node that goes into scenerendrer
	//scene parser does not work because I suck at boost
	//NS_SG::composite  *test_Loader = NS_SG::parseScene("TestScene.xml");


	boost::shared_ptr<NS_SG::composite> o_loader(new NS_SG::composite("lader"));




//------------UnderGround Scene

	//m is for mesh/model  texture is included. 
	NS_ENG::model m_cavern("Mesh/cave.obj", "Mesh/cave.mtl");



	//NS_ENG::model fly( "Mesh/fixedP38.obj", "Mesh/newP38.mtl");


	//mn is for model node
	boost::shared_ptr<NS_SG::modelNode> mn_cavern(new NS_SG::modelNode("Scene_Cavern", &m_cavern, &e_geom));


	boost::shared_ptr<NS_SG::objTransform> tran_cavern(new NS_SG::objTransform("tran_cavern"));

	tran_cavern->setPosition(NS_VEC::VEC3(0.0f, 0.0f, 0.0f));
	tran_cavern->setRotation(NS_VEC::QUAT(0.0f, 90.0f, 0.0f));

	tran_cavern->addChild(mn_cavern.get());


	//details to Scene
	NS_ENG::model m_stalagmite("Mesh/Stalagmite.obj", "Mesh/Stalagmite.mtl");



	//a node can only have one parent
	boost::shared_ptr<NS_SG::modelNode> mn_stalagmite_1(new NS_SG::modelNode("Scene_Stalagmite_1", &m_stalagmite, &e_geom));
	boost::shared_ptr<NS_SG::objTransform> tran_stalagmite_1(new NS_SG::objTransform("tran_stalagmite_1"));
	tran_stalagmite_1->setPosition(NS_VEC::VEC3(2.0f, 10.0f, 10.0f));
	tran_stalagmite_1->addChild(mn_stalagmite_1.get());

	boost::shared_ptr<NS_SG::modelNode> mn_stalagmite_2(new NS_SG::modelNode("Scene_Stalagmite_2", &m_stalagmite, &e_geom));
	boost::shared_ptr<NS_SG::objTransform> tran_stalagmite_2(new NS_SG::objTransform("tran_stalagmite_2"));
	
	tran_stalagmite_2->addChild(mn_stalagmite_2.get());
	tran_stalagmite_2->setPosition(NS_VEC::VEC3(-3.0f, 10.0f, 10.0f));


	o_loader->addChild(tran_stalagmite_1.get());
	o_loader->addChild(tran_stalagmite_2.get());
//-------------------------------------me

	//WHY AM I SO DUMB! YOU CANT MAKE A HEDRON OUT OUT HEXAGONS ALONE!
	//NS_ENG::model m_HexBase("Mesh/HexBase.obj", "Mesh/HexBase.mtl");
	//NS_ENG::model m_HexArm("Mesh/HexArm.obj", "Mesh/HexArm.mtl");
	NS_ENG::model m_protagonist("Mesh/cube_texture.obj", "Mesh/cube_texture.mtl");

	//mn is for model node
	boost::shared_ptr<NS_SG::modelNode> mn_protoganist(new NS_SG::modelNode("protoganist", &m_protagonist, &e_geom));





	boost::shared_ptr<NS_SG::objTransform> tran_protagonist(new NS_SG::objTransform("tran_protoganist"));
	
	
	
	tran_protagonist->setPosition(NS_VEC::VEC3(0.0f, 0.0f, 0.0f));
	
	
	
	tran_protagonist->addChild(mn_protoganist.get());



	ptrTranProt = tran_protagonist.get();

	


	
//--------------------Camera 
	//1 for nowf
	

	boost::shared_ptr<NS_SG::camera> kambot(new NS_SG::camera("kambot"));


	boost::shared_ptr<NS_SG::objTransform> tran_kambot(new NS_SG::objTransform("tran_kambot"));
	boost::shared_ptr<NS_SG::targetTransform> target_kambot(new NS_SG::targetTransform("target_kambot"));


	
	
	target_kambot->setTarget(mn_protoganist.get());

	target_kambot->addChild(kambot.get());



	tran_kambot->setPosition(NS_VEC::VEC3(0.0f, 4.0f, 4.0f));
	
	

	tran_kambot->addChild(target_kambot.get());
	
	
	o_loader->addChild(tran_kambot.get());
	 


	ptrCamTran = tran_kambot.get();









//------------------Lights



	//boost::shared_ptr<NS_SG::dirLightNode> n_dir_lys(new NS_SG::dirLightNode("DirLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f));


	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys(new NS_SG::pointLightNode("PointLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 0.01f, 0.02f, 0.5f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point(new NS_SG::objTransform("tran_PointLys"));
	tran_Point->setPosition(NS_VEC::VEC3(0.0f, 2.0f, 0.0f));
	tran_Point->setScale(NS_VEC::VEC3(1.0f, 1.0f, 1.0f));

	//boost::shared_ptr<NS_SG::objTransform> tran_Point2(new NS_SG::objTransform("tran_PointLys2"));
	//tran_Point2->setPosition(NS_VEC::VEC3(1.0f, 2.0f, 0.0f));




	tran_Point->addChild(n_point_lys.get());
	//tran_Point2->addChild(tran_Point.get());

	ptrLitPlan = tran_Point.get();



	o_loader->addChild(tran_Point.get());




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
	stream = BASS_StreamCreateFile(false, "bf.ogg", 0, 0,
		BASS_STREAM_PRESCAN);
	if (!stream)
		std::cout << "failed to open tune" << std::endl;



//----------create rocket device
	//Should be up at first
	rocket = sync_create_device("sync");



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
	
	
	
	PlaneSync = NS_SG::objectAnim();
	CameraSync = NS_SG::objectAnim();

	

//------adds node to scene  (should do this when created to help  sort shit out)
	o_loader->addChild(tran_protagonist.get());

	o_loader->addChild(tran_cavern.get());

	o_loader->addObjectAnime(tran_kambot.get(), CameraSync);



	ptrComp = o_loader.get();


	NS_ENG::rendrer* mRender = new NS_ENG::rendrer(o_loader.get(), kambot.get(), n_sphereL.get(), n_sphereN.get(), n_quad.get());



	mRender->Run();



	sync_destroy_device(rocket);
	return 0;
}
