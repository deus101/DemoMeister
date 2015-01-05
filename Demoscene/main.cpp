#include "world.h"

//world as a scene object and going through a sceneloader?
world o_World;




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
	GLfloat fAspect;

	if (h == 0)
		h = 1;

	//gl::vie
	//startskudd for omskriving 

	gl::Viewport(0, 0, (GLsizei)w, (GLsizei)h);

	//fAspect = (GLfloat)w / (GLfloat)h;

	cout << "Changed Screen size!" << endl;


	//gluPerspective(35.0f, fAspect, 1.0f, 200.0f);


}



void callRenderScene()
{
	o_World.RenderScene();
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
	cout << "Minor version! : " << glload::GetMinorVersion() << endl;
	cout << "Major Version! : " << glload::GetMajorVersion() << endl;

	o_World.AfterInit();




}






int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitContextVersion(3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);

#ifdef DEBUG
	glutInitContextFlags(GLUT_DEBUG);
#endif
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(800, 600);
	//glutInitWindowPosition (300, 200);
	glutCreateWindow("Deus's Ex Machine");


	glload::LoadFunctions();
	if (gl::exts::var_ARB_debug_output)
	{
		gl::Enable(gl::DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		//gl::DebugMessageCallbackARB(, (void*)15);
	}

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
