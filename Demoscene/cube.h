#ifndef CUBE_HPP
#define CUBE_HPP

#include "actors.h"

namespace sg {
	namespace noder {


		class cube : public actors
		{
		public:

			cube();
			cube(GLfloat, GLfloat, GLfloat, bool);

			virtual void draw();



		};




	}
}



#endif