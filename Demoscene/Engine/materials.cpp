#include "materials.h"
//#include "map.h"
#include "AssetMapClasses\map.h"


//#include "../Libs/FreeImage.h"


#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <boost\filesystem.hpp>
//#include <Shlwapi.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
using namespace NS_ENG;
using namespace std;


//namespace NS_MAT
//namespace NS_ENG
//{
std::list <s_mat> Material::classMaterialList = std::list <s_mat>();
//std::list <Material*> Material::classModelList = std::list <Material*>();

GLuint Material::MaterialMapTextureUnit = 0;


Material::Material() : asset()
{
	//Mats.Clear();

}


//this should be a static method, and eaach materials object should be stored in the static container as one materials
//hmm but what about shader jutsu?
//void LoadMats(const char *param, MATERIALS& Mats)
//void LoadMats(const char *Origin, const char *param)
void Material::LoadMats( const char *param)
{


	//Squiddy.




	FILE * mtlFile;
	fopen_s(&mtlFile, param , "rb");

	//Mats.Clear();
	
	string CurrentMaterial;
	char line[1024] = "";
	char id[512] = "";
	std::cout << "---------MTL:Begin loading materials from:" << param << endl;
	int NrMatFile = 0;
	while( fscanf_s(mtlFile, "%s", id, sizeof(id)) > 0)
	{

		if(strcmp (id, "newmtl") == 0)
		{
			NrMatFile++;
			s_mat mtl;
			char nam[80] ="";
			fscanf_s(mtlFile, "%79s", nam ,sizeof(nam));
			mtl.name = nam;
			CurrentMaterial = nam;
			std::cout << "-material name: " << mtl.name << endl;
			//Mats.m_Materials.push_back( mtl );
			NS_ENG::Material::classMaterialList.push_back(mtl);

			NS_ENG::Material::classMaterialList.back().matID =  NS_ENG::Material::classMaterialList.size();
		}
		if(strcmp (id, "Kd") == 0)
		{
			//diffuse reflectivity  RGB


			fscanf_s(mtlFile, "%f %f %f", &NS_ENG::Material::classMaterialList.back().diff[0], &NS_ENG::Material::classMaterialList.back().diff[1], &NS_ENG::Material::classMaterialList.back().diff[2]);

			NS_ENG::Material::classMaterialList.back().diff[3] = 1.0;

		}
		if(strcmp (id, "Ka") == 0)
		{
			//ambient reflectivity using RGB


		
			fscanf_s(mtlFile, "%f %f %f", &NS_ENG::Material::classMaterialList.back().amb[0], &NS_ENG::Material::classMaterialList.back().amb[1], &NS_ENG::Material::classMaterialList.back().amb[2]);
			NS_ENG::Material::classMaterialList.back().amb[3] = 1.0;
		}
		if(strcmp (id, "Ks") == 0)
		{
			//specular reflectivity RGB
		
			fscanf_s(mtlFile, "%f %f %f", &NS_ENG::Material::classMaterialList.back().spec[0], &NS_ENG::Material::classMaterialList.back().spec[1], &NS_ENG::Material::classMaterialList.back().spec[2]);
			NS_ENG::Material::classMaterialList.back().spec[3] = 1.0;
		}
		if(strcmp (id, "Ke") == 0)
		{	//emmisive in rgb or should it just be a float
			NS_VEC::VEC3 c;
			
			fscanf_s(mtlFile, "%f %f %f", &NS_ENG::Material::classMaterialList.back().emmi[0], &NS_ENG::Material::classMaterialList.back().emmi[1], &NS_ENG::Material::classMaterialList.back().emmi[2]);
			NS_ENG::Material::classMaterialList.back().emmi[3] = 1.0;

		}
		if(strcmp (id, "Ns") == 0)
		{
			//Specular exponent 0 to 1000

			GLfloat shin = 0.0f;
			fscanf_s(mtlFile, "%f", &shin);
			
			NS_ENG::Material::classMaterialList.back().shiny = shin;
		}
		else if (strcmp(id, "map_Kd") == 0)
		{
			//"map_bump"
			//here we implement a map object...
			bool duplicate = false;
			//load
			//GLuint tmp_TName;
				
			char path[80];

			fscanf_s (mtlFile, "%79s", path, sizeof(path));
			//string tmp_S_Path(path);





			FileTextureDesc NewDiffTex;
			//(NewDiffTex.Name = string("DiffuseTex:")+string(PathFindFileNameA(path));

			//boost::filesystem::path tmp_Path = boost::filesystem::path(path);
			
			boost::filesystem::path tmp_Path = boost::filesystem::path(Squiddy.FindAndRegister(path));

			

			
			boost::filesystem::path fileName = tmp_Path.filename();
			boost::filesystem::path Folder = tmp_Path.parent_path();


			vector<string> tokens;

			boost::split(tokens, fileName.string(), boost::is_any_of("_"));
			
			/*
			boost::char_separator<char> sep("_");

			boost::tokenizer< boost::char_separator<char> > tokens(fileName.string(), sep);
			//= "";
			
			//tokens.assign()
			std::string TagValue = "";
			//std::list< struct PointLightItem>::iterator

			//tokenizer::const_iterator()
			boost::tokenizer< boost::char_separator<char>>::iterator tok_it = tokens.begin();
			

			std::string Tag(tok_it->data());
			*/





			//NewDiffTex.Name = string("DiffuseTex:") + boost::filesystem::path(path).filename().string();
			NewDiffTex.Name = string("DiffuseTex: ") + tmp_Path.filename().string();

			
			NewDiffTex.Origin = "LoadMats: " + CurrentMaterial + " From:" + string(param);
			NewDiffTex.Description = "Use in the Geometry pass Set TextureUnit at Enum DiffuseMap_UNIT ";

			NewDiffTex.Target = GL_TEXTURE_2D;
			NewDiffTex.Map_Path = tmp_Path.string();
			NewDiffTex.internalFormat = GL_RGBA;
			NewDiffTex.format = GL_RGBA;
			NewDiffTex.type = GL_UNSIGNED_BYTE;
			NewDiffTex.filter = GL_NEAREST;


			//NS_ENG::Material::classMaterialList.back().enum_Map_Category

			//Map_Categories
			//0 Diffuse Forward_Diffuse
			//1 Bump
			NS_ENG::Material::classMaterialList.back().id_Map = MapAsset::LoadMaps(&NewDiffTex);
			//What I would do in the future, is to enact a Rule through a static functions and the LoadMaps or any other Static Asset Loader
			//would be instructed for that call to create the right Asset and set the right properties.
			//this would work well when I want to prepare a model but with different materials at its objects, those could be set with a string or with xml
		}

	}


	//NS_ENG::Material::classMaterialList.push_front(this);

	//iter = NS_ENG::Material::classMaterialList.begin();


		fclose(mtlFile);

		std::cout << "Loaded " << NrMatFile << ", Materials NR of materials so far : " << NS_ENG::Material::classMaterialList.size() << endl << "Done loading the " << param << " MTL---------" <<endl << endl;
		//cout << "NR of materials: " << Mats.m_Materials.size() << endl;
}



//per Packet being compiled, for each material found  if packet shader (vertex,geometry,fragment)  check for shader items(Type, EffectName)
//As far as i can tell a global Effect repo is needed, and loading mats can't be overly responsible for it

//effectname from MTL  None_xMaterialName  
//Check if "None" effect has pre_parsed code that needs to be added for shadertype, check if packet allready have the code
//std::string Material::AssureEffect{char* effectCode, string EffectName, Enum::ShaderType,  

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
	
	//float matInfo[12];



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
		//default bool



		//MatIter.diff[0]
		NS_VEC::VEC3 col1Diff(MatIter.diff[0], MatIter.diff[1], MatIter.diff[2]); // rotate around z-axis (in tangent space)
		rowMaterial.push_back(col1Diff);

		NS_VEC::VEC3 col1Spec(MatIter.spec[0], MatIter.spec[1], MatIter.spec[2]); // rotate around z-axis (in tangent space)
		rowMaterial.push_back(col1Spec);

		//need SamplerId
		//NS_VEC::VEC3 MapLocMapIdEffectId(1, MatIter.id_Map, MatIter.shiny); // rotate around z-axis (in tangent space)
		//rowMaterial.push_back(MapLocMapIdEffectId);

		//first value confirming Diffuse texture is assigned to material, 0 is no 1 is simple direct Loaded Texture, 2 is ArrayTexture
		//Second is a meta sampler ID, though each vec will deffine the type of texture, this will specify the sampler in question
		//Mostly important I feel for array texture collections which has different sizes
		//Third is relevant to Array Textures only, this is the layer ID
		//NS_VEC::VEC3 TexDiff(MatIter. MatIter.spec[1], MatIter.spec[2]); // rotate around z-axis (in tangent space)
		//rowMaterial.push_back(col1Spec);


		//if routinme to see if aspect of material have been checked
	}
	//GL_R8
	glGenTextures(1, &Material::MaterialMapTextureUnit);
	glBindTexture(GL_TEXTURE_2D, Material::MaterialMapTextureUnit);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 2, nr_mats, 0, GL_RGB, GL_FLOAT, &rowMaterial[0]);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 3, nr_mats, 0, GL_RGB, GL_FLOAT, &rowMaterial[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	return Material::MaterialMapTextureUnit;
}

//}
