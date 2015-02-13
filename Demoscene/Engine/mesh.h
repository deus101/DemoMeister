#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <deque> 
#include <string>
#include <string.h>
#include "../Math/vec.h"


namespace NS_MESH
{
	//APPAPPAPAPAA 
//using namespace std;
//using namespace NS_VEC;

struct s_FaceVertex
{

		s_FaceVertex()
		{
			m_PID = 0;
			m_UID = 0;
			m_NID = 0;
		}

		unsigned int m_PID;
		unsigned int m_UID;
		unsigned int m_NID;

		//half edge here?
		// unsigned int m_line
		

};

struct s_Face
{
	s_Face()
	{
		m_Verts.reserve( 4 );
	}
	
	//VEC3 m_vNor;
	NS_VEC::VEC3 m_vMid;
	vector< s_FaceVertex > m_Verts;
	
};


struct s_Group
{	
	
	s_Group()
	{
		group_name ="       ";
		m_Faces.clear();
		
	}
	string group_name;
	string mat;
	int matid;
	deque< s_Face > m_Faces;


};




struct MESH
{
	deque<NS_VEC::VEC3> m_Pos;
	deque<NS_VEC::VEC3> m_Norms;
	deque<NS_VEC::VEC2> m_Uvs;
	 

	deque<s_Group> m_Groups;
	


	

	void Clear (void)
	{
		m_Pos.clear();
		m_Norms.clear();
		m_Uvs.clear();

		m_Groups.clear();
		

	}
};

void LoadMesh( const char *param, MESH& Mesh);

}
#pragma once

#endif
