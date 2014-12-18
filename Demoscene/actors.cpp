#include "actors.h"
//#include "shaders.h"
//extern Shader_Progs o_progs;



//typedef boost::shared_ptr< actors > node;
//typedef boost::shared_ptr< const actors >  actorsPtr;
//vector < actorsPtr > herd;
//fuck that shit
using namespace std;

namespace sg {
	namespace noder {

		actors::actors(void)
		{

			pos = VEC3(0.0f, 0.0f, 0.0f);
			up = VEC3(0.0f, 1.0f, 0.0f);
			forward = VEC3(0.0f, 0.0f, -1.0);

			v = VEC3(0.0f, 0.0f, 0.0f);
            a = VEC3(0.0f, 0.0f, 0.0f);

			mvm = false;
			this->SetModel();


		}

		actors::actors(GLfloat x, GLfloat y, GLfloat z, bool move)
		{

            pos = VEC3(x, y, z);
			up = VEC3(0.0f, 1.0f, 0.0f);
			forward = VEC3(0.0f, 0.0f, -1.0); //forward, Z etc

			v = VEC3(0.0f, 0.0f, 0.0f);
			a = VEC3(0.0f, 0.0f, 0.0f);
			mvm = move;

			this->SetModel();

		}


		//model matrix
		void actors::SetModel()
		{
			m3dLoadIdentity44(Model);
			M3DMatrix44f temp;
			m3dLoadIdentity44(temp);
			temp[3] = pos.X;
			temp[7] = pos.Y;
			temp[11] = pos.Z;

			//temp[12] = pos.X;
			//temp[13] = pos.Y;
			//temp[14] = pos.Z;

			m3dMatrixMultiply44(Model, Model, temp);



			std::cout << "Model Matrix: " << std::endl;
			std::cout << Model[0] << "  " << Model[4] << "  " << Model[8] << "  " << Model[12] << std::endl;
			std::cout << Model[1] << "  " << Model[5] << "  " << Model[9] << "  " << Model[13] << std::endl;
			std::cout << Model[2] << "  " << Model[6] << "  " << Model[10] << "  " << Model[14] << std::endl;
			std::cout << Model[3] << "  " << Model[7] << "  " << Model[11] << "  " << Model[15] << std::endl;





		}
		void Translate(GLfloat)
		{




		}


		void Rotate()
		{




		}
		void Scale()
		{




		}


	}
}
