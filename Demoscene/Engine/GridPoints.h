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
		std::vector<NS_VEC::VEC2> CellPos;

		//NS_VEC::VEC3 CellPos[][];



		GridPoints(int GridSize_X, int GridSize_Y, float Size_X, float Size_Y);
		
		//Let the node handle that?
		//CreateHeightMap
		GLuint vao_model;
		GLuint vbo_points;
		//GLuint vbo_height;
		//GLuint vbo_col;

		void Draw();

	private:

	
	};

}