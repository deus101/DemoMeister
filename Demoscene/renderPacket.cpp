#include "renderPacket.h"
#include "math3d.h"
using namespace NS_VEC;


renderPacket::renderPacket()
{
 //gi den shaderne
	renderPacket();


}

void renderPacket::DrawNode(NS_MESH::MESH o, NS_MAT::MATERIALS m, M3DMatrix44f MODEL)
{

	//gl::BindVertexArray(vao_model);
	//Sett opp egne programmer

	gl::UseProgram(o_progs.ShaderObject);
	GLint ModelLoc = gl::GetUniformLocation(o_progs.ShaderObject, "M");
	if (ModelLoc != -1)
	{
		//cout << "In Model found uniform for Model Matrix" << endl;
		//gl::UniformMatrix4fv(ModelLoc, 1, gl::FALSE_, this->Model);
		//"this" i rendrenren henter model matrisen
	}

	GLint DifLoc = gl::GetUniformLocation(o_progs.ShaderObject, "Diffuse");
	GLint AmbLoc = gl::GetUniformLocation(o_progs.ShaderObject, "Ambiant");
	GLint SpecLoc = gl::GetUniformLocation(o_progs.ShaderObject, "Specular");
	GLint ShiLoc = gl::GetUniformLocation(o_progs.ShaderObject, "Shininess");

	if (ModelLoc != -1)
	{
		//cout << "In Model found uniform for Model Matrix" << endl;
		//gl::UniformMatrix4fv(AmbLoc, 1, gl::TRUE_, this->  );
		//"this" i rendrenren henter model matrisen
	}



	//gl::PolygonMode(gl::GL_FRONT_AND_BACK, gl::GL_FILL);

	for (unsigned int i = 0; i < Sort_Groups.size(); i++)
	{


		gl::BindVertexArray(Sort_Groups[i].vao);

		gl::Uniform4fv(DifLoc, 1, (const GLfloat *)this->palette.m_Materials[meshy.m_Groups[i].matid].diff);
		gl::Uniform4fv(AmbLoc, 1, (const GLfloat *)this->palette.m_Materials[meshy.m_Groups[i].matid].amb);
		gl::Uniform4fv(SpecLoc, 1, (const GLfloat *)this->palette.m_Materials[meshy.m_Groups[i].matid].spec);
		gl::Uniform1f(ShiLoc, this->palette.m_Materials[meshy.m_Groups[i].matid].shiny);

		gl::DrawElements(gl::TRIANGLES, Sort_Groups[i].IBO.size(), gl::UNSIGNED_SHORT, (void*)0);
	}


}

