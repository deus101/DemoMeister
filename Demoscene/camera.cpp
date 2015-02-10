////#include "camera.h"
////#include "shaders.h"
//#define DegToRad 0.01745329f
////extern Shader_Progs o_progs;
//
//
//
//		camera::camera() : node()
//		{
//
//			this->SetProjection();
//			cout << "Projection matrix: " << endl;
//			cout << Projection[0] << "  " << Projection[4] << "  " << Projection[8] << "  " << Projection[12] << endl;
//			cout << Projection[1] << "  " << Projection[5] << "  " << Projection[9] << "  " << Projection[13] << endl;
//			cout << Projection[2] << "  " << Projection[6] << "  " << Projection[10] << "  " << Projection[14] << endl;
//			cout << Projection[3] << "  " << Projection[7] << "  " << Projection[11] << "  " << Projection[15] << endl;
//
//			this->SetView();
//			cout << "View Matrix: " << endl;
//			cout << View[0] << "  " << View[4] << "  " << View[8] << "  " << View[12] << endl;
//			cout << View[1] << "  " << View[5] << "  " << View[9] << "  " << View[13] << endl;
//			cout << View[2] << "  " << View[6] << "  " << View[10] << "  " << View[14] << endl;
//			cout << View[3] << "  " << View[7] << "  " << View[11] << "  " << View[15] << endl;
//		}
//
//		camera::camera(GLfloat x, GLfloat y, GLfloat z, bool move) : actors(x, y, z, move)
//		{
//			this->SetProjection();
//			cout << "Projection matrix: " << endl;
//			cout << Projection[0] << "  " << Projection[4] << "  " << Projection[8] << "  " << Projection[12] << endl;
//			cout << Projection[1] << "  " << Projection[5] << "  " << Projection[9] << "  " << Projection[13] << endl;
//			cout << Projection[2] << "  " << Projection[6] << "  " << Projection[10] << "  " << Projection[14] << endl;
//			cout << Projection[3] << "  " << Projection[7] << "  " << Projection[11] << "  " << Projection[15] << endl;
//
//			this->SetView();
//			cout << "View Matrix: " << endl;
//			cout << View[0] << "  " << View[4] << "  " << View[8] << "  " << View[12] << endl;
//			cout << View[1] << "  " << View[5] << "  " << View[9] << "  " << View[13] << endl;
//			cout << View[2] << "  " << View[6] << "  " << View[10] << "  " << View[14] << endl;
//			cout << View[3] << "  " << View[7] << "  " << View[11] << "  " << View[15] << endl;
//
//
//		}
//
//		void camera::SetView(void)
//		{
//			this->LookAt();
//		}
//
//		void camera::SetProjection(void)
//		{
//
//			//gl::GetIntegerv( gl::VIEWPORT, viewport);
//			gl::GetIntegerv( gl::VIEWPORT, viewport);
//
//
//
//
//			m3dMakePerspectiveMatrix(Projection, DegToRad * 60.0f, ((GLfloat)viewport[2] / (GLfloat)viewport[3]), 1.0f, 100.0f);
//
//			//m3dMakeOrthographicMatrix(Projection, 0.0f,  static_cast<float>(viewport[2]), 0.0f, static_cast<float>(viewport[3]), 1.0f, 100.f);
//		}
//
//
//		void camera::draw()
//		{
//			//m3dMatrixMultiply44(View, View, Model);
//			//
//			//this->Transform();
//			//this->SetView();
//			this->SetProjection();
//			gl::UseProgram(o_progs.ShaderObject);
//			GLint viewloc = gl::GetUniformLocation(o_progs.ShaderObject, "MV");
//			if (viewloc != -1)
//			{
//				//cout << "found uniform for View Matrix" << endl;
//				gl::UniformMatrix4fv(viewloc, 1, gl::TRUE_, View);
//			}
//
//			GLint PersLoc = gl::GetUniformLocation(o_progs.ShaderObject, "P");
//			if (PersLoc != -1)
//			{
//				//cout << "found uniform for Perspective Matrix" << endl;
//				gl::UniformMatrix4fv(PersLoc, 1, gl::TRUE_, Projection);
//			}
//
//			/*
//			GLint InvLoc = gl::GetUniformLocation( o_progs.ShaderObject, "MV");
//			if (InvLoc != -1)
//			{
//			//cout << "found uniform for Perspective Matrix" << endl;
//			gl::UniformMatrix4fv(InvLoc,1,gl::GL_FALSE,ViewInv);
//			}
//			*/
//
//		}
//
//		//SHIT!!!
//		void camera::LookAt()
//		{
//			
//			m3dLoadIdentity44(View);
//			//m3dLoadIdentity44(ViewInv);
//			VEC3 x, y, z;
//			//faen er du for en? Lys? Look?
//			VEC3 L(0.0, 4.0, -2.0);
//
//
//			//z.X = (0.0f)-view.X;
//			//z.Y = (0.2f)-view.Y;
//			//z.Z = (0.0f)-view.Z;
//			cout << "L before Model tranform to Cam actor: " << L.X << "." << L.Y << "." << L.Z << endl;
//			cout << "Pos before Model tranform to Cam actor: " << pos.X << "." << pos.Y << "." << pos.Z << endl;
//			z.X = L.X - pos.X;
//			z.Y = L.Y - pos.Y;
//			z.Z = L.Z - pos.Z;
//			cout << "L after Model tranform to Cam actor: " << L.X << "." << L.Y << "." << L.Z << endl;
//			cout << "Pos after Model tranform to Cam actor: " << pos.X << "." << pos.Y << "." << pos.Z << endl;
//			z.NormIt();
//
//			y = up;
//
//			x = cross(z, y);
//			x.NormIt();
//
//			y = cross(x, z);
//			cout << "Side after Model tranform to Cam actor X: " << x.X << " Y: " << x.Y << " Z: " << x.Z << endl;
//			cout << "Up after Model tranform to Cam actor  x: " << y.X << " y: " << y.Y << " z: " << y.Z << endl;
//			cout << "Forward after Model tranform to Cam actor x: " << z.X << " Y: " << z.Y << " z: " << z.Z << endl;
//			M3DMatrix44f matrix;
//
//
//			matrix[0] = x.X;
//			matrix[1] = y.X;
//			matrix[2] = -z.X;
//			matrix[3] = 0.0f;
//			matrix[4] = x.Y;
//			matrix[5] = y.Y;
//			matrix[6] = -z.Y;
//			matrix[7] = 0.0f;
//			matrix[8] = x.Z;
//			matrix[9] = y.Z;
//			matrix[10] = -z.Z;
//			matrix[11] = 0.0f;
//			matrix[12] = 0.0f;
//			matrix[13] = 0.0f;
//			matrix[14] = 0.0f;
//			matrix[15] = 1.0f;
//
//			/*
//			#define M(row,col)  View[col*4+row]
//			M(0, 0) = 1.0f;
//			M(0, 1) = 0.0f;
//			M(0, 2) = 0.0f;
//			M(0, 3) = 0.0f;
//			M(1, 0) = 0.0f;
//			M(1, 1) = 1.0f;
//			M(1, 2) = 0.0f;
//			M(1, 3) = 0.0f;
//			M(2, 0) = 0.0f;
//			M(2, 1) = 0.0f;
//			M(2, 2) = 1.0f;
//			M(2, 3) = 0.0f;
//			M(3, 0) = 0.0f;
//			M(3, 1) = 0.0f;
//			M(3, 2) = -3.0f;
//			M(3, 3) = 1.0f;
//			#undef M
//
//
//			*/
//
//
//
//			m3dMatrixMultiply44(View, View, matrix);
//
//
//
//
//			M3DMatrix44f temp;
//			m3dLoadIdentity44(temp);
//			temp[3] = -pos.X;
//			temp[7] = -pos.Y;
//			temp[11] = -pos.Z;
//
//
//
//
//
//			m3dMatrixMultiply44(View, View, temp);
//			//m3dMatrixMultiply44(View, Model, View );
//			//m3dInvertMatrix44(ViewInv, View);
//
//
//		}
//
//
//
//
//		void camera::EasyMV()
//		{
//			m3dLoadIdentity44(View);
//			VEC3 xAxis;
//			xAxis = cross(this->forward, this->up);
//
//
//			M3DMatrix44f mat;
//			mat[0] = xAxis.X;
//			mat[1] = this->up.X;
//			mat[2] = this->forward.X;
//			mat[3] = 0.0f;
//			mat[4] = xAxis.Y;
//			mat[5] = this->up.Y;
//			mat[6] = this->forward.Y;
//			mat[7] = 0.0f;
//			mat[8] = xAxis.Z;
//			mat[9] = this->up.Z;
//			mat[10] = this->forward.Z;
//			mat[11] = 0.0f;
//			mat[12] = 0.0f;
//			mat[13] = 0.0f;
//			mat[14] = 0.0f;
//			mat[15] = 1.0f;
//
//			/*
//			M3DMatrix44f Roll;
//			m3dRotationMatrix44( Roll, -0.0, 0.0,0.0,1.0);
//			//m3dMatrixMultiply44(View, Roll, View );
//			m3dMatrixMultiply44(View, View,Roll );
//			M3DMatrix44f Head;
//			m3dRotationMatrix44( Head, -0.0, 0.0,1.0,0.0);
//			//m3dMatrixMultiply44(View,Head , View);
//			m3dMatrixMultiply44(View, View , Head);
//			*/
//			m3dMatrixMultiply44(View, View, mat);
//
//			M3DMatrix44f Roll;
//			m3dRotationMatrix44(Roll, -0.0, 0.0, 0.0, 1.0);
//			//m3dMatrixMultiply44(View, Roll, View );
//			m3dMatrixMultiply44(View, View, Roll);
//
//
//			M3DMatrix44f Head;
//			m3dRotationMatrix44(Head, -0.0, 0.0, 1.0, 0.0);
//			//m3dMatrixMultiply44(View,Head , View);
//			m3dMatrixMultiply44(View, View, Head);
//
//			M3DMatrix44f Pitch;
//			m3dRotationMatrix44(Pitch, 15.0 * DegToRad, 1.0, 0.0, 0.0);
//			//m3dMatrixMultiply44(View, Pitch, View );
//			m3dMatrixMultiply44(View, View, Pitch);
//
//
//
//			M3DMatrix44f translate;
//			m3dLoadIdentity44(translate);
//			translate[3] = -pos.X;
//			translate[7] = -pos.Y;
//			translate[11] = -pos.Z;
//
//			//m3dMatrixMultiply44(View,  View,  translate );
//			m3dMatrixMultiply44(View, translate, View);
//			View[11] = -(View[11]);
//			View[10] = -(View[10]);
//			View[9] = -(View[9]);
//
//
//	
//	
//}
