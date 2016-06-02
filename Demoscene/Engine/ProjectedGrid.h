#pragma once

#include <string>
#include <vector>
#include <deque> 
#include <map>


#include "mesh.h"
#include "materials.h"
#include "../Effect/GeomPacket.h"
#include "../Effect/HeightMapPacket.h"
#include "../Rendrer/context.h"


namespace NS_ENG {




	class ProjectedGrid : public asset
	{
	public:
		float DeltaTime;



	


		int  i_Grid_Res;
		float  f_Grid_Scale;
		float f_Grid_Height;


		std::vector<NS_VEC::VEC3> G_Vertice;
		std::vector<NS_VEC::VEC2> G_UV;

		
		//NS_VEC::VEC3 CellPos[][];
		//Vec4(x = pos.X, y = cellHeight, Z = pos.Y, a = packed RGB
		//std::vector<NS_VEC::VEC4> CellData;


		ProjectedGrid(int GridSize, float GridScale, float GridHeight);

		//Let the node handle that?
		//CreateHeightMap
		GLuint vao_model;
		GLuint vbo_points; //ff


								   //GLuint vbo_height;
								   //GLuint vbo_col;
		GLfloat defaultHeight;
		GLfloat defaultColor;

		//shader uniform values
		//

		//I think I can figoure out to create a non quadric grid but why bother
		void Draw();

		void AtEase();
		void UpdateBuffers();
		void SetDelta(double d = 1.0);



	private:

		void UpdateLists();


	};

}