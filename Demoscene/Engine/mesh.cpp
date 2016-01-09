#include "mesh.h"
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
using namespace NS_VEC;

namespace NS_MESH
{
	



	void LoadMesh( const char *param, MESH &Mesh)
	{

		FILE * objFile;
		objFile = fopen ( param, "rb");

		Mesh.Clear();
	
		
		char line[1024] = "";
		char id[512] = "";

		while( fscanf (objFile, "%s", id) > 0)
		{
			if(strcmp (id, "v") == 0)
			{
				VEC3 v; 
				fscanf (objFile, "%f %f %f", &v.X, &v.Y, &v.Z);


				Mesh.m_Pos.push_back(v);

			}
			if(strcmp (id, "vt") == 0)
			{
				VEC2 uv;
				fscanf (objFile, "%f %f", &uv.X, &uv.Y);

				Mesh.m_Uvs.push_back(uv);
			}
			if(strcmp (id, "vn") == 0)
			{
				VEC3 vn;
				fscanf (objFile, "%f %f %f", &vn.X, &vn.Y, &vn.Z);
				vn.NormIt();
				Mesh.m_Norms.push_back(vn);
			}
			if(strcmp ( id, "g") == 0)
			{
				s_Group temp;
				char nam[50];
				char mat[50];
				fscanf (objFile, "%s \n", &nam);
				fscanf (objFile, "%s", &mat);
				fscanf (objFile, "%s", &mat);
				temp.mat = mat;

				
				temp.group_name = nam;

				Mesh.m_Groups.push_back( temp );
				
				cout << "Group: " << temp.group_name << endl;
				cout << "Material: " << temp.mat << endl << endl;
				
			}
			else  //problem
			if(strcmp (id, "f") == 0)
			{

				s_Face F;

				while(true)
				{
					s_FaceVertex FV;


					if(fscanf(objFile, "%i/%i/%i", &FV.m_PID, &FV.m_UID, &FV.m_NID) <= 0)
					break;

					
					//cout << " pid: " << FV.m_PID << " nid: " << FV.m_NID << endl;
					--FV.m_PID;
					--FV.m_UID;
					--FV.m_NID;

					F.m_Verts.push_back ( FV );
				}
				if(F.m_Verts.size() >= 3)
				{

					//This is just a primite trying to calculate the midpoint of the triangle
					//its irrelevant in the indexing
					VEC3 a, b, c;
					a = Mesh.m_Pos[ F.m_Verts[0].m_PID];
					b = Mesh.m_Pos[ F.m_Verts[1].m_PID];
					c = Mesh.m_Pos[ F.m_Verts[2].m_PID];
					
					
					//F.m_vNorm.CalcNorm ( a, b, c);

					F.m_vMid.X = ((a.X + b.X + c.X)/3);
					F.m_vMid.Y = ((a.Y + b.Y + c.Y)/3);
					F.m_vMid.Z = ((a.X + b.Z + c.Z)/3);

					//cout << "NOrmal " << F.m_vNorm.X << " " << F.m_vNorm.Y << " " << F.m_vNorm.Z << endl;
				
					Mesh.m_Groups.back().m_Faces.push_back( F );

			} 	

			}

		}

	fclose (objFile);
	cout << " nr vertex: " << Mesh.m_Pos.size() << endl;
	cout << " nr UVs: " << Mesh.m_Uvs.size() << endl;
	cout << " nr normals: " << Mesh.m_Norms.size() << endl;
	cout << " nr groups: " << Mesh.m_Groups.size() << endl;

	}

}
