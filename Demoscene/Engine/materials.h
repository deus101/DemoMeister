#ifndef MATERIALS_HPP
#define MATERIALS_HPP

#include <vector>
#include <deque> 
#include <string>
#include <string.h>
#include "asset.h"
#include <Math\vec.h>


//ok so think about changing these parameters per Model Object... or globally  The name itself could do the trick.
//tempted to add a list of references to all Models using this

//oh right...I never really made a class for materials...
//it makes more sense that if I have a data structure for Mesh I should have one for texture
//namespace NS_MAT
namespace NS_ENG 
{
//using namespace std;
//using namespace NS_VEC;


//this I need, possibly better to use for argument when constructing ubershader
struct s_mat
{
	s_mat()
	{
		name = "           ";
			shiny = 0.0f;
			id_Map = NULL;
	}
std::string name;
GLfloat amb[4];
GLfloat diff[4];
GLfloat spec[4];
GLfloat emmi[4];
GLfloat shiny;
//not unit.. name...right?
//GLint tUnit;
GLint id_Map;
//basically to identify the texture
std::string tPath;

GLint matID;

};
//replace this with a class
struct MATERIALS
{
	void Clear(void)
	{
		m_Materials.clear();
	}

std::deque<s_mat> m_Materials;

};
//void LoadMats( const char *param, MATERIALS& Mats);
class Material : public asset
{

	//FUCK! Forgot about this.
private:
	
	std::list <boost::shared_ptr<Material>>::iterator MatIter;
	//std::list <s_mat>::iterator MatIter;
public:
	static std::list <boost::shared_ptr<Material>> ClassMaterialList;
	//static std::list <s_mat> ClassMaterialList;
	//
	static GLuint baseMaterialMapTextureUnit;


	std::string Mat_Name;
	GLfloat Mat_Amb[4];
	GLfloat Mat_Diff[4];
	GLfloat Mat_Spec[4];
	GLfloat Mat_Emmi[4];
	GLfloat Mat_Shiny;


	//not unit.. name...right?
	//needs more then just a texture name
	

	//0 none, 1 forwarded drawn and loaded, 2 Global ArrayTexture
	GLint Tex_Has_DiffuseTexture;
	GLint Tex_Has_BumpTexture;

	//Zero if one, 
	GLint Tex_Diffuse_SamplerID;
	//Zero if one, we know we need to access the Bump/Normal Map sampler because we are activly looking up the range in the baseMaterialMap
	//I imagine if you have 512 sized seamless textures and 1024 sized ones we need to create texture arrays for both
	//There is a different between bump and normal map remember that
	GLint Tex_Bump_SamplerID;

	//Zero if one in Tex_Has_DiffuseTexture
	GLint Tex_Diffuse_Layer;
	GLint Tex_Bump_Layer;

	//The model class should not be responsible in loading the ArrayTextures or baseMaterialMap
	//Model must only load the forward rendered ones
	GLint Mat_TUnit;
	GLint Mat_MatID;

Material();

~Material() {};

void Load() {};

int Load(const char *param);


void Init() {};


void Draw() {  };






static void LoadMats(const char *param);

static std::string  Shaderfy();

static GLuint GeneratebaseMaterialMap();
//hurm sometimes oop makes no sense
//void Draw();
//or my fix ideas makes no sense

//MATERIALS& Mats;

};

}


//#pragma once

#endif
