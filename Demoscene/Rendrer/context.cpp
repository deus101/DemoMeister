#include "context.h"
#include <iostream>
#include <stdio.h>

//using namespace NS_REND;

static ICallbacks* s_pCallbacks = NULL;
//mGBuffer =  GBuffer;
//mGBuffer = NULL;
static bool sDepth = false;
static bool sStencil = false;
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
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(IdleCB);
	//glutSpecialFunc(SpecialKeyboardCB);
	//glutPassiveMotionFunc(PassiveMouseCB);
	//glutKeyboardFunc(KeyboardCB);
	//glutMouseFunc(MouseCB);
}


void Init(int argc, char** arg, bool aDepth, bool aStencil)
{

	//wglShareLists()

	sDepth = aDepth;
	sStencil = aStencil;

	glutInit(&argc, arg);


	unsigned int DisplayMode = GLUT_DOUBLE ;
	//unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RENDERING_CONTEXT | GLUT_USE_CURRENT_CONTEXT;


	if (aDepth) {
		DisplayMode |= GLUT_DEPTH;
	}

	if (aStencil) {
		DisplayMode |= GLUT_STENCIL;
	}

	glutInitDisplayMode(DisplayMode);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//glutSetOption(GLUT_RENDERING_CONTEXT , GLUT_USE_CURRENT_CONTEXT);

	
	//glutInitContextVersion(3, 3);
	//glutInitContextProfile(GLUT_CORE_PROFILE);

#ifdef _DEBUG
	glutInitContextFlags(GLUT_DEBUG);
#endif
	//HGLRC initContext = wglGetCurrentContext();
	//bool hei = false;

}

bool InitWindow(unsigned int aWidth, unsigned int aHeight, bool fs, const char* aTitle)
{
	pWidth = aWidth;
	pHeight = aHeight;

	glutInitWindowSize(aWidth, aHeight);
	Glu_Window = glutCreateWindow(aTitle);
	//DeviceContext = wglGetCurrentDC();
	
	//wglMakeCurrent()
	//RendContext = wglGetCurrentContext();
	//wglGetCurrentDC();
	//wglMakeCurrent(DeviceContext, RendContext);
	
	glload::LoadTest test = glload::LoadFunctions(); //DeviceContext
	if (!test)
		return false;
	//DeviceContext
	if (gl::exts::var_ARB_debug_output)
	{
		gl::Enable(gl::DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		//gl::DebugMessageCallbackARB(, (void*)15);

	}
	
	std::cout << "Minor version! : " << glload::GetMinorVersion() << std::endl;
	std::cout << "Major Version! : " << glload::GetMajorVersion() << std::endl;
	
	//maybe some checks to see if you really need it?
	//I should have a sorta enum argumented function that sorts out the different bind draw commands
	//SharedContex = wglCreateContext(DeviceContext); //wglGetCurrentContext();
	//bool ShareSuccess = wglShareLists(SharedContex, RendContext);
	//bool bGbuffer;
	//mGBuffer = new GBuffer();
	//Sure why not
	//ResizeBuffer = TRUE;
	//mGBuffer = new GBuffer();
	//mGBuffer->Init(pWidth, pHeight);
	//return ResizeBuffer;
	//mGBuffer ->Init(aWidth, aHeight);
	//bGbuffer =   Init(aWidth, aHeight);
	//return bGbuffer;
	//mGBuffer = new GBuffer();
	return true;
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
	std::cout << "Initialising MainLoop" << std::endl;

	gl::ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gl::FrontFace(gl::CW);
	gl::CullFace(gl::BACK);
	gl::Enable(gl::CULL_FACE);

	if (sDepth) {
		gl::Enable(gl::DEPTH_TEST);
	}

	s_pCallbacks = pCallbacks;
	InitCallbacks();

	//what why?
	glutMainLoop();
	

}

void Swap()
{
	
	glutSwapBuffers();

}

void LeaveMainLoop()
{
	glutLeaveMainLoop();
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