#pragma once

#include <string>
#include <vector>
#include <deque> 
#include <map>


#include "mesh.h"
#include "materials.h"
#include "../ShaderFu/GeomPacket.h"
#include "../ShaderFu/HeightMapPacket.h"
#include "../Rendrer/context.h"


namespace NS_ENG{

	//effect classes specifically for grids
	//ideas is to have a container of these objects that will deleted themselves when its moved on
	/*
	int Char_A[9][9] ={
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 2, 1, 0, 0, 0 },
		{ 0, 0, 1, 2, 1, 2, 1, 0, 0 },
		{ 0, 1, 2, 1, 0, 1, 2, 1, 0 },
		{ 0, 1, 2, 1, 0, 1, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 1, 1, 1, 2, 1, 0 },
		{ 0, 1, 1, 1, 0, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

*/
	class AbstractModifier
	{
		//used for intersection at a given point form a cell
		//use half sizes ugh course we only use scalar for product for now
		float Dim_X, Dim_Y;
		//finding out distance
		NS_VEC::VEC2 orig;
		//what color value for the grid effect
		NS_VEC::VEC3 colorModifier;
		//amplitude?
		float heightModifier;

		
		//bool finished;
		//end of base properties



	private:
		//lifespan ends when there are no grid cells to modify.
		bool finished;

		float radius;
		//incremental radius increase
		float increment;
		//If distance and radius is match up send the new height and color values
		//Radius should maybe be in one of the concrete classes
	public:
		 AbstractModifier(float dX, float dY, NS_VEC::VEC2 v, float mod_amp, NS_VEC::VEC3 mod_col, float rad, float rad_inc)
			: Dim_X(dX), Dim_Y(dY), orig(v), colorModifier(mod_col), heightModifier(mod_amp), radius(rad), increment(rad_inc)
		{};


		//Virtual methods, regular ones for now
		//finds out if cell is in scope of the effect and returns the modifiers.
		bool ModifyCell(NS_VEC::VEC2 cellPos, NS_VEC::VEC3 &ret_Col, float &ret_h)
		{
			NS_VEC::VEC2 p = cellPos;
			NS_VEC::VEC2 O = orig;
			float dist = (p -= O).CalcLength();

			if ((dist + Dim_X) >= radius && (dist - Dim_X) <= radius)
			{
				ret_Col = this->colorModifier;
				ret_h = this->heightModifier;
				finished = false;
				return true;

			}
			else
				return false;

			//this->orig

		};

		//does two things, first it chekcs wheter it modified any cells in previous frame
		//second it increment, this should also be a virtual method. 
		bool Increment(float Delta = 1.0f)
		{
			if (finished){
				//tell grid class to remove from container
				return false;
			}
			else{
				
				this->radius += this->increment * Delta;
				finished = true;
				return true;
			}
		}

	};


	class GridPoints : public asset
	{
	public:
		float DeltaTime;

		struct CellAttributes{
			NS_VEC::VEC3 cellCol;
			NS_VEC::VEC3 defaultCol;
			NS_VEC::VEC2 pos;
			float cellHeight;
			float defaultHeight;
			CellAttributes(){};
			CellAttributes(NS_VEC::VEC2 XY ,NS_VEC::VEC3 defCol, float defHei){
				pos = XY;
				defaultCol = NS_VEC::VEC3(0.0f, 0.749f, 1.0f);
				cellCol = defCol;
				//just for testing
				//defaultHeight = defHei;
				defaultHeight = 0.1f;
				cellHeight = defHei;

			};

		};


		float UniformCellSize;

		std::vector<NS_VEC::VEC2> CellPos;
		std::vector<NS_VEC::VEC3> CellCols;
		std::vector<float> ColHeights;

		std::vector<CellAttributes> CellAttrib;
		//NS_VEC::VEC3 CellPos[][];
		std::vector<NS_ENG::AbstractModifier> GridEffects;

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
		void SetDelta(double d = 1.0);

		void StimulateCell(int index, NS_VEC::VEC3 col, float high = 0.0f);
		//Composite methods not sure which one to use...
		void CreateGridActor(NS_VEC::VEC2 _pos, NS_VEC::VEC3 col, float high = 0.0f);

		void Asciify(const char *word, int size);

	private:

		void UpdateLists();

	
	};

}