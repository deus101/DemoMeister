#include "circle.h"

namespace sg {
	namespace noder {
		circle::circle() : actors()
		{
			r = 3.0;

		}


		circle::circle(GLfloat radius, GLfloat x, GLfloat y, GLfloat z, bool move) : actors(x, y, z, move)
		{

			r = radius;

		}


		void circle::draw()
		{

			GLfloat mShininess[] = { 500 };

			GLfloat DiffuseMaterial[] = { 0.6, 0.6, 0.6 };
			GLfloat AmbientMaterial[] = { 1.0, 0.0, 0.0 };
			GLfloat SpecularMaterial[] = { 1.0, 1.0, 1.0 };
			/*
			glPushMatrix();


			glTranslatef( pos.X, pos.Y, pos.Z);


			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseMaterial);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AmbientMaterial);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularMaterial);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
			glutSolidSphere( r, 20, 20);
			glPopMatrix();
			*/
		}
	}
}
