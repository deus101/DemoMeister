#include "GridPoints.h"

using namespace NS_ENG;

GridPoints::GridPoints(int GridSize_X, int GridSize_Y, float Size_X, float Size_Y)
{
	//Half size

	//CellPos = vector < NS_VEC::VEC2>;

	float HalfSizeX = Size_X / 2;

	//start
	int i = GridSize_X / 2;
	int j = GridSize_Y / 2;

	int LimI = -GridSize_X / 2;
	int LimJ = -GridSize_Y / 2;
	while (j > LimJ)
	{
		float ypos = j * Size_Y;
		while (i > LimI)
		{
			float xpos = i * Size_X;
			CellPos.push_back(NS_VEC::VEC2(xpos, ypos));
					i--;

			}
		j--;


	}


}


void GridPoints::Draw()
{







	//glBindTexture(GL_TEXTURE_2D, Sort_Groups[i].tex);

	glDrawArrays(GL_POINT_BIT, 0, CellPos.size() *sizeof(NS_VEC::VEC2));



	//glBindVertexArray(0);

}


