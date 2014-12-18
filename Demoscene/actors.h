#ifndef ACTORS_HPP
#define ACTORS_HPP
#include <iostream>
#include "vec.h"
#include "math3d.h"
//#include "world.h"
#include <boost/enable_shared_from_this.hpp>
#include <deque>
#include <map>


//using namespace std;
//using namespace gl;
using namespace NS_VEC;

namespace sg {
	namespace noder {

		typedef boost::shared_ptr< class actors > actorsPtr;
		typedef boost::shared_ptr< const class actors > node;
		typedef boost::weak_ptr< class actors > svakRef;
        //parent???
		typedef std::deque< actorsPtr > Nodes;
		typedef std::map< unsigned int, svakRef> NodeKart;



		class actors
		{
		public:
			VEC3 pos;
			VEC3 up;
			VEC3 forward;

			VEC3 v; // * t
			VEC3 a; // * t
			//model matrise her

			//M3DMatrix44f Model;

			//forward
			//rotation
			//scale
			bool mvm;

			actors();
			actors(GLfloat x, GLfloat y, GLfloat z, bool move);

			void SetModel();
			void Transform();
			void Rotate();
			void Scale();


			virtual void draw()
			{}
		protected:
			M3DMatrix44f Model;

		};

	}
}
#endif
