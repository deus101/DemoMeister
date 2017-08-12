#pragma once


/* <windef.h> and <gl.h>*/


#include <GL\glew.h>


#include <GLFW/glfw3.h>

//#include <GL\wglew.h>

#include "../util.h"

#include "../world.h"


#include "gbuffer.h"
#include "callbacks.h"

#include "../FreeImage.h"






		extern unsigned int pHeight;
		extern unsigned int pWidth;
		extern bool m_created;
		
		extern bool sDepth;
		extern bool sStencil;
		extern GLFWwindow* s_pWindow;


		//extern DeploymentOrganizer Squiddy;
		//static double deltaTime;
		//static double currentTime;

		static bool ResizeBuffer;
		
		static int glu_Window;
		//static HGLRC RendContext;
		//static HDC DeviceContext;
		static int Glu_Window;

		//static HGLRC SharedContex;
		//static GLuint Program;


		//static GBuffer* mgBuffer;
		extern DemoMeister * TheDisc;




		//context();
		//~context();
		void KeyboardCB(GLFWwindow* window, int key, int scancode, int action, int mods);

		void ErrorCallback(int error, const char* description);
		//void Init(int argc, char** arg, bool aDepth, bool aStencil);
		//static HGLRC InitWindow(unsigned int Width, unsigned int Height, bool fs, const char* aTitle);

		bool Init(int argc, char** arg, bool aDepth, bool aStencil, unsigned int Width, unsigned int Height, bool fs, const char* aTitle, DemoMeister *globe);


		void ChangeSize(unsigned int w, unsigned int h);
		
		
		void ContextRun(ICallbacks* pCallbacks);

		void Swap();

		void LeaveMainLoop();



		unsigned int GetPixelWidth();

		unsigned int GetPixelHeight();


		//bool GetGBStatus() ;

		//void SetGBStatus(bool) ;


	//private:


	//};
		

	//static GBuffer * mGBuffer;



	

//}