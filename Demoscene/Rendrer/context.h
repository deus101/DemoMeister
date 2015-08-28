#pragma once

#include <glload/gl_3_3.hpp>
#include <glload/gl_load.hpp>
#include <glload/wgl_load.hpp>
#include <GL/freeglut.h>
//#include "freeglut.h"
#include "gbuffer.h"
#include "callbacks.h"
//namespace NS_REND
//{
//	class context
//	{
//	public:
		
		//static GBuffer * mGBuffer = 0;

		static bool ResizeBuffer;
		
		static int glu_Window;
		static HGLRC RendContext;
		static HDC DeviceContext;
		static int Glu_Window;

		static HGLRC SharedContex;
		static GLuint Program;


		//context();
		//~context();

		void Init(int argc, char** arg, bool aDepth, bool aStencil);
		//static HGLRC InitWindow(unsigned int Width, unsigned int Height, bool fs, const char* aTitle);

		//static bool Init(int argc, char** arg, bool aDepth, bool aStencil, unsigned int Width, unsigned int Height, bool fs, const char* aTitle);
		bool InitWindow(unsigned int Width, unsigned int Height, bool fs, const char* aTitle);

		void ChangeSize(unsigned int w, unsigned int h);
		
		
		void ContextRun(ICallbacks* pCallbacks);

		void Swap();

		//unsigned int GetPixelWidth() ;

		//unsigned int GetPixelHeight() ;

		//bool GetGBStatus() ;

		//void SetGBStatus(bool) ;


	//private:


	//};
		
	static unsigned int pHeight;
	static unsigned int pWidth;
	static bool m_created;
	//static GBuffer * mGBuffer;



	

//}