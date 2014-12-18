#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "actors.h"

namespace sg {
	namespace noder {

		class circle : public actors
		{
		public:



			circle();
			circle(GLfloat, GLfloat, GLfloat, GLfloat, bool);

			virtual void draw();


		public:

			GLdouble r;


		};

	}
}

#endif