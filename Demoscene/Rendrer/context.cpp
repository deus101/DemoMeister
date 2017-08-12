#include "context.h"
#include <iostream>
#include <stdio.h>

//#include <GLFW/glfw3.h>
//#include <GL\wglew.h>
//#include <GL\glew.h>
//#include <GL\wglew.h>

//using namespace NS_REND;

static ICallbacks* s_pCallbacks = NULL;


bool sDepth = false;
bool sStencil = false;
GLFWwindow* s_pWindow = NULL;


unsigned int pHeight = 0;
unsigned int pWidth = 0;
bool m_created = false;


DeploymentOrganizer Squiddy;
DemoMeister *TheDisc = NULL;
extern void Sync();


//static unsigned int pHeight = 0;
//static unsigned int pWidth = 0;
//static bool m_created;
//HGLRC context::SharedContex;
 //int context::Glu_Window;
// HGLRC context::RendContext = 0;
// HDC context::DeviceContext;
//bool context::ResizeBuffer;

//context::context()
//{
//	
//
//}
//
//
//context::~context()
//{
//
//
//}


static void RenderSceneCB()
{
	s_pCallbacks->RenderSceneCB();
}


static void IdleCB()
{
	s_pCallbacks->RenderSceneCB();
	
}


 void InitCallbacks()
{
	//I'm beginning to think I should utilize the DemoMeister class

	//glutDisplayFunc(RenderSceneCB);
	//glutIdleFunc(IdleCB);
	//glutSpecialFunc(SpecialKeyboardCB);
	//glutPassiveMotionFunc(PassiveMouseCB);
	//glutKeyboardFunc(KeyboardCB);
	//glutMouseFunc(MouseCB);
	
	glfwSetKeyCallback(s_pWindow, KeyboardCB);
}


void ErrorCallback(int error, const char* description)
{
#ifdef WIN32
	char msg[1000];
	_snprintf_s(msg, sizeof(msg), "GLFW error %d - %s", error, description);
	//MessageBoxA(NULL, msg, NULL, 0);
#else
	fprintf(stderr, "GLFW error %d - %s", error, description);
#endif    
	exit(0);
}

void GLFWBackendTerminate()
{
	glfwDestroyWindow(s_pWindow);
	glfwTerminate();
}


bool Init(int argc, char** arg, bool aDepth, bool aStencil, unsigned int aWidth, unsigned int aHeight, bool fs, const char* aTitle, DemoMeister * globe)
{


	sDepth = aDepth;
	sStencil = aStencil;
	
	//GL_CONTEXT_COMPATIBILITY_PROFILE_BIT
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (glfwInit() != 1) {
		exit(1);
	}





	int Major, Minor, Rev;

	glfwGetVersion(&Major, &Minor, &Rev);

	printf("GLFW %d.%d.%d initialized\n", Major, Minor, Rev);

	glfwSetErrorCallback(ErrorCallback);

	//context
	//wglCreateContextAttribsARB()
	pWidth = aWidth;
	pHeight = aHeight;


	GLFWmonitor* pMonitor = fs ? glfwGetPrimaryMonitor() : NULL;
	
	glfwWindowHint(GLFW_REFRESH_RATE, 60);

	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	//glfwWindowHint(GLFw, GL_TRUE);
	
	s_pWindow = glfwCreateWindow(aWidth, aHeight, aTitle, pMonitor, NULL);
	
	glfwSetInputMode(s_pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	if (!s_pWindow) {
		exit(1);
	}
	glfwMakeContextCurrent(s_pWindow);

	glewExperimental = true;
	
	//glew
	int glewErr = glewInit();
	//if (!glewErr) {
	//		exit(1);
	//}

	GLint max_texture_units, max_combined_texture_units;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_units);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_combined_texture_units);

	TheDisc = globe;

	TheDisc->ResolutionX = pWidth;
	TheDisc->ResolutionY = pHeight;
	//mgBuffer = new GBuffer();
	//mgBuffer->Init(pWidth, pHeight, s_pWindow);
	//mGBuffer->Init(500, 500);

	return s_pWindow;



}

//glem denne for nå
void ChangeSize(unsigned int w, unsigned int h)
{
	GLfloat fAspect;

	if (h == 0)
		h = 1;

	//startskudd for omskriving 

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	//fAspect = (GLfloat)w / (GLfloat)h;

	std::cout << "Changed Screen size!" << std::endl;
	
	pWidth = w;
	pHeight = h;

	ResizeBuffer = true;



	//context::mGBuffer->Init(w, h);



}
//mulig en callback classe her med en app classe
void ContextRun(ICallbacks* pCallbacks)
{
	if (!pCallbacks) {
		exit(1);
	}
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	if (sDepth) {
		glEnable(GL_DEPTH_TEST);
	}

	s_pCallbacks = pCallbacks;
	InitCallbacks();

	while (!glfwWindowShouldClose(s_pWindow)) {


		Sync();
		//bruke en callback her for rocket?
		s_pCallbacks->RenderSceneCB();
		//glfwSwapBuffers(s_pWindow);
		glfwPollEvents();
	}
	

}

void Swap()
{
	glfwSwapBuffers(s_pWindow);
		
}

void LeaveMainLoop()
{
	glfwSetWindowShouldClose(s_pWindow, 1);

}
unsigned int GetPixelWidth()
{
	return pWidth;
}

unsigned int GetPixelHeight() 
{

	return pHeight;
}

/*
float GetDeltaTime()
{

	return float(deltaTime);


}

double GetDeltaTimeD()
{

	return deltaTime;
}
*/

//
//bool context::GetGBStatus() const
//{
//	return ResizeBuffer;
//}
//
//void context::SetGBStatus(bool state) const
//{
//	ResizeBuffer = state;
//}