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


namespace NS_ENG{

	class GridPoints : public asset
	{
	public:

		struct CellAttributes{
			NS_VEC::VEC3 cellCol;
			NS_VEC::VEC3 defaultCol;
			NS_VEC::VEC2 pos;
			float cellHeight;
			float defaultHeight;
			CellAttributes(){};
			CellAttributes(NS_VEC::VEC2 XY ,NS_VEC::VEC3 defCol, float defHei){
				pos = XY;
				defaultCol = defCol;
				cellCol = defCol;
				//just for testing
				//defaultHeight = defHei;
				defaultHeight = 0.1;
				cellHeight = defHei;

			};

		};

		std::vector<NS_VEC::VEC2> CellPos;
		std::vector<NS_VEC::VEC3> CellCols;
		std::vector<float> ColHeights;

		std::vector<CellAttributes> CellAttrib;
		//NS_VEC::VEC3 CellPos[][];
		
		//Vec4(x = pos.X, y = cellHeight, Z = pos.Y, a = packed RGB
		//std::vector<NS_VEC::VEC4> CellData;


		GridPoints(int GridSize_X, int GridSize_Y, float GridSize, NS_VEC::VEC3 col = NS_VEC::VEC3(0.0, 0.749,1.0));
		
		//Let the node handle that?
		//CreateHeightMap
		GLuint vao_model;
		GLuint vbo_points; //ff
		GLuint vbo_height_f;
		GLuint vbo_color_fff;
		GLuint vbo_PosColHei_ffff; //vec for y comp as height and alpha as a packed rgb vector
		//color.r + color.g * 256.0 + color.b * 256.0 * 256.0


		//GLuint vbo_height;
		//GLuint vbo_col;
		GLfloat defaultHeight;
		GLfloat defaultColor;

		//shader uniform values
		//
		GLfloat HalfSize; 
		
		//I think I can figoure out to create a non quadric grid but why bother
		void Draw();

		void AtEase();
		void UpdateBuffers();

		void StimulateCell(int index, NS_VEC::VEC3 col, float high = 0.0f);



	private:

		void UpdateLists();

	
	};

}