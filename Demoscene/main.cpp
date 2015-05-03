#include "world.h"
#include <iostream>
#include "bass.h"

#include "sync.h"
//world as a scene object and going through a sceneloader?
#include "Rendrer\context.h"
#include "Engine\rendrer.h"
#include "SceneGraph\assetNode.h"
#include "SceneGraph\modelNode.h"
#include "SceneGraph\dirLightNode.h"
#include "SceneGraph\pointLightNode.h"
#include "SceneGraph\dirLightNode.h"
#include "SceneGraph\targetNode.h"
NS_REND::context *mContext;
NS_ENG::rendrer *mRender;




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





void TimerFunction(int)
{

	glutPostRedisplay();
	glutTimerFunc(3, TimerFunction, 1);

}
void IdleFunc()
{
	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{


	mContext->ChangeSize(w, h);
	//GLfloat fAspect;

	//if (h == 0)
	//	h = 1;

	//gl::vie
	//startskudd for omskriving 

	//gl::Viewport(0, 0, (GLsizei)w, (GLsizei)h);

	//fAspect = (GLfloat)w / (GLfloat)h;

	//cout << "Changed Screen size!" << endl;
	//std::

	//gluPerspective(35.0f, fAspect, 1.0f, 200.0f);


}



void callRenderScene()
{
	mContext->Run();
	
	mRender->draw();
	mContext->Swap();
}


void SetupRC()
{
	glload::LoadFunctions();
	
	//if(glload::LoadFunctions() == glload::)
	//{

	//glutSwapBuffers();
	//Sleep(2000);
	//exit(0);
 //   }
	
	//glload::LoadWinFunctions(


	//o_World.AfterInit();
	/*
	sg::noder::composite test("test");

	model("Mesh/p38.obj", "Mesh/p38.mtl");
	*/
	//nei faen den er en attributt nå den!
	
	

	//o_loader

	

	//test.findChild("hoo");
}






int main(int argc, char** argv)
{
	mContext = new NS_REND::context();
	mContext->Init(argc, argv, true, false);

	//glutInit(&argc, argv);

	std::cout << "Result of init windows: " << mContext->InitWindow(800, 600, false, "Deus's Ex Machine") << std::endl;

	//glutInitWindowPosition(-1, -1);




	//o_World.WindowID = 
	//    glutIgnoreKeyRepeat(1);

	//    glutSpecialFunc( keyBoard );
	//    glutSpecialUpFunc( callKeyRelease );

	//SetupRC();
	//DO IT! TO IT!



	boost::shared_ptr<NS_SG::composite> o_loader(new NS_SG::composite("lader"));

	//NS_SG::camera kambot = NS_SG::camera("kambot");
	boost::shared_ptr<NS_SG::camera> kambot(new NS_SG::camera("kambot"));
	//NS_SG::modelNode plane = NS_SG::modelNode
	//NS_SG::objTransform tran_kambot = NS_SG::objTransform("tran_kambot");
	boost::shared_ptr<NS_SG::objTransform> tran_kambot(new NS_SG::objTransform("tran_kambot"));
	boost::shared_ptr<NS_SG::targetTransform> target_kambot(new NS_SG::targetTransform("target_kambot"));


	tran_kambot->setPosition(NS_VEC::VEC3(0.0f, 1.0f, -2.0f));

	target_kambot->addChild(kambot.get());
	//husk
	//o_loader->addChild(&tran_kambot);


	NS_ENG::model fly(*mContext, "Mesh/p38.obj", "Mesh/p38.mtl");
	//NS_SG::modelNode()

	NS_EFF::GeomPacket e_geom = NS_EFF::GeomPacket();


	NS_EFF::PointLightPacket e_point = NS_EFF::PointLightPacket();

	NS_EFF::NullPacket e_null = NS_EFF::NullPacket();

	NS_EFF::DirLightPacket e_dir = NS_EFF::DirLightPacket();
	
	

	std::cout << "Status of geometry effect is: " << e_geom.Init() << std::endl;

	std::cout << "Status of point light effect is: " << e_point.Init() << std::endl;

	std::cout << "Status of dir light effect is: " << e_dir.Init() << std::endl;

	std::cout << "Status of null effect is: " << e_null.Init() << std::endl;

	//this should not be started here.
	//e_geom.Enable();

	//NS_SG::modelNode n_fly = NS_SG::modelNode("plane", &fly, &e_geom);
	boost::shared_ptr<NS_SG::modelNode> n_fly(new NS_SG::modelNode("plane", &fly, &e_geom));
	//NS_SG::objTransform tran_fly = NS_SG::objTransform("tran_plane");
	boost::shared_ptr<NS_SG::objTransform> tran_fly(new NS_SG::objTransform("tran_plane"));
	tran_fly->setPosition(NS_VEC::VEC3(0.0f, 1.0f, 0.0f));


	target_kambot->setTarget(n_fly.get());

	tran_fly->addChild(n_fly.get());


	tran_kambot->addChild(target_kambot.get());
	o_loader->addChild(tran_kambot.get());

	o_loader->addChild(tran_fly.get());


	//boost::shared_ptr<NS_SG::dirLightNode> n_dir_lys(new NS_SG::dirLightNode("DirLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f));

																													
	boost::shared_ptr<NS_SG::pointLightNode> n_point_lys(new NS_SG::pointLightNode("PointLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f, 0.0f, 0.0f, 0.3f, &e_point, &e_null));
	boost::shared_ptr<NS_SG::objTransform> tran_Point(new NS_SG::objTransform("tran_PointLys"));
	tran_Point->setPosition(NS_VEC::VEC3(1.0f, 2.0f, 0.0f));

	//boost::shared_ptr<NS_SG::objTransform> tran_Point2(new NS_SG::objTransform("tran_PointLys2"));
	//tran_Point2->setPosition(NS_VEC::VEC3(1.0f, 2.0f, 0.0f));

	tran_Point->addChild(n_point_lys.get());
	//tran_Point2->addChild(tran_Point.get());
	o_loader->addChild(tran_Point.get());
	boost::shared_ptr<NS_SG::dirLightNode> n_dir_lys(new NS_SG::dirLightNode("DirLys", NS_VEC::VEC3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f, &e_dir));
	
	boost::shared_ptr<NS_SG::objTransform> tran_Dir(new NS_SG::objTransform("tran_DirLys"));

	tran_Dir->setPosition(NS_VEC::VEC3(-10.0f, 5.0f, 0.0f));
	tran_Dir->setRotation(NS_VEC::QUAT(-45.0f, 90.0f, 0.0f));
	tran_Dir->addChild(n_dir_lys.get());

	o_loader->addChild(tran_Dir.get());
	

	mRender = new NS_ENG::rendrer(o_loader.get(), kambot.get(), mContext);



	//STOP DEFINING THE SHIT!
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(callRenderScene);
	glutTimerFunc(33, TimerFunction, 1);
	glutIdleFunc(IdleFunc);
	//glutFullScreen();
	glutMainLoop();


	return 0;
}
