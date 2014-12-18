#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

//#include "world.h"
#include <iostream>
#include "Timer.h"
#include "boost/shared_ptr.hpp"
#include <vector>
#include "actors.h"
#include "circle.h"
#include "cube.h"
#include "pyramid.h"
#include "model.h"
#include "camera.h"

//#include <sync.h>



//#include <bass.h>

using namespace std;
namespace sg {
	namespace noder {





		class composite : public actors
		{


			Timer clock;
		public:

			composite(void);

			//void AddActor(GLfloat, GLfloat, GLfloat);

			void AddActor(int, GLfloat, GLfloat, GLfloat);
			void AddActor(VEC3, string, string, GLfloat, GLfloat, GLfloat);
			void Magic(bool);
			void DrawAll();
			void StartTimer();
			void SortTracks();



		};




	}
}


#endif