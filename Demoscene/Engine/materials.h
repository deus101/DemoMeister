#ifndef MATERIALS_HPP
#define MATERIALS_HPP

#include <vector>
#include <deque> 
#include <string>
#include <string.h>
#include "asset.h"
#include "../Math/vec.h"


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
			tUnit = NULL;
	}
std::string name;
GLfloat amb[4];
GLfloat diff[4];
GLfloat spec[4];
GLfloat emmi[4];
GLfloat shiny;
//not unit.. name...right?
GLint tUnit;
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


private:
	//std::list <Material*>::iterator MatIter;
	std::list <s_mat>::iterator MatIter;
public:
	//static std::list <Material*> classMaterialList;
	static std::list <s_mat> classMaterialList;

	std::string Mat_Name;
	GLfloat Mat_Amb[4];
	GLfloat Mat_Diff[4];
	GLfloat Mat_Spec[4];
	GLfloat Mat_Emmi[4];
	GLfloat Mat_Shiny;
	//not unit.. name...right?
	//needs more then just a texture name
	
	GLint Mat_TUnit;
	GLint Mat_MatID;

Material();

static void LoadMats(const char *param);

//hurm sometimes oop makes no sense
//void Draw();
//or my fix ideas makes no sense

//MATERIALS& Mats;

};

}


//#pragma once

#endif
