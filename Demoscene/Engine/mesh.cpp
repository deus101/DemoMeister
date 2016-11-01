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
	
		Mesh.file_name = param;
		
		char line[1024] = "";
		char id[512] = "";
		bool b_groupFirst = false;
		bool b_RelativeIndex = false;
		bool b_hasUvs = false;
		bool b_hasNorm = false;

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
				
				b_hasUvs = true;
			}
			if(strcmp (id, "vn") == 0)
			{
				VEC3 vn;
				fscanf (objFile, "%f %f %f", &vn.X, &vn.Y, &vn.Z);
				vn.NormIt();
				Mesh.m_Norms.push_back(vn);

				b_hasNorm = true;
			}
			if(strcmp ( id, "g") == 0)
			{
				//Mesh.m_Pos.size
				s_Group temp;
				char nam[50] = "";
				char mat[50] = "";
				fscanf (objFile, "%s \n", &nam);
				fscanf (objFile, "%s", &mat);
				fscanf (objFile, "%s", &mat);
				temp.mat = mat;

				
				temp.group_name = nam;

				Mesh.m_Groups.push_back( temp );
				
				std::cout << "Group: " << temp.group_name << endl;
				std::cout << "Material: " << temp.mat << endl << endl;


				//if group is first defined then in most sane cases the indeices are relative that is negative
				//if (Mesh.m_Pos.size() == 0 && b_groupFirst != true);
					
				if (Mesh.m_Pos.size() == int(0))
				{
					//int faen = Mesh.m_Pos.size();
					b_groupFirst = true;
					b_RelativeIndex = true;
				}
		
			}
			else  //problem
			if(strcmp (id, "f") == 0)
			{

				s_Face F;

				while(true)
				{
					s_FaceVertex FV;

					if (b_hasUvs == false)
					{
						if (fscanf(objFile, "%i//%i", &FV.m_PID, &FV.m_NID) <= 0)
						break;

						//FV.m_UID = 4294967296;

					}
					else
					{

					
					if(fscanf(objFile, "%i/%i/%i", &FV.m_PID, &FV.m_UID, &FV.m_NID) <= 0)
					break;
					}
					//fscanf(objFile, "%i/%i/%i", &FV.m_PID, &FV.m_UID, &FV.m_NID);
					
					//b_RelativeIndex = true;
					//cout << " pid: " << FV.m_PID << " nid: " << FV.m_NID << endl;


					if(b_RelativeIndex != true)
					{ 
					--FV.m_PID;
					--FV.m_UID;
					--FV.m_NID;
					}


					F.m_Verts.push_back ( FV );
				}
				if(F.m_Verts.size() >= 3)
				{

					//This is just a primite trying to calculate the midpoint of the triangle
					//its irrelevant in the indexing
					VEC3 a, b, c;

					int i_relativeIndicatorPos = 0;
					int i_relativeIndicatorUvs = 0;
					int i_relativeIndicatorNrm = 0;

					if (b_RelativeIndex == true){
						i_relativeIndicatorPos = Mesh.m_Pos.size();
						i_relativeIndicatorUvs = Mesh.m_Uvs.size();
						i_relativeIndicatorNrm = Mesh.m_Norms.size();

					}



					a = Mesh.m_Pos[i_relativeIndicatorPos + F.m_Verts[0].m_PID];
					b = Mesh.m_Pos[i_relativeIndicatorPos + F.m_Verts[1].m_PID];
					c = Mesh.m_Pos[i_relativeIndicatorPos + F.m_Verts[2].m_PID];
					
					F.m_Verts[0].m_PID = F.m_Verts[0].m_PID + i_relativeIndicatorPos;
					F.m_Verts[1].m_PID = F.m_Verts[1].m_PID + i_relativeIndicatorPos;
					F.m_Verts[2].m_PID = F.m_Verts[2].m_PID + i_relativeIndicatorPos;

					//F.m_vNorm.CalcNorm ( a, b, c);

					F.m_vMid.X = ((a.X + b.X + c.X)/3);
					F.m_vMid.Y = ((a.Y + b.Y + c.Y)/3);
					F.m_vMid.Z = ((a.X + b.Z + c.Z)/3);

					//cout << "NOrmal " << F.m_vNorm.X << " " << F.m_vNorm.Y << " " << F.m_vNorm.Z << endl;
					//4294967295
					if (b_hasNorm == false)
					{
						VEC3 NewNormal;
						//Mesh.m_Uvs.push_back(uv);
						NewNormal.CalcNorm(a, b, c);
						Mesh.m_Norms.push_back(NewNormal);
						int NewNormInd = Mesh.m_Norms.size() -1;
						F.m_Verts[0].m_NID = NewNormInd;
						F.m_Verts[1].m_NID = NewNormInd;
						F.m_Verts[2].m_NID = NewNormInd;
					}
					else if (b_hasNorm == true || b_RelativeIndex == true)
					{
						F.m_Verts[0].m_NID = F.m_Verts[0].m_NID + i_relativeIndicatorNrm;
						F.m_Verts[1].m_NID = F.m_Verts[1].m_NID + i_relativeIndicatorNrm;
						F.m_Verts[2].m_NID = F.m_Verts[2].m_NID + i_relativeIndicatorNrm;

					}

					if (b_hasUvs == false)
					{
						VEC2 fake_uv1, fake_uv2, fake_uv3;
						//Mesh.m_Uvs.push_back(uv);
						fake_uv1 = VEC2(0, 1);
						fake_uv2 = VEC2(1, 1);
						fake_uv3 = VEC2(1, 0);
						Mesh.m_Uvs.push_back(fake_uv1); 
						int NewUvId1 = Mesh.m_Uvs.size() - 1;
						Mesh.m_Uvs.push_back(fake_uv2);
						int NewUvId2 = Mesh.m_Uvs.size() - 1;
						Mesh.m_Uvs.push_back(fake_uv3);
						int NewUvId3 = Mesh.m_Uvs.size() - 1;

						F.m_Verts[0].m_UID = NewUvId1;
						F.m_Verts[1].m_UID = NewUvId2;
						F.m_Verts[2].m_UID = NewUvId3;

					}
					else if (b_hasUvs == true || b_RelativeIndex == true)
					{
						F.m_Verts[0].m_UID = F.m_Verts[0].m_UID + i_relativeIndicatorUvs;
						F.m_Verts[1].m_UID = F.m_Verts[1].m_UID + i_relativeIndicatorUvs;
						F.m_Verts[2].m_UID = F.m_Verts[2].m_UID + i_relativeIndicatorUvs;

					}


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
