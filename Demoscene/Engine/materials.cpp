#include "materials.h"
#include "map.h"
//#include "../Libs/FreeImage.h"


#include <algorithm>
#include <stdio.h>
#include <iostream>


using namespace NS_ENG;
using namespace std;


//namespace NS_MAT
//namespace NS_ENG
//{
std::list <s_mat> Material::classMaterialList = std::list <s_mat>();

GLuint Material::MaterialMapTextureUnit = 0;


Material::Material() : asset()
{
	//Mats.Clear();

}


//this should be a static method, and eaach materials object should be stored in the static container as one materials
//hmm but what about shader jutsu?
//void LoadMats(const char *param, MATERIALS& Mats)
void Material::LoadMats( const char *param)
{
	FILE * mtlFile;
	mtlFile = fopen( param , "rb");

	//Mats.Clear();
	
		
	char line[1024] = "";
	char id[512] = "";
	std::cout << "---------MTL:Begin loading materials from:" << param << endl;
	int NrMatFile = 0;
	while( fscanf(mtlFile, "%s", id) > 0)
	{

		if(strcmp (id, "newmtl") == 0)
		{
			NrMatFile++;
			s_mat mtl;
			char nam[80] ="";
			fscanf(mtlFile, "%79s", nam );
			mtl.name = nam;
			std::cout << "-material name: " << mtl.name << endl;
			//Mats.m_Materials.push_back( mtl );
			NS_ENG::Material::classMaterialList.push_back(mtl);

			NS_ENG::Material::classMaterialList.back().matID =  NS_ENG::Material::classMaterialList.size();
		}
		if(strcmp (id, "Kd") == 0)
		{
				
			fscanf(mtlFile, "%f %f %f", &NS_ENG::Material::classMaterialList.back().diff[0], &NS_ENG::Material::classMaterialList.back().diff[1], &NS_ENG::Material::classMaterialList.back().diff[2]);
			//fscanf(mtlFile, "%f %f %f", &Mats.m_Materials.back().diff[0], &Mats.m_Materials.back().diff[1], &Mats.m_Materials.back().diff[2]);

			//Mats.m_Materials.back().diff[3] = 1.0;
			NS_ENG::Material::classMaterialList.back().diff[3] = 1.0;
				//input[3] = 1.0;
			//Mats.m_Materials.back().diff = input;
		}
		if(strcmp (id, "Ka") == 0)
		{
				
			//fscanf(mtlFile, "%f %f %f", &Mats.m_Materials.back().amb[0], &Mats.m_Materials.back().amb[1], &Mats.m_Materials.back().amb[2]);
			//Mats.m_Materials.back().amb[3] = 1.0;
			fscanf(mtlFile, "%f %f %f", &NS_ENG::Material::classMaterialList.back().amb[0], &NS_ENG::Material::classMaterialList.back().amb[1], &NS_ENG::Material::classMaterialList.back().amb[2]);
			NS_ENG::Material::classMaterialList.back().amb[3] = 1.0;
		}
		if(strcmp (id, "Ks") == 0)
		{
			
			//fscanf(mtlFile, "%f %f %f", &Mats.m_Materials.back().spec[0], &Mats.m_Materials.back().spec[1], &Mats.m_Materials.back().spec[2]);
			//Mats.m_Materials.back().spec[3] = 1.0;
			fscanf(mtlFile, "%f %f %f", &NS_ENG::Material::classMaterialList.back().spec[0], &NS_ENG::Material::classMaterialList.back().spec[1], &NS_ENG::Material::classMaterialList.back().spec[2]);
			NS_ENG::Material::classMaterialList.back().spec[3] = 1.0;
		}
		if(strcmp (id, "Ke") == 0)
		{	
			NS_VEC::VEC3 c;
			//fscanf(mtlFile, "%f %f %f", &Mats.m_Materials.back().emmi[0], &Mats.m_Materials.back().emmi[1], &Mats.m_Materials.back().emmi[2]);
			//Mats.m_Materials.back().emmi[3] = 1.0;
			fscanf(mtlFile, "%f %f %f", &NS_ENG::Material::classMaterialList.back().emmi[0], &NS_ENG::Material::classMaterialList.back().emmi[1], &NS_ENG::Material::classMaterialList.back().emmi[2]);
			NS_ENG::Material::classMaterialList.back().emmi[3] = 1.0;

		}
		if(strcmp (id, "Ns") == 0)
		{
			GLfloat shin = 0.0f;
			fscanf(mtlFile, "%f", &shin);
			//Mats.m_Materials.back().shiny = shin;
			NS_ENG::Material::classMaterialList.back().shiny = shin;
		}
		else if (strcmp(id, "map_Kd") == 0)
		{

			//here we implement a map object...
			bool duplicate = false;
			//load
			GLuint tmp_TName;
				
			char path[80];

			fscanf(mtlFile, "%79s", path);
			string tmp_Path(path);


			NS_ENG::Material::classMaterialList.back().id_Map = MapAsset::LoadMaps(path);

		}

	}


		fclose(mtlFile);

		std::cout << "Loaded " << NrMatFile << ", Materials NR of materials so far : " << NS_ENG::Material::classMaterialList.size() << endl << "Done loading the " << param << " MTL---------" <<endl << endl;
		//cout << "NR of materials: " << Mats.m_Materials.size() << endl;
}


std::string Material::Shaderfy() {
	//forget this for now work ing static int GenerateMaterialMap();
	bool first = true;
	string GlSL = "//retrive materials \n ";



	//constructing color buffer or that is...material texture. 
	//Columns
	int nr_mats = NS_ENG::Material::classMaterialList.size();

	//OK so what do we need in terms of...wel channels, each Row would be a channel in this regard.
	//

	//3 for diffuse, 3 for specular, 1 for effect/technique, 1 for technique and 1 for texture
	//question is wheter I should just offload diffuse into the gbuffer, this makles sense because if we have normal/bump map those can be bound
	//in the forward rendering...well forward as it gets with a deferred rendrer...but then we dont have to bother adding 
	//boundless textures that might be cumbersome to handle and instead focus on the physical based properties and add their maps 
	//to be boundless as it gets to the lightning stage
	float matInfo[12];



	/* 
	glGenTextures(1, &NoiseTexure);
	glBindTexture(GL_TEXTURE_2D, NoiseTexure);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	*/


	for (auto MatIter : NS_ENG::Material::classMaterialList)
	{
		string Current;
		if(first == true)
		{
			Current =  string(" if(ID=") + std::to_string((int)MatIter.matID) + string("){\n ");
			first = false;
		}
		else
		{
		
			Current = string(" else-if(ID=") + std::to_string((int)MatIter.matID) + string("){\n ");
		}

		string Diffuse = string(" MatDiffuse =  vec4(") 
			+ std::to_string((float)MatIter.diff[0])
			+ string(",")
			+ std::to_string((float)MatIter.diff[1])
			+ string(",")
			+ std::to_string((float)MatIter.diff[2])
			+ string(",")
			+ std::to_string((float)MatIter.diff[3])
			+ string(");\n ");
		string Specular = string(" MatSpecular =  vec4(")
			+ std::to_string((float)MatIter.spec[0])
			+ string(",")
			+ std::to_string((float)MatIter.spec[1])
			+ string(",")
			+ std::to_string((float)MatIter.spec[2])
			+ string(",")
			+ std::to_string((float)MatIter.spec[3])
			+ string(");\n ") + string(" }");
		
			//cout << " The material: " << MatIter.matID << ":" << MatIter.name << " have allready loaded the texture " << MatIter.tPath << endl;
			//cout << " Using the GlName :" << MatIter.tUnit << endl;
			//meshy.m_Groups[u].matid = j;
			//meshy.m_Groups[u].matid = MatIter.matID;
			//NS_ENG::Material::classMaterialList.back().tUnit = MatIter.tUnit;
			//NS_ENG::Material::classMaterialList.back().tPath = tmp_Path;
			//MG.
		GlSL += Current;
		GlSL += Diffuse;
		GlSL += Specular;

	}


	//GlSL += "}\n";

	cout << GlSL;
	return GlSL;
}

GLuint Material::GenerateMaterialMap() {
	int nr_mats = NS_ENG::Material::classMaterialList.size();
	if(Material::MaterialMapTextureUnit != 0)
		return Material::MaterialMapTextureUnit;
	//Vec4 diffuse, vec4 specular is 2 collumns

	std::vector<NS_VEC::VEC3> rowMaterial;

	for (auto MatIter : NS_ENG::Material::classMaterialList)
	{
		//MatIter.diff[0]
		NS_VEC::VEC3 col1Diff(MatIter.diff[0], MatIter.diff[1], MatIter.diff[2]); // rotate around z-axis (in tangent space)
		rowMaterial.push_back(col1Diff);

		NS_VEC::VEC3 col1Spec(MatIter.spec[0], MatIter.spec[1], MatIter.spec[2]); // rotate around z-axis (in tangent space)
		rowMaterial.push_back(col1Spec);
	}
	glGenTextures(1, &Material::MaterialMapTextureUnit);
	glBindTexture(GL_TEXTURE_2D, Material::MaterialMapTextureUnit);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 2, nr_mats, 0, GL_RGB, GL_FLOAT, &rowMaterial[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	return Material::MaterialMapTextureUnit;
}

//}
