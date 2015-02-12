#pragma once

#include "freeglut.h"
#include "gbuffer.h"

namespace NS_REND
{
	class context
	{
	public:

		GLuint Program;
		unsigned int Width, Breadth;

		context(unsigned int Width, unsigned int Breadth);
		~context();

		void Init();
		void InitWindow();




	};

}