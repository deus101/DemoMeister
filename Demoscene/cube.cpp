#include "cube.h"

#include "shaders.h"

extern Shader_Progs o_progs;
namespace sg {
	namespace noder {

		cube::cube() : actors()
		{


		}

		cube::cube(GLfloat x, GLfloat y, GLfloat z, bool move) : actors(x, y, z, move)
		{


		}

		void cube::draw()
		{

			GLint ModelLoc = gl::GetUniformLocation(o_progs.ShaderObject, "M");
			if (ModelLoc != -1)
			{
				//cout << "found uniform for Model Matrix" << endl;
				gl::UniformMatrix4fv(ModelLoc, 1, gl::TRUE_, Model);




			}

		}
	}
}