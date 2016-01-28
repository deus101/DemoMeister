#include "model.h"

#include <iostream>
//#include "vsGLInfoLib.h"

using namespace NS_ENG;

using namespace std;
using namespace NS_MESH;
using namespace NS_MAT;

//arve drawable her
model::model() 
{

}




model::model( string obj, string mtl)
{

	LoadMesh(obj.c_str(), meshy);
	LoadMats(mtl.c_str(), palette);



	Sort_Groups.clear();

	map<PackedVertex, unsigned int> VertexToOutIndex;

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
				unsigned int index;
				//unsigned short index;
			


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

					//unsigned short newindex = (unsigned short)Sort_Pos.size() - 1;

					unsigned int newindex = (unsigned int)Sort_Pos.size() - 1;
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
		//palette.m
		//cout << "group color is :" << u << endl;
		//meshy.m_Pos.
		MG.tex = palette.m_Materials[meshy.m_Groups[u].matid].tUnit;

		Sort_Groups.push_back(MG);


	}

	
	//Husk å generer programmet før dette
	//gl::UseProgram(aContext.Program);
	//KA FAEN TENKTE JEG PÅ!

	cout << "NR groups: " << Sort_Groups.size() << endl;
	cout << "VBOs   vertex: " << Sort_Pos.size() << " Norms: " << Sort_Norms.size() << " UVs: " << Sort_Uvs.size() << endl;

	glGenBuffers(1, &vbo_vertices);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, Sort_Pos.size() * sizeof(GLfloat)* 3, &Sort_Pos[0], GL_STATIC_DRAW);

	glGenBuffers(1, &vbo_uv);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
	glBufferData(GL_ARRAY_BUFFER, Sort_Uvs.size() * sizeof(GLfloat)* 2, &Sort_Uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &vbo_normals);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glBufferData(GL_ARRAY_BUFFER, Sort_Norms.size() * sizeof(GLfloat)* 3, &Sort_Norms[0], GL_STATIC_DRAW);



	for (unsigned int j = 0; j < Sort_Groups.size(); j++)
	{
		cout << "NR of indice for: " << j << " is " << Sort_Groups[j].IBO.size() << endl;
		glGenVertexArrays(1, &Sort_Groups[j].vao);
		glBindVertexArray(Sort_Groups[j].vao);

		cout << "vao ident: " << Sort_Groups[j].vao << endl;
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


		glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


		glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);






		glGenBuffers(1, &Sort_Groups[j].vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Sort_Groups[j].vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Sort_Groups[j].IBO.size() * sizeof(unsigned int), &Sort_Groups[j].IBO[0], GL_STATIC_DRAW);
		
	}


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);





	//gl::BindBuffer(gl::GL_ARRAY_BUFFER, 0);



	cout << "loading done" << endl;
	
	//this->BufferLog();

}
model::~model()
{

}



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




	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (unsigned int i = 0; i < Sort_Groups.size(); i++)
	{
	

		glBindVertexArray(Sort_Groups[i].vao);

		if (Sort_Groups[i].tex != NULL)
		{
			glActiveTexture(COLOR_TEXTURE_UNIT);
			glBindTexture(GL_TEXTURE_2D, Sort_Groups[i].tex);
		}
		//gl::Uniform4fv(DifLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].diff);
		//gl::Uniform4fv(AmbLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].amb);
		//gl::Uniform4fv(SpecLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].spec);
		//gl::Uniform1f(ShiLoc, palette.m_Materials[meshy.m_Groups[i].matid].shiny);
		//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, (GLintptr)_data.indices.length, _data.indices.bytes);
		//glDrawElements(GL_TRIANGLES, Sort_Groups[i].IBO.size(), GL_UNSIGNED_SHORT, (void*)0);
		
		glDrawElements(GL_TRIANGLES, Sort_Groups[i].IBO.size(), GL_UNSIGNED_INT, (void*)0);


	}
	glBindVertexArray(0);

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

