#include "materials.h"

#include <algorithm>
#include <stdio.h>
#include <iostream>
namespace NS_MAT
{

	using namespace std;

	void LoadMats( const char *param, MATERIALS& Mats)
	{
		FILE * mtlFile;
		mtlFile = fopen( param , "rb");

		Mats.Clear();
	
		
		char line[1024] = "";
		char id[512] = "";

		while( fscanf (mtlFile, "%s", id) > 0)
		{
			if(strcmp (id, "newmtl") == 0)
			{
				s_mat mtl;
				char nam[50];
				fscanf(mtlFile, "%s \n", &nam );
				mtl.name = nam;
				//cout << "material name: " << mtl.name << endl;
				Mats.m_Materials.push_back( mtl );
			}
			if(strcmp (id, "Kd") == 0)
			{
				
				fscanf(mtlFile, "%f %f %f", &Mats.m_Materials.back().diff[0], &Mats.m_Materials.back().diff[1], &Mats.m_Materials.back().diff[2]);
				Mats.m_Materials.back().diff[3] = 1.0;
				
					//input[3] = 1.0;
				//Mats.m_Materials.back().diff = input;
			}
			if(strcmp (id, "Ka") == 0)
			{
				
				fscanf(mtlFile, "%f %f %f", &Mats.m_Materials.back().amb[0], &Mats.m_Materials.back().amb[1], &Mats.m_Materials.back().amb[2]);
				Mats.m_Materials.back().amb[3] = 1.0;
			}
			if(strcmp (id, "Ks") == 0)
			{
			
				fscanf(mtlFile, "%f %f %f", &Mats.m_Materials.back().spec[0], &Mats.m_Materials.back().spec[1], &Mats.m_Materials.back().spec[2]);
				Mats.m_Materials.back().spec[3] = 1.0;
			}
			if(strcmp (id, "Ke") == 0)
			{	
				VEC3 c;
				fscanf(mtlFile, "%f %f %f", &Mats.m_Materials.back().emmi[0], &Mats.m_Materials.back().emmi[1], &Mats.m_Materials.back().emmi[2]);
				Mats.m_Materials.back().emmi[3] = 1.0;
			}
			else
			if(strcmp (id, "Ns") == 0)
			{
				GLfloat c = 0.0f;
				fscanf(mtlFile, "%f", &c );
				Mats.m_Materials.back().shiny = c;
			}

		}


		fclose(mtlFile);

		cout << "NR of materials: " << Mats.m_Materials.size() << endl;

	}

}
