#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <deque> 
#include <string>
#include <string.h>
#include <Math/vec.h>
#include <Math/math3d.h>
//should I consider giving this a static container?
//NO!
namespace NS_MESH
{

struct s_FaceVertex
{

		s_FaceVertex()
		{
			m_PID = 0;
			m_UID = 0;
			m_NID = 0;
		}


		int m_PID;
		int m_UID;
		int m_NID;

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
	std::vector< s_FaceVertex > m_Verts;
	
};

/*
	s_ModelAid()
	{

		v4_BB[0] = 0;
		v4_BB[1] = 0;
		v4_BB[2] = 0;
		v4_BB[3] = 0;
		Orientation.W = 0;
		Orientation.X = 0;
		Orientation.Y = 0;
		Orientation.Z = 0;
		MidPointReach[0] = 0;
		MidPointReach[1] = 0;
		MidPointReach[2] = 0;
		MidPointReach[3] = 0;
		MatObjChildTech[0] = 0;
		MatObjChildTech[1] = 0;
		MatObjChildTech[2] = 0;
		MatObjChildTech[3] = 0;
	}*/

struct s_ModelAid
{

	s_ModelAid()
	{
		m3dLoadVector4(v4_BB_Min, 0.0, 0.0, 0.0, 0.0);
		m3dLoadVector4(v4_BB_Max, 0.0, 0.0, 0.0, 0.0);
		m3dLoadVector4(MidPointReach, 0.0, 0.0, 0.0, 0.0);
		m3dLoadVector4(MatObjChildTech, 0.0, 0.0, 0.0, 0.0);
	}
	M3DVector4f v4_BB_Min;
	M3DVector4f v4_BB_Max;
	M3DVector4f MidPointReach;
	M3DVector4f MatObjChildTech;
	//NS_VEC::QUAT Orientation;
	

};



struct s_Group
{	
	
	s_Group()
	{
		group_name ="       ";
		m_Faces.clear();

	}
	std::string group_name;
	std::string mat;
	int matid;
	std::deque< s_Face > m_Faces;
	
	s_ModelAid Child;

};



//husk denne idean, cube texture, geometri shader, og bygninger I profil.
struct MESH
{
	std::string file_name;
	std::string file_mat;
	

	std::deque<NS_VEC::VEC3> m_Pos;
	std::deque<NS_VEC::VEC3> m_Norms;
	std::deque<NS_VEC::VEC2> m_Uvs;
	std::deque<NS_VEC::VEC3> m_Tangent;
	//m3dCalculateTangentBasis(M3DVector3f vTangent,

	std::deque<s_Group> m_Groups;
	
	//M3DVector4f v4_BB_Sum;
	//NS_VEC::QUAT Orientation;
	//M3DVector4f MidPointReach;
	//M3DVector4f MatObjChildTech;

	s_ModelAid Child;

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
