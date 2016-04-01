#include "context.h"
#include <iostream>
#include <stdio.h>

//using namespace NS_REND;

static ICallbacks* s_pCallbacks = NULL;
//mGBuffer =  GBuffer;
//mGBuffer = NULL;
static bool sDepth = false;
static bool sStencil = false;
static GLFWwindow* s_pWindow = NULL;
//Buffer = NULL;


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
	//I'm beginning to think I should utilize the world class

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


bool Init(int argc, char** arg, bool aDepth, bool aStencil, unsigned int aWidth, unsigned int aHeight, bool fs, const char* aTitle)
{


	sDepth = aDepth;
	sStencil = aStencil;


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	if (glfwInit() != 1) {
		//ENG_ERROR("Error initializing GLFW");
		exit(1);
	}





	int Major, Minor, Rev;

	glfwGetVersion(&Major, &Minor, &Rev);

	printf("GLFW %d.%d.%d initialized\n", Major, Minor, Rev);

	glfwSetErrorCallback(ErrorCallback);



	pWidth = aWidth;
	pHeight = aHeight;


	GLFWmonitor* pMonitor = fs ? glfwGetPrimaryMonitor() : NULL;
	
	glfwWindowHint(GLFW_REFRESH_RATE, 60);
	/*
	GLFWmonitor* pm = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(pm);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	*/
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	
	s_pWindow = glfwCreateWindow(aWidth, aHeight, aTitle, pMonitor, NULL);
	glfwSetInputMode(s_pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	if (!s_pWindow) {
		exit(1);
	}
	glfwMakeContextCurrent(s_pWindow);


	int glewErr = glewInit();
	//if (!glewErr) {
	//		exit(1);
	//}




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
		//ENG_ERROR("callbacks not specified");
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

	//kansje denne burde være I main eller World.
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