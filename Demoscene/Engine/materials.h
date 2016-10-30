#ifndef MATERIALS_HPP
#define MATERIALS_HPP

#include <vector>
#include <deque> 
#include <string>
#include <string.h>
#include "../Math/vec.h"




//oh right...I never really made a class for materials...
namespace NS_MAT
{
//using namespace std;
//using namespace NS_VEC;

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
