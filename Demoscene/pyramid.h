#ifndef PYRAMID_HPP
#define PYRAMID_HPP

#include "actors.h"
#include "mesh.h"

using namespace NS_MESH;
namespace sg {
	namespace noder {

		class pyramid : public actors
		{
		public:

			pyramid();
			pyramid(GLfloat, GLfloat, GLfloat, bool);

			virtual void draw();

		public:

			MESH dodo;


		};


	}
}

#endif