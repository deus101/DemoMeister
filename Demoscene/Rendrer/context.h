#pragma once

#include <glload/gl_3_3.hpp>
#include <glload/gl_load.hpp>
#include <gl/freeglut.h>
//#include "freeglut.h"
#include "gbuffer.h"

namespace NS_REND
{
	class context
	{
	public:

		GLuint Program;
		GBuffer mGBuffer;

		context();
		~context();

		void Init(int argc, char** arg, bool aDepth, bool aStencil);
		bool InitWindow(unsigned int Width, unsigned int Height, bool fs, const char* aTitle);

		void ChangeSize(unsigned int w, unsigned int h);
		void Run();

		void Swap();

		unsigned int GetPixelWidth() const;

		unsigned int GetPixelHeight() const;


	private:
	
		unsigned int pWidth, pHeight;
		bool m_created;


	};

}