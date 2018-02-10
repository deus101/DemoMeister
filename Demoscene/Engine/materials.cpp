#include "materials.h"
//#include "map.h"
//#include "AssetMapClasses\map.h"
#include "AssetMapClasses\FileTexture.h"
#include <DemoMeister\world.h>
///#include "../Libs/FreeImage.h"


#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <boost\filesystem.hpp>
//#include <Shlwapi.h>
#include <boost\tokenizer.hpp>
#include <boost\algorithm\string.hpp>
#include <boost\make_shared.hpp>

using namespace NS_ENG;
using namespace std;



list<boost::shared_ptr< Material  >> NS_ENG::Material::ClassMaterialList;

GLuint Material::baseMaterialMapTextureUnit = 0;


Material::Material() : asset::asset()
{
	//Mats.Clear();

}

int NS_ENG::Material::Load(const char * param)
{
	return 0;
}


void Material::LoadMats( const char *param)
{




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
			NS_ENG::Material::ClassMaterialList.push_back(boost::make_shared<NS_ENG::Material>());
			NrMatFile++;
			//s_mat mtl;
			char nam[80] ="";
			fscanf_s(mtlFile, "%79s", nam ,sizeof(nam));
			
			//name = nam;

			//Mats.m_Materials.push_back( mtl );
			
			CurrentMaterial = nam;
			


			NS_ENG::Material::ClassMaterialList.back()->Mat_Name = CurrentMaterial;

			std::cout << "-material name: " << NS_ENG::Material::ClassMaterialList.back()->Mat_Name << endl;
			NS_ENG::Material::ClassMaterialList.back()->Tex_Has_BumpTexture = FALSE;
			NS_ENG::Material::ClassMaterialList.back()->Tex_Has_DiffuseTexture = FALSE;
			NS_ENG::Material::ClassMaterialList.back()->Mat_MatID = (GLint) NS_ENG::Material::ClassMaterialList.size();
		}
		if(strcmp (id, "Kd") == 0)
		{
			//diffuse reflectivity  RGB


			fscanf_s(mtlFile, "%f %f %f", &NS_ENG::Material::ClassMaterialList.back()->Mat_Diff[0], &NS_ENG::Material::ClassMaterialList.back()->Mat_Diff[1], &NS_ENG::Material::ClassMaterialList.back()->Mat_Diff[2]);

			NS_ENG::Material::ClassMaterialList.back()->Mat_Diff[3] = 1.0;

		}
		if(strcmp (id, "Ka") == 0)
		{
			//ambient reflectivity using RGB


		
			fscanf_s(mtlFile, "%f %f %f", &NS_ENG::Material::ClassMaterialList.back()->Mat_Amb[0], &NS_ENG::Material::ClassMaterialList.back()->Mat_Amb[1], &NS_ENG::Material::ClassMaterialList.back()->Mat_Amb[2]);
			NS_ENG::Material::ClassMaterialList.back()->Mat_Amb[3] = 1.0;
		}
		if(strcmp (id, "Ks") == 0)
		{
			//specular reflectivity RGB
		
			fscanf_s(mtlFile, "%f %f %f", &NS_ENG::Material::ClassMaterialList.back()->Mat_Spec[0], &NS_ENG::Material::ClassMaterialList.back()->Mat_Spec[1], &NS_ENG::Material::ClassMaterialList.back()->Mat_Spec[2]);
			NS_ENG::Material::ClassMaterialList.back()->Mat_Spec[3] = 1.0;
		}
		if(strcmp (id, "Ke") == 0)
		{	//emmisive in rgb or should it just be a float
			NS_VEC::VEC3 c;
			
			fscanf_s(mtlFile, "%f %f %f", &NS_ENG::Material::ClassMaterialList.back()->Mat_Emmi[0], &NS_ENG::Material::ClassMaterialList.back()->Mat_Emmi[1], &NS_ENG::Material::ClassMaterialList.back()->Mat_Emmi[2]);
			NS_ENG::Material::ClassMaterialList.back()->Mat_Emmi[3] = 1.0;

		}
		if(strcmp (id, "Ns") == 0)
		{
			//Specular exponent 0 to 1000

			GLfloat shin = 0.0f;
			fscanf_s(mtlFile, "%f", &shin);
			
			NS_ENG::Material::ClassMaterialList.back()->Mat_Shiny = shin;
		}
		else if (strcmp(id, "map_Kd") == 0)
		{
			
			bool duplicate = false;
	
				
			char path[80] = "";

			fscanf_s (mtlFile, "%79s", path, (unsigned int)size(path));
			
			string tmp_S_Path(path);



			NS_ENG::Material::ClassMaterialList.back()->Tex_Has_DiffuseTexture = TRUE;

			
		

			
			std::string faen( Squiddy.FindAndRegister(tmp_S_Path));
			boost::filesystem::path tmp_Path = boost::filesystem::path(faen);

			boost::filesystem::path fileName = tmp_Path.filename();
			boost::filesystem::path Folder = tmp_Path.parent_path();


			FileTextureDesc *NewDiffTex = new FileTextureDesc();
			NewDiffTex->Name = string("DiffuseTex:") + tmp_Path.filename().string();

			NewDiffTex->Origin = string(__FUNCTION__) + "(" + std::string(param) +  ") " + " Material: " + string(CurrentMaterial) + "\n";
			NewDiffTex->Description = "Use in the Geometry pass Set TextureUnit at Enum DiffuseMap_UNIT ";

			NewDiffTex->Target = GL_TEXTURE_2D;
			NewDiffTex->Map_Path = tmp_Path.string();
			NewDiffTex->internalFormat = GL_RGBA;
			NewDiffTex->format = GL_RGBA;
			NewDiffTex->type = GL_UNSIGNED_BYTE;
			NewDiffTex->filter = GL_NEAREST;
			NewDiffTex->MapContent = NS_ENG::MAP_CONTENT_TYPE::DIFFUSE;



			TheDisc->AddTexture(tmp_Path, NS_ENG::Material::ClassMaterialList.back()->Tex_Has_DiffuseTexture, NewDiffTex);


			//What I would do in the future, is to enact a Rule through a static functions and the LoadMaps or any other Static Asset Loader
			//would be instructed for that call to create the right Asset and set the right properties.
			//this would work well when I want to prepare a model but with different materials at its objects, those could be set with a string or with xml
		}

	}



		fclose(mtlFile);

		std::cout << "Loaded " << NrMatFile << ", Materials NR of materials so far : " << NS_ENG::Material::ClassMaterialList.size() << endl << "Done loading the " << param << " MTL---------" <<endl << endl;
}



//per Packet being compiled, for each material found  if packet shader (vertex,geometry,fragment)  check for shader items(Type, EffectName)
//As far as i can tell a global Effect repo is needed, and loading mats can't be overly responsible for it

//effectname from MTL  None_xMaterialName  
//Check if "None" effect has pre_parsed code that needs to be added for shadertype, check if packet allready have the code
//std::string Material::AssureEffect{char* effectCode, string EffectName, Enum::ShaderType,  


//OK, for materials This was abandoned but it could still be usefull to have
std::string Material::Shaderfy() {
	//forget this for now work ing static int GeneratebaseMaterialMap();
	bool first = true;
	string GlSL = "//retrive materials \n ";

	//actually as I expand the baseMaterialMap it would be nice to have procedures drawn up
	//for GLSL, possibly another lamebrain idea I just got for the ASSET monstrosity
	//BUT NOT THIS YEAR!


	int nr_mats =(int) ClassMaterialList.size();




	for (auto MatIter : NS_ENG::Material::ClassMaterialList)
	{
		string Current;
		if(first == true)
		{
			Current =  string(" if(ID=") + std::to_string((int)MatIter->Mat_MatID) + string("){\n ");
			first = false;
		}
		else
		{
		
			Current = string(" else-if(ID=") + std::to_string((int)MatIter->Mat_MatID) + string("){\n ");
		}

		string Diffuse = string(" MatDiffuse =  vec4(") 
			+ std::to_string((float)MatIter->Mat_Diff[0])
			+ string(",")
			+ std::to_string((float)MatIter->Mat_Diff[1])
			+ string(",")
			+ std::to_string((float)MatIter->Mat_Diff[2])
			+ string(",")
			+ std::to_string((float)MatIter->Mat_Diff[3])
			+ string(");\n ");
		string Specular = string(" MatSpecular =  vec4(")
			+ std::to_string((float)MatIter->Mat_Diff[0])
			+ string(",")
			+ std::to_string((float)MatIter->Mat_Diff[1])
			+ string(",")
			+ std::to_string((float)MatIter->Mat_Diff[2])
			+ string(",")
			+ std::to_string((float)MatIter->Mat_Diff[3])
			+ string(");\n ") + string(" }");
		
	
		GlSL += Current;
		GlSL += Diffuse;
		GlSL += Specular;

	}




	cout << GlSL;
	return GlSL;
}

GLuint Material::GeneratebaseMaterialMap() {


	
	int nr_mats = (int)NS_ENG::Material::ClassMaterialList.size();



	if(Material::baseMaterialMapTextureUnit != 0)
		return Material::baseMaterialMapTextureUnit;

	std::vector<NS_VEC::VEC3> rowMaterial;

	for (auto MatIter : NS_ENG::Material::ClassMaterialList)
	{

		NS_VEC::VEC3 col1Diff(MatIter->Mat_Diff[0], MatIter->Mat_Diff[1], MatIter->Mat_Diff[2]);
		rowMaterial.push_back(col1Diff);

		NS_VEC::VEC3 col1Spec(MatIter->Mat_Spec[0], MatIter->Mat_Spec[1], MatIter->Mat_Spec[2]);
		rowMaterial.push_back(col1Spec);
       //this way we cans skip needless inquireries...nah pointless, dont waste the space
		NS_VEC::VEC3 MapLocMapIdEffectId(
			MatIter->Tex_Diffuse_SamplerID, 
			MatIter->Tex_Diffuse_Layer,
			MatIter->Tex_Has_BumpTexture);
		rowMaterial.push_back(MapLocMapIdEffectId);
		

		//first value confirming Diffuse texture is assigned to material, 0 is no 1 is simple direct Loaded Texture, 2 is ArrayTexture
		//Second is a meta sampler ID, though each vec will deffine the type of texture, this will specify the sampler in question
		//Mostly important I feel for array texture collections which has different sizes
		//Third is relevant to Array Textures only, this is the layer ID
		//NS_VEC::VEC3 TexDiff(MatIter. MatIter.spec[1], MatIter.spec[2]); // rotate around z-axis (in tangent space)
		//rowMaterial.push_back(col1Spec);

		
		//if routinme to see if aspect of material have been checked
	}
	

	//this probably can't wait next year, fix the fucking layout to something useable so it can be properly
	//UGH! TextureName! not unit!
	glGenTextures(1, &Material::baseMaterialMapTextureUnit);
	glBindTexture(GL_TEXTURE_2D, Material::baseMaterialMapTextureUnit);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 2, nr_mats, 0, GL_RGB, GL_FLOAT, &rowMaterial[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 3, nr_mats, 0, GL_RGB, GL_FLOAT, &rowMaterial[0]);
	

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	base_buffer::AddGlobalTexture("baseMaterialMap", GL_TEXTURE_2D, Material::baseMaterialMapTextureUnit, nr_mats, 0, true); 
	return Material::baseMaterialMapTextureUnit;
}

