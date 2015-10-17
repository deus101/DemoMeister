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


static void InitCallbacks()
{
	//glutDisplayFunc(RenderSceneCB);
	//glutIdleFunc(IdleCB);
	//glutSpecialFunc(SpecialKeyboardCB);
	//glutPassiveMotionFunc(PassiveMouseCB);
	//glutKeyboardFunc(KeyboardCB);
	//glutMouseFunc(MouseCB);
}


void ErrorCallback(int error, const char* description)
{
#ifdef WIN32
	char msg[1000];
	_snprintf_s(msg, sizeof(msg), "GLFW error %d - %s", error, description);
	MessageBoxA(NULL, msg, NULL, 0);
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

	//wglShareLists()

	sDepth = aDepth;
	sStencil = aStencil;

	//glutInit(&argc, arg);
	//GLFWmonitor* primary = glfwGetPrimaryMonitor();
	//const GLFWvidmode* mode = glfwGetVideoMode(primary);



	if (glfwInit() != 1) {
		//ENG_ERROR("Error initializing GLFW");
		exit(1);
	}

	int Major, Minor, Rev;

	glfwGetVersion(&Major, &Minor, &Rev);

	printf("GLFW %d.%d.%d initialized\n", Major, Minor, Rev);

	glfwSetErrorCallback(ErrorCallback);

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//GBuffer* ss = new GBuffer();
	//ss->Init(500, 500);





	pWidth = aWidth;
	pHeight = aHeight;


	GLFWmonitor* pMonitor = fs ? glfwGetPrimaryMonitor() : NULL;
	//GLFWmonitor* pm = glfwGetPrimaryMonitor();
	//const GLFWvidmode* mode = glfwGetVideoMode(pm);

	//glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	//glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	//glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	//glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	glfwWindowHint(GLFW_DOUBLEBUFFER, gl::TRUE_);
	
	s_pWindow = glfwCreateWindow(aWidth, aHeight, aTitle, pMonitor, NULL);

	if (!s_pWindow) {
		//OGLDEV_ERROR("error creating window");
		exit(1);
	}
	glfwMakeContextCurrent(s_pWindow);

	// Must be done after glfw is initialized!
	glload::LoadTest test = glload::LoadFunctions(); //DeviceContext
	std::cout << "Minor version! : " << glload::GetMinorVersion() << std::endl;
	std::cout << "Major Version! : " << glload::GetMajorVersion() << std::endl;
	
	if (!test) {
		//OGLDEV_ERROR((const char*)glewGetErrorString(res));
		exit(1);
	}




	//mgBuffer = new GBuffer();
	//mgBuffer->Init(pWidth, pHeight, s_pWindow);
	//GBuffer* mGBuffer = new GBuffer();
	//mGBuffer->Init(500, 500);

	return s_pWindow;



}

//glem denne for nå
void ChangeSize(unsigned int w, unsigned int h)
{
	GLfloat fAspect;

	if (h == 0)
		h = 1;

	//gl::vie
	//startskudd for omskriving 

	gl::Viewport(0, 0, (GLsizei)w, (GLsizei)h);

	//fAspect = (GLfloat)w / (GLfloat)h;

	std::cout << "Changed Screen size!" << std::endl;
	
	pWidth = w;
	pHeight = h;

	ResizeBuffer = TRUE;
		//gluPerspective(35.0f, fAspect, 1.0f, 200.0f);

	//context::mGBuffer->Init(w, h);
}
//mulig en callback classe her med en app classe
void ContextRun(ICallbacks* pCallbacks)
{
	if (!pCallbacks) {
		//ENG_ERROR("callbacks not specified");
		exit(1);
	}

	gl::ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gl::FrontFace(gl::CCW);
	gl::CullFace(gl::BACK);
	gl::Enable(gl::CULL_FACE);

	if (sDepth) {
		gl::Enable(gl::DEPTH_TEST);
	}

	s_pCallbacks = pCallbacks;
	InitCallbacks();

	while (!glfwWindowShouldClose(s_pWindow)) {
		s_pCallbacks->RenderSceneCB();
		glfwSwapBuffers(s_pWindow);
		glfwPollEvents();
	}
	

}

void Swap()
{
	
	//glutSwapBuffers();

}

void LeaveMainLoop()
{
	glfwSetWindowShouldClose(s_pWindow, 1);
	//glutLeaveMainLoop();
}
//unsigned int context::GetPixelWidth() const
//{
//	return pWidth;
//}
//
//unsigned int context::GetPixelHeight() const
//{
//
//	return pHeight;
//}
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