#include "context.h"
#include <iostream>
#include <stdio.h>

using namespace NS_REND;

static bool sDepth = false;
static bool sStencil = false;

context::context()
{


}


context::~context()
{
}

void context::Init(int argc, char** arg, bool aDepth, bool aStencil)
{
	glutInit(&argc, arg);


	sDepth = aDepth;
	sStencil = aStencil;

	unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGBA;

	if (aDepth) {
		DisplayMode |= GLUT_DEPTH;
	}

	if (aStencil) {
		DisplayMode |= GLUT_STENCIL;
	}

	glutInitDisplayMode(DisplayMode);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);


	//not sure if I need this
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);

#ifdef _DEBUG
	glutInitContextFlags(GLUT_DEBUG);
#endif

}

bool context::InitWindow(unsigned int aWidth, unsigned int aHeight, bool fs, const char* aTitle)
{
	pWidth = aWidth;
	pHeight = aHeight;

	glutInitWindowSize(aWidth, aHeight);
	glutCreateWindow(aTitle);


	glload::LoadTest test = glload::LoadFunctions();

	if (!test)
		return false;

	if (gl::exts::var_ARB_debug_output)
	{
		gl::Enable(gl::DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		//gl::DebugMessageCallbackARB(, (void*)15);
	}

	std::cout << "Minor version! : " << glload::GetMinorVersion() << std::endl;
	std::cout << "Major Version! : " << glload::GetMajorVersion() << std::endl;
	
	//maybe some checks to see if you really need it?
	//I should have a sorta enum argumented function that sorts out the different bind draw commands
	mGBuffer.Init(aWidth, aHeight);

	return true;
}
