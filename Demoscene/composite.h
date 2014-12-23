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



//ubrukelig?
//Kansje jeg kan bruke den til noe annet men kompositt slik kan ikke brukes i en scanegraph 
//fordi data og noder bør holdes seperat.


//OOOOR! I can  use the actors system as leafnodes.

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