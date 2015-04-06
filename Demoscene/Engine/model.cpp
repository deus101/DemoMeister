#include "model.h"

#include <iostream>
//#include "shaders.h"
//#include "vsGLInfoLib.h"

//nei nei nei
//extern Shader_Progs o_progs;
using namespace NS_ENG;

using namespace std;
using namespace NS_MESH;
using namespace NS_MAT;

//arve drawable her
model::model() 
{

}




model::model(const NS_REND::context &aContext, string obj, string mtl)
{

	LoadMesh(obj.c_str(), meshy);
	LoadMats(mtl.c_str(), palette);



	Sort_Groups.clear();

	map<PackedVertex, unsigned short> VertexToOutIndex;

	for (unsigned int u = 0; u < meshy.m_Groups.size(); u++)
	{

		buffer_Group MG;



		for (unsigned int j = 0; j < meshy.m_Groups[u].m_Faces.size(); j++)
		{
			for (unsigned int k = 0; k < meshy.m_Groups[u].m_Faces[j].m_Verts.size(); k++)
			{
				PackedVertex packed = {
					meshy.m_Pos[meshy.m_Groups[u].m_Faces[j].m_Verts[k].m_PID],
					meshy.m_Uvs[meshy.m_Groups[u].m_Faces[j].m_Verts[k].m_UID],
					meshy.m_Norms[meshy.m_Groups[u].m_Faces[j].m_Verts[k].m_NID]
				};
				unsigned short index;

				bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);


				if (found)
				{ // A similar vertex is already in the VBO, use it instead !
					MG.IBO.push_back(index);
				}
				else
				{ // If not, it needs to be added in the output data.
					Sort_Pos.push_back(meshy.m_Pos[meshy.m_Groups[u].m_Faces[j].m_Verts[k].m_PID]);
					Sort_Uvs.push_back(meshy.m_Uvs[meshy.m_Groups[u].m_Faces[j].m_Verts[k].m_UID]);
					Sort_Norms.push_back(meshy.m_Norms[meshy.m_Groups[u].m_Faces[j].m_Verts[k].m_NID]);

					unsigned short newindex = (unsigned short)Sort_Pos.size() - 1;
					MG.IBO.push_back(newindex);
					VertexToOutIndex[packed] = newindex;
				}
			}

		}
		
		for(unsigned int j = 0; j < palette.m_Materials.size(); j++)
		{
		cout << "mats :" << j << endl;
		if( meshy.m_Groups[u].mat.compare(palette.m_Materials[j].name) == 0)
		{
		cout << "MAT: " << palette.m_Materials[j].name << " : " << j << endl;
		meshy.m_Groups[u].matid = j;

		break;
		}

		}

		//MG.amb = palette.m_Materials[ meshy.m_Groups[u].matid ].amb;
		//MG.dif = palette.m_Materials[ meshy.m_Groups[u].matid ].diff;
		//MG.emi = palette.m_Materials[ meshy.m_Groups[u].matid ].emmi;
		//MG.spec = palette.m_Materials[ meshy.m_Groups[u].matid].shiny
		
		//cout << "group color is :" << u << endl;
		//meshy.m_Pos.


		Sort_Groups.push_back(MG);


	}

	//lasting av data til CPU man jeg trenger en funksjon som henter shaderprogram(gjør jeg det?) og laster buffrer
	
	//Husk å generer programmet før dette
	//gl::UseProgram(aContext.Program);
	//KA FAEN TENKTE JEG PÅ!

	cout << "NR groups: " << Sort_Groups.size() << endl;
	cout << "VBOs   vertex: " << Sort_Pos.size() << " Norms: " << Sort_Norms.size() << " UVs: " << Sort_Uvs.size() << endl;

	gl::GenBuffers(1, &vbo_vertices);

	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_vertices);
	gl::BufferData(gl::ARRAY_BUFFER, Sort_Pos.size() * sizeof(GLfloat)* 3, &Sort_Pos[0], gl::STATIC_DRAW);

	gl::GenBuffers(1, &vbo_uv);

	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_uv);
	gl::BufferData(gl::ARRAY_BUFFER, Sort_Uvs.size() * sizeof(GLfloat)* 2, &Sort_Uvs[0], gl::STATIC_DRAW);

	gl::GenBuffers(1, &vbo_normals);

	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_normals);
	gl::BufferData(gl::ARRAY_BUFFER, Sort_Norms.size() * sizeof(GLfloat)* 3, &Sort_Norms[0], gl::STATIC_DRAW);



	for (unsigned int j = 0; j < Sort_Groups.size(); j++)
	{
		cout << "NR of indice for: " << j << " is " << Sort_Groups[j].IBO.size() << endl;
		gl::GenVertexArrays(1, &Sort_Groups[j].vao);
		gl::BindVertexArray(Sort_Groups[j].vao);

		cout << "vao ident: " << Sort_Groups[j].vao << endl;
		gl::BindBuffer(gl::ARRAY_BUFFER, vbo_vertices);
		gl::EnableVertexAttribArray(0);
		gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, (void*)0);


		gl::BindBuffer(gl::ARRAY_BUFFER, vbo_uv);
		gl::EnableVertexAttribArray(1);
		gl::VertexAttribPointer(1, 2, gl::FLOAT, gl::FALSE_, 0, (void*)0);


		gl::BindBuffer(gl::ARRAY_BUFFER, vbo_normals);
		gl::EnableVertexAttribArray(2);
		gl::VertexAttribPointer(2, 3, gl::FLOAT, gl::FALSE_, 0, (void*)0);






		gl::GenBuffers(1, &Sort_Groups[j].vbo);
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, Sort_Groups[j].vbo);
		gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, Sort_Groups[j].IBO.size() * sizeof(unsigned short), &Sort_Groups[j].IBO[0], gl::STATIC_DRAW);
	}


	gl::BindVertexArray(0);
	gl::BindBuffer(gl::ARRAY_BUFFER, 0);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);





	//gl::BindBuffer(gl::GL_ARRAY_BUFFER, 0);



	cout << "loading done" << endl;
	
	//this->BufferLog();

}
model::~model()
{

}


//FEIL FEIL FEIL
//RENDER QUE! NUH!


		//cout << "nr indices for: " << i << " is " << Sort_Groups[i].IBO.size() << endl;
		//VSGLInfoLib::getBufferInfo(gl::GL_ELEMENT_ARRAY_BUFFER, Sort_Groups[i].vbo);
		//VSGLInfoLib::getCurrentBufferInfo();

		//VSGLInfoLib::getBufferInfo(gl::


	

	//VSGLInfoLib::getProgramInfo(o_progs.ShaderObject);
	//VSGLInfoLib::getUniformsInfo(o_progs.ShaderObject);
	//VSGLInfoLib::getCurrentBufferInfo();
	//VSGLInfoLib::getAttributesInfo(o_progs.ShaderObject);


	//VSGLInfoLib::getProgramInfo(o_progs.ShaderObject);
	//VSGLInfoLib::getUniformInfo(o_progs.ShaderObject, "V");
	//VSGLInfoLib::getUniformInfo(o_progs.ShaderObject, "P");
	//VSGLInfoLib::getUniformInfo(o_progs.ShaderObject, "M");
	//VSGLInfoLib::getUniformInfo(o_progs.ShaderObject, "MV");

	//VSGLInfoLib::getCurrentBufferInfo();

	//gl::DisableVertexAttribArray(0);
	//gl::DisableVertexAttribArray(1);
	//gl::DisableVertexAttribArray(2);









	//unifor for model matrix

void model::Draw()
{

	////gl::BindVertexArray(vao_model);
	////Sett opp egne programmer
	////gl::UseProgram(m_shaderProg);
	//GLint ModelLoc = gl::GetUniformLocation(m_shaderProg, "M");
	//if (ModelLoc != -1)
	//{
	//	//cout << "In Model found uniform for Model Matrix" << endl;
	//	//gl::UniformMatrix4fv(ModelLoc, 1, gl::FALSE_, this->Model);
	//	//"this" i rendrenren henter model matrisen
	//}

	//GLint DifLoc = gl::GetUniformLocation(m_shaderProg, "Diffuse");
	//GLint AmbLoc = gl::GetUniformLocation(m_shaderProg, "Ambiant");
	//GLint SpecLoc = gl::GetUniformLocation(m_shaderProg, "Specular");
	//GLint ShiLoc = gl::GetUniformLocation(m_shaderProg, "Shininess");

	//if (ModelLoc != -1)
	//{
	//	//cout << "In Model found uniform for Model Matrix" << endl;
	//	//gl::UniformMatrix4fv(AmbLoc, 1, gl::TRUE_, this->  );
	//	//"this" i rendrenren henter model matrisen
	//}



	////gl::PolygonMode(gl::GL_FRONT_AND_BACK, gl::GL_FILL);

	//for (unsigned int i = 0; i < Sort_Groups.size(); i++)
	//{


	//	gl::BindVertexArray(Sort_Groups[i].vao);

	//	gl::Uniform4fv(DifLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].diff);
	//	gl::Uniform4fv(AmbLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].amb);
	//	gl::Uniform4fv(SpecLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].spec);
	//	gl::Uniform1f(ShiLoc, palette.m_Materials[meshy.m_Groups[i].matid].shiny);

	//	gl::DrawElements(gl::TRIANGLES, Sort_Groups[i].IBO.size(), gl::UNSIGNED_SHORT, (void*)0);
	//}


}





void model::BufferLog()
{
	for (unsigned int i = 0; i < Sort_Groups.size(); i++)
	{
		cout << "Group: " << i << endl;
		for (unsigned int j = 0; j < Sort_Groups[i].IBO.size(); j++)
		{
			cout << "Index: " << j << " -> " << Sort_Groups[i].IBO[j] << endl;

			cout << "Pos: " << Sort_Pos[Sort_Groups[i].IBO[j]].X << "," << Sort_Pos[Sort_Groups[i].IBO[j]].Y << "," << Sort_Pos[Sort_Groups[i].IBO[j]].Z << " UV: " << Sort_Uvs[Sort_Groups[i].IBO[j]].X << "," << Sort_Uvs[Sort_Groups[i].IBO[j]].X << " Normals: " << Sort_Norms[Sort_Groups[i].IBO[j]].X << "," << Sort_Norms[Sort_Groups[i].IBO[j]].Y << "," << Sort_Norms[Sort_Groups[i].IBO[j]].Z << endl;


		}



	}


}

