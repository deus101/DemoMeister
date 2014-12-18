#include "pyramid.h"


namespace sg {
	namespace noder {
		pyramid::pyramid() : actors()
		{


		}

		pyramid::pyramid(GLfloat x, GLfloat y, GLfloat z, bool move) : actors(x, y, z, move)
		{

			LoadMesh("pyramid.obj", dodo);


		}

		void pyramid::draw()
		{
			/*
			glPushMatrix();
			glTranslatef( pos.X, pos.Y, pos.Z);

			//glEnable(GL_POLYGON_OFFSET_FILL);
			//glPolygonOffset(1.1,4.0);
			glPushMatrix();
			glBegin(GL_TRIANGLES);

			for(unsigned int i = 0; i < dodo.m_Faces.size(); i++)
			{
			glColor3f(0,1,1);
			//glNormal3f( dodo.m_Pos[dodo.m_Faces[i].m_Verts[0].m_NID].X,  dodo.m_Faces[i].m_vNorm.Y,  dodo.m_Faces[i].m_vNorm.Z );
			glVertex3f(  dodo.m_Pos[dodo.m_Faces[i].m_Verts[0].m_PID].X, dodo.m_Pos[dodo.m_Faces[i].m_Verts[0].m_PID].Y,  dodo.m_Pos[ dodo.m_Faces[i].m_Verts[0].m_PID ].Z);

			glVertex3f(  dodo.m_Pos[dodo.m_Faces[i].m_Verts[1].m_PID].X, dodo.m_Pos[dodo.m_Faces[i].m_Verts[1].m_PID].Y,  dodo.m_Pos[ dodo.m_Faces[i].m_Verts[1].m_PID ].Z);

			glVertex3f(  dodo.m_Pos[dodo.m_Faces[i].m_Verts[2].m_PID].X, dodo.m_Pos[dodo.m_Faces[i].m_Verts[2].m_PID].Y,  dodo.m_Pos[ dodo.m_Faces[i].m_Verts[2].m_PID ].Z);

			}
			glEnd();
			glPopMatrix();
			//glDisable(GL_POLYGON_OFFSET_FILL);


			glPopMatrix();
			*/
		}
	}
}