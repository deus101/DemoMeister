#ifndef MATERIALS_HPP
#define MATERIALS_HPP

#include <vector>
#include <deque> 
#include <string>
#include <string.h>
#include "../Math/vec.h"


//ok so think about changing these parameters per Model Object... or globally  The name itself could do the trick.
//tempted to add a list of references to all Models using this

//oh right...I never really made a class for materials...
namespace NS_MAT
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

void LoadMats( const char *param, MATERIALS& Mats);


}


//#pragma once

#endif
