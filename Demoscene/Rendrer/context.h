#pragma once

#include <glload/gl_3_3.hpp>
#include <glload/gl_load.hpp>
#include <GL/freeglut.h>
//#include "freeglut.h"
#include "gbuffer.h"

namespace NS_REND
{
	class context
	{
	public:
		static GBuffer * mGBuffer;

		GLuint Program;


		context();
		~context();

		static void Init(int argc, char** arg, bool aDepth, bool aStencil);
		static bool InitWindow(unsigned int Width, unsigned int Height, bool fs, const char* aTitle);

		void ChangeSize(unsigned int w, unsigned int h);
		static void Run();

		static void Swap();

		unsigned int GetPixelWidth() const;

		unsigned int GetPixelHeight() const;




	private:


	};
		
	static unsigned int pHeight;
	static unsigned int pWidth;
	static bool m_created;
	//static GBuffer * mGBuffer;



	

}