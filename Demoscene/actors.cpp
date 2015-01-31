#include "actors.h"
//#include "shaders.h"
//extern Shader_Progs o_progs;


//fuck did i do here?
//def boost::shared_ptr< actors > node;
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
			
			position = pos;
			rotation = QUAT(0.0f, 0.0f, 0.0f, 0.0f);
			scale = 1.0f;
			bool DirtyMat = true;

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
			rotation = QUAT(0.0f, 0.0f, 0.0f, 0.0f);
			
			scale = 1.0f;
			bool DirtyMat = true;
			mvm = move;

			this->SetModel();

		}


		//model matrix
		void actors::SetModel()
		{
			m3dLoadIdentity44(Model);
			M3DMatrix44f temp;
			m3dLoadIdentity44(temp);
			//temp[3] = pos.X;
			//temp[7] = pos.Y;
			//temp[11] = pos.Z;
			//er dette nødvendig?
			temp[12] = pos.X;
			temp[13] = pos.Y;
			temp[14] = pos.Z;

			m3dMatrixMultiply44(Model, Model, temp);


			std::cout << "Model Matrix: " << std::endl;
			std::cout << Model[0] << "  " << Model[4] << "  " << Model[8] << "  " << Model[12] << std::endl;
			std::cout << Model[1] << "  " << Model[5] << "  " << Model[9] << "  " << Model[13] << std::endl;
			std::cout << Model[2] << "  " << Model[6] << "  " << Model[10] << "  " << Model[14] << std::endl;
			std::cout << Model[3] << "  " << Model[7] << "  " << Model[11] << "  " << Model[15] << std::endl;





		}

		void actors::Transform()
		{
			
			M3DMatrix44f m_scale;
			m3dLoadIdentity44(m_scale);
			m3dScaleMatrix44(m_scale, scale, scale, scale);
				//m3dMatrixMultiply44(Model, Model, m_scale);
				//quite horrible
				//using quaternions now
				M3DMatrix44f m_rot;
			
				//m3dLoadIdentity44(m_rot);

				//m3dRotationMatrix33()

				m3dRotationMatrix44(m_rot, rotation);
				//m3dRotationMatrix44(m_rot, m3dDegToRad(d), r.X, r.Y, r.Z);
				//Model = m_scale * m_rot;

				//m3dInvertMatrix44(m_rot, m_rot);

				m3dMatrixMultiply44(m_rot, m_scale, m_rot);

				M3DMatrix44f m_tran;
				m3dLoadIdentity44(m_tran);
				m3dTranslationMatrix44(m_tran, pos.X, pos.Y, pos.Z);


				m3dMatrixMultiply44(m_tran, m_rot, m_tran);

				m3dCopyMatrix44(Model, m_rot);
				
				//Model[3] = pos.X;
				//Model[7] = pos.Y;
			    //Model[11] = pos.Z;
				
				Model[12] = pos.X;
				Model[13] = pos.Y;
				Model[14] = pos.Z;
				
				DirtyMat = false;

		}

		void  actors::TranslateLocal(GLfloat x, GLfloat y, GLfloat z)
		{
			// need some if transformed shit for this
			this->pos.X = x;//12 13 abd 14 stupid!
			this->pos.Y = y;
			this->pos.Z = z;
			


			DirtyMat = true;
			//M3DMatrix44f Translate;
		//	m3dTranslationMatrix44(Translate, x, y, z);

		}


		void  actors::RotateLocal(GLfloat degrees, GLfloat x, GLfloat y, GLfloat z)
		{
			
			//rotation.NormIt();
			this->rotation = QUAT(degrees, x, y, z);

			DirtyMat = true;
			/*
			M3DMatrix44f Rotate;
			
			m3dRotationMatrix44(Rotate, m3dDegToRad(degrees), x, y, z);

			m3dMatrixMultiply44(Model, Model, Rotate);
			*/

		}

		void  actors::RotateLocal(const QUAT& qRot)
		{ 
			/*
			VEC3 axRot;
			float axDeg;
			qRot.TAA(axRot, axDeg);
			this->rotation.X = axRot.X;
			this->rotation.Y = axRot.Y;
			this->rotation.Z = axRot.Z;
			this->degree = axDeg;
			*/
			this->rotation = qRot;

			DirtyMat = true;
			/*
			M3DMatrix44f Rotate;

			m3dRotationMatrix44(Rotate, m3dDegToRad(degrees), x, y, z);

			m3dMatrixMultiply44(Model, Model, Rotate);
			*/

		}
		void actors::ScaleLocal(float W)
		{
			

			this->scale = W;
			DirtyMat = true;


		}


	}
}
