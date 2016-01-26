#include "materials.h"
#include "../Libs/FreeImage.h"


#include <algorithm>
#include <stdio.h>
#include <iostream>

using namespace std;



namespace NS_MAT
{

	

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
				NS_VEC::VEC3 c;
				fscanf(mtlFile, "%f %f %f", &Mats.m_Materials.back().emmi[0], &Mats.m_Materials.back().emmi[1], &Mats.m_Materials.back().emmi[2]);
				Mats.m_Materials.back().emmi[3] = 1.0;
			}
			if(strcmp (id, "Ns") == 0)
			{
				GLfloat c = 0.0f;
				fscanf(mtlFile, "%f", &c );
				Mats.m_Materials.back().shiny = c;
			}
			else
			if (strcmp(id, "map_Kd") == 0)
			{
				GLuint tmp_TName = 0;
				char path[50];
				fscanf(mtlFile, "%s \n", &path);
				FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(path, 0);
				//FreeImageIO
				FIBITMAP* imagen = FreeImage_Load(formato, path);

				FIBITMAP* temp = imagen;
				imagen = FreeImage_ConvertTo32Bits(imagen);
				FreeImage_Unload(temp);

				int w = FreeImage_GetWidth(imagen);
				int h = FreeImage_GetHeight(imagen);
				cout << "The size of the image is: " << path << " es " << w << "*" << h << endl; 
				GLubyte* textura = new GLubyte[4 * w*h];
				char* pixeles = (char*)FreeImage_GetBits(imagen);
			

				for (int j = 0; j<w*h; j++){
					textura[j * 4 + 0] = pixeles[j * 4 + 2];
					textura[j * 4 + 1] = pixeles[j * 4 + 1];
					textura[j * 4 + 2] = pixeles[j * 4 + 0];
					textura[j * 4 + 3] = pixeles[j * 4 + 3];
				}

				glGenTextures(1, &tmp_TName);
				glBindTexture(GL_TEXTURE_2D, tmp_TName);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)textura);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

				GLenum huboError = glGetError();
				if (huboError){

					cout << "There was an error loading the texture" << endl;
				}

				Mats.m_Materials.back().tUnit = tmp_TName;
			}

		}


		fclose(mtlFile);

		cout << "NR of materials: " << Mats.m_Materials.size() << endl;

	}

}
