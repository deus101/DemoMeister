#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "actors.h"
#include "math3d.h"
//#include "world.h"
namespace sg {
	namespace noder {

		class camera : public actors
		{
		public:
			int viewport[4];


			//M3DMatrix44f View;
			//M3DMatrix44f Projection;
			//M3DMatrix44f Ortho;

			camera();
			camera(GLfloat, GLfloat, GLfloat, bool);
			virtual void draw();
			void SetProjection();
			void SetView();
			void LookAt();
			void EasyMV();
		protected:
			VEC3  L;
			M3DMatrix44f View;
			M3DMatrix44f Projection;
			M3DMatrix44f ViewInv;





		};

	}
}


#endif