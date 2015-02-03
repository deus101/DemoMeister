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

void setMatrices(const M3DMatrix44f &world, const M3DMatrix44f&view, const M3DMatrix44f &proj)
{	
	M3DMatrix44f wv, wvp;

	//assert(NULL != p);
	M3DMatrix44f world_view_proj, matWVP_inv;
	m3dMatrixMultiply44(wv, world, view);


	m3dMatrixMultiply44(wvp, wv, proj);
	m3dCopyMatrix44(world_view_proj, wvp);
	m3dInvertMatrix44(matWVP_inv, world_view_proj);
	

	M3DMatrix44f world_view;
	m3dMatrixMultiply44( world_view, world,view);
	M3DMatrix44f world_inv;
	M3DMatrix44f world_view_inv;
	m3dInvertMatrix44(world_inv, world);
	m3dInvertMatrix44(world_view_inv, world_view);

	if (this->world != NULL)
		setMatrix(this->world, world);
	if (this->world_inv != NULL)
		setMatrix(this->world_inv, world_inv);
	if (this->view != NULL)
		setMatrix(this->view, view);
	if (this->view_inv != NULL)
		setMatrix(this->view, view.inverse());
	if (this->projection != NULL)
		setMatrix(this->projection, proj);
	if (this->worldview != NULL)
		setMatrix(this->worldview, world_view);
	if (this->worldview_inv != NULL)
		setMatrix(this->worldview_inv, world_view_inv);
	if (this->worldviewprojection != NULL)
		setMatrix(this->worldviewprojection, world_view_proj);
	if (this->matWVP_inv)
		setMatrix(this->matWVP_inv, matWVP_inv);

	if (this->viewPos != NULL) setVector3(this->viewPos, world_view_inv.getTranslation());
	if (this->viewDir != NULL) setVector3(this->viewDir, world_view.getZAxis());

}