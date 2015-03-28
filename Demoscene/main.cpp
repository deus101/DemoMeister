#include "world.h"
#include <iostream>
#include "bass.h"

#include "sync.h"
//world as a scene object and going through a sceneloader?
#include "Rendrer\context.h"

NS_REND::context mContext;



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


	mContext.ChangeSize(w, h);
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
	mContext.Run();
}


void SetupRC()
{
	glload::LoadFunctions();
	/*
	if(glload::LoadFunctions() == glload::LS_LOAD_FAILED)
	{

	glutSwapBuffers();
	Sleep(2000);
	exit(0);
    }|
	*/
	//glload::LoadWinFunctions(
	std::cout << "Minor version! : " << glload::GetMinorVersion() << std::endl;
	std::cout << "Major Version! : " << glload::GetMajorVersion() << std::endl;

	//o_World.AfterInit();
	/*
	sg::noder::composite test("test");

	model("Mesh/p38.obj", "Mesh/p38.mtl");
	*/
	



	



}






int main(int argc, char** argv)
{

	mContext.Init(argc, argv, true, false);

	//glutInit(&argc, argv);

	mContext.InitWindow(800, 600, false, "Deus's Ex Machine");

	//glutInitWindowPosition(-1, -1);




	//o_World.WindowID = 
	//    glutIgnoreKeyRepeat(1);

	//    glutSpecialFunc( keyBoard );
	//    glutSpecialUpFunc( callKeyRelease );

	SetupRC();

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(callRenderScene);
	glutTimerFunc(33, TimerFunction, 1);
	//glutIdleFunc(IdleFunc);
	//glutFullScreen();
	glutMainLoop();


	return 0;
}
