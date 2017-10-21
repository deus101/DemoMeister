#include "model.h"
//#include "materials.h"
#include "AssetMapClasses/map.h"
#include <iostream>

#include <boost\tokenizer.hpp>
#include <boost\algorithm\string.hpp>
#include <boost\algorithm\string\regex.hpp> 
//#include "vsGLInfoLib.h"

using namespace NS_ENG;

using namespace std;
using namespace NS_MESH;
//using namespace NS_MAP;
//using namespace NS_MAT;

//arve drawable her

//std::list <model*> classModelList;
std::list <model*> model::classModelList = std::list <model*>();

model::model() 
{

}



//Anything with the static container should not have something todo in a constructor
model::model(string obj, string mtl, bool UV , bool Tangent ) : asset()
{




	//actually all this is just a test, I have really no reason to do this for this class, finding duplicates is something
	//id rather do elsewhere....Again completely fucking pointless....well...or is it, if I wanted a function to set up nodes with assets
	//this might be allright...
	bool IsClone = false;
	bool NewPaint = false;
	bool SpecialInstructions = false;

	if (mtl.c_str()[0] == '#')
		SpecialInstructions = true;

	for (auto iter : model::classModelList) {
		
		//cout << "\n Previus file: " << iter->meshy.file_name << endl;
		if (obj.compare(iter->meshy.file_name) == 0)
		{
			//could provide memory leaks
			cout << "\n Found Model Object with same mesh: " << iter->meshy.file_name << endl;
			//hmm maybe what I really want is just to copy the sorted vertex and attribute buffers
			//A central deopsitory for the mesh struct maybe intead?
			*this = *iter;

			//actually its not really a clone at all, should fix that.
			IsClone = true;


			if (mtl.empty() == false  && this->meshy.file_mat.compare(mtl) != 0)
			{
				

				break;
			}
			else
			{
			return;
			}
		}

	}


	NewPaint = true;

	if(!IsClone)
	{ 
	LoadMesh(obj.c_str(), meshy);
	//LoadMats(mtl.c_str(), palette);
	

	std::string M_files = Squiddy.FindAndRegister(meshy.file_mat);


	if(M_files.compare("None") != 0)
	{
	NS_ENG::Material::LoadMats(M_files.c_str());
	}

	Sort_Groups.clear();
	}
	//meshy.



	

	map<PackedVertex, unsigned int> VertexToOutIndex;

	for (unsigned int u = 0; u < meshy.m_Groups.size(); u++)
	{

		buffer_Group MG;

		//We are gonna make sure these are filled, even if we have a new material at hand we will allways load the original;
		MG.ObjName = meshy.m_Groups[u].group_name;
		MG.MatName = MG.OriginalMat = meshy.m_Groups[u].mat;
		MG.ObjectID = u;

		if(!IsClone)
		{

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


					unsigned int newindex = (unsigned int)Sort_Pos.size() - 1;
					MG.IBO.push_back(newindex);
					VertexToOutIndex[packed] = newindex;
				}
			}

		}

		}

		//continue with adding or repainting materials
		
		/*
		for(unsigned int j = 0; j < palette.m_Materials.size(); j++)
		{
		cout << "mats :" << j << endl;
		if( meshy.m_Groups[u].mat.compare(palette.m_Materials[j].name) == 0)
		{
		cout << "MAT: " << palette.m_Materials[j].name << " : " << j << endl;
		meshy.m_Groups[u].matid = j;
		*/
		//Sort_Groups.push_back(MG);
		//for (unsigned int j = 0; j < NS_ENG::Material::classMaterialList.size(); j++)

		if(NewPaint == true && IsClone == true )
		{


		boost::char_separator<char> sep("#G#");

		boost::tokenizer< boost::char_separator<char> > tokens(mtl, sep);

		

		std::string TagValue = "";


		//boost::char_separator<char> sep("#G#");

		boost::tokenizer< boost::char_separator<char>>::iterator tok_it = tokens.begin();


		
		for (auto iter : model::classModelList)
		{ 

		std::string Tag(tok_it->data());

		boost::char_separator<char> sep2("#MN#");

		boost::tokenizer< boost::char_separator<char>>::iterator tok_sec = tokens.begin();

		//std::string MatStr = "";
		std::string Obj(tok_sec->data());
		tok_sec++;


		std::string MatStr(tok_sec->data());


		SetMaterial(MG, Obj, MatStr);

		}

		return;


		}
		else if(SpecialInstructions == true)
		{

			/*
			boost::char_separator<char> sep("#G#","");
			//boost::char_delimiters_separator<std::string> sep3("#G#")
			//boost::char_delimiters_separator<char> sep(true,"#G#");


			boost::tokenizer< boost::char_separator<char> > tokens(mtl, sep);
			//boost::tokenizer<boost::char_delimiters_separator<char> > tokens(mtl, sep);

			boost::tokenizer< boost::char_separator<char>>::iterator tok_it = tokens.begin();
			//boost::tokenizer< boost::char_delimiters_separator<char> >::iterator tok_it = tokens.begin();


			std::string TagValue = "";
			while (tok_it != tokens.end())
			{


				//std::string Obj(tok_sec->data());

				std::string Tag(tok_it->data());
				//std::string Next( tok_it->begin()._Ptr);
				boost::char_separator<char> sep2("#MN#");

				//boost::tokenizer< boost::char_separator<char> > TokensSecond(Tag, sep2);
				boost::tokenizer< boost::char_separator<char> > TokensSecond(Next, sep2);

				boost::tokenizer< boost::char_separator<char>>::iterator tok_sec = TokensSecond.begin();

				//std::string MatStr = "";
				std::string Obj(tok_sec->data());
				tok_sec++;


				std::string MatStr(tok_sec->data());


				SetMaterial(MG, Obj, MatStr);
				tok_it++;
			}
			*/

			vector<string> tokens;

			//boost::split(tokens, mtl, boost::is_any_of("#G#"));

			boost::split_regex(tokens, mtl, boost::regex("#G#"));

			vector<string>::iterator ModelGrpIt = tokens.begin();

			vector<string>::iterator ModelGrpItEnd = tokens.end();

			if (tokens.front().empty())
				ModelGrpIt++;


			//for (std::list<ShaderItemPtr>::iterator ip = this->ShaderSourceComponents.begin(); ip != this->ShaderSourceComponents.end(); ++ip)

			while (ModelGrpIt != ModelGrpItEnd)
			{

				vector<string> SecondTokens;

				//boost::split(tokens, mtl, boost::is_any_of("#G#"));

				boost::split_regex(SecondTokens, ModelGrpIt->data(), boost::regex("#MN#"));

				//if (std::equal(SecondTokens.begin(), SecondTokens.end(), (size_t)2));
				//if ((SecondTokens.size() == (size_t)2) && std::equal(SecondTokens.begin(), SecondTokens.end(), (size_t)2));
				if (SecondTokens.size() == (size_t)2);
				{

					SetMaterial(MG, SecondTokens.front(), SecondTokens.back());

				}


				ModelGrpIt++;
			}




		}
		else
		{ 
		SetMaterial(MG, "", "");
		}
		MG.ModelAidChild = meshy.m_Groups[u].Child;

		Sort_Groups.push_back(MG);
		

	}

	ModelAidRoot = meshy.Child;
	//Husk å generer programmet før dette
	//gl::UseProgram(aContext.Program);
	//KA FAEN TENKTE JEG PÅ!

	//cout << "NR groups: " << Sort_Groups.size() << endl;
	//cout << "VBOs   vertex: " << Sort_Pos.size() << " Norms: " << Sort_Norms.size() << " UVs: " << Sort_Uvs.size() << endl;

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
		//cout << "NR of indice for: " << j << " is " << Sort_Groups[j].IBO.size() << endl;
		glGenVertexArrays(1, &Sort_Groups[j].vao);
		glBindVertexArray(Sort_Groups[j].vao);

		//cout << "vao ident: " << Sort_Groups[j].vao << endl;
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


		glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


		glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);





		//wait what? 
		glGenBuffers(1, &Sort_Groups[j].vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Sort_Groups[j].vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Sort_Groups[j].IBO.size() * sizeof(unsigned int), &Sort_Groups[j].IBO[0], GL_STATIC_DRAW);
		

		
		glBindBuffer(GL_ARRAY_BUFFER, vbo_BaseTool);

		for (unsigned int i = 0; i < 4; i++) {
			glEnableVertexAttribArray(3 + i);
			glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(s_ModelAid),
				(const GLvoid*)(sizeof(GLfloat) * i * 4));
			glVertexAttribDivisor(3 + i, 1);
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo_ChildTool);

		for (unsigned int i = 0; i < 4; i++) {
			glEnableVertexAttribArray(4 + i);
			glVertexAttribPointer(4 + i, 4, GL_FLOAT, GL_FALSE, sizeof(s_ModelAid),
				(const GLvoid*)(sizeof(GLfloat) * i * 4));
			glVertexAttribDivisor(4 + i, 1);
		}
		






	}


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);





	//gl::BindBuffer(gl::GL_ARRAY_BUFFER, 0);



	//cout << "loading done" << endl;
	
	//this->BufferLog();

	NS_ENG::model::classModelList.push_front(this);

	iter = NS_ENG::model::classModelList.begin();


	//cout << "\n Number of models: " << NS_ENG::model::classModelList.size() << endl;


}

//}
model::~model()
{
	//classModelList.erase(iter);
}

void model::SetMaterial(buffer_Group &Object, std::string TaskModel = "", std::string TaskMaterial = "")
{

	bool B_ModelGroup = false;

	if (&Object != NULL)
		B_ModelGroup = true;

	
	if (Object.ObjName.compare(TaskModel) != 0)
		return;

	std::string Distincion;

	if(!TaskMaterial.empty())
	{ 
		Distincion = TaskMaterial;
	}
	else
	{
		Distincion = Object.MatName;
	}


	for (auto MatIter : NS_ENG::Material::classMaterialList)
	{
		

			//meshy.m_Groups[u]
		if (Distincion.compare(MatIter.name) == 0)
		{
			cout << "MAT: " << MatIter.name << " : " << MatIter.matID << endl;
			//meshy.m_Groups[u].matid = j;
			Object.MatId = MatIter.matID;
			//MG.
			//map
			MapAsset *TmpMap = NULL;
			TmpMap = MapAsset::RetriveMap(MatIter.id_Map);
			//MapAssetPtr TmpMap = MapAsset::RetriveMap(MatIter.id_Map);
			if (TmpMap != NULL)
			{
				//Oh right...I did use that
				Object.tex = TmpMap->Map_TName;
			}



			//not as elegant as I thought.
			meshy.m_Groups[Object.ObjectID].Child.MatObjChildTech[0] = MatIter.matID;
			meshy.m_Groups[Object.ObjectID].Child.MatObjChildTech[2] = Object.ObjectID;
			break;
		}

	}



}

void model::Draw()
{

	

	//GLuint vbo_BaseTool;
	//GLuint vbo_ChildTool;

	//this shit needs to go. 
	GLint ShaderProg;
	//glGetIntegerv(GL_CURRENT_PROGRAM, &ShaderProg);
	
	//GLint VEC3_DIFF_UNILOC = glGetUniformLocation(ShaderProg, "mDiffuseCol");
	
	//remember to move to overloaded method
	glBindBuffer(GL_ARRAY_BUFFER, vbo_BaseTool);
	glBufferData(GL_ARRAY_BUFFER, sizeof(s_ModelAid) * 2, &ModelAidRoot, GL_DYNAMIC_DRAW);



	//glActiveTexture(CurrentStage->TextureUnits[TypeOfTexture::MaterialMap_UNIT]);

	//glBindTexture(GL_TEXTURE_2D, Material::GenerateMaterialMap());


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (unsigned int i = 0; i < Sort_Groups.size(); i++)
	{

		glBindBuffer(GL_ARRAY_BUFFER, vbo_ChildTool);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s_ModelAid) * 2, &Sort_Groups[i].ModelAidChild, GL_DYNAMIC_DRAW);


		
		//This shit must be redone to use mat ID and stuff
		glBindVertexArray(Sort_Groups[i].vao);
		//glUniform3f(VEC3_DIFF_UNILOC, Sort_Groups[i].dif.X, Sort_Groups[i].dif.Y, Sort_Groups[i].dif.Z);
		

		//Sort_Groups[i].





		//13.07  is allways null
		if (Sort_Groups[i].tex != NULL)
		{
			//if ActivateAlbedoSampler
			glActiveTexture(CurrentStage->TextureUnits[TypeOfTexture::DiffuseMap_UNIT]);
			//glActiveTexture(TypeOfTexture::DiffuseMap_UNIT);

			//glBindTexture(GL_TEXTURE_2D, Sort_Groups[i].tex);
			glBindTexture(GL_TEXTURE_2D, Sort_Groups[i].tex);
		}

		//Sort_Groups[i].
		//gl::Uniform4fv(DifLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].diff);
		//gl::Uniform4fv(AmbLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].amb);
		//gl::Uniform4fv(SpecLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].spec);
		//glUniform1f(this->, palette.m_Materials[meshy.m_Groups[i].matid].shiny);
		//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, (GLintptr)_data.indices.length, _data.indices.bytes);
		//glDrawElements(GL_TRIANGLES, Sort_Groups[i].IBO.size(), GL_UNSIGNED_SHORT, (void*)0);
		
		glDrawElements(GL_TRIANGLES, Sort_Groups[i].IBO.size(), GL_UNSIGNED_INT, (void*)0);

		//nvogl gives exception error every second run








	}
	glBindVertexArray(0);

}


void model::Draw(int instances)
{



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

