#include "GridPoints.h"

using namespace NS_ENG;

GridPoints::GridPoints(int GridSize_X, int GridSize_Y, float Size_X, float Size_Y) : asset()
{
	GLenum error;
	//Half size

	//CellPos = vector < NS_VEC::VEC2>;

	float HalfSizeX = Size_X / 2;

	//start
	int i = GridSize_X / 2;
	int j = GridSize_Y / 2;

	int LimI = -GridSize_X / 2;
	int LimJ = -GridSize_Y / 2;
	while (j >= LimJ)
	{
		float ypos = j * Size_Y;
		while (i >= LimI)
		{
			float xpos = i * Size_X;
			CellPos.push_back(NS_VEC::VEC2(xpos, ypos));
					i--;

			}
		j--;
		i = GridSize_X / 2;


	}

	glGenVertexArrays(1, &vao_model);
	glBindVertexArray( vao_model);
	glGenBuffers(1, &vbo_points);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
	glBufferData(GL_ARRAY_BUFFER, CellPos.size() * sizeof(GLfloat) * 2, CellPos.data(), GL_STATIC_DRAW);
	//, 0, CellPos.size() *sizeof(NS_VEC::VEC2)
	error = glGetError();
	glBindVertexArray(0);

}


void GridPoints::Draw()
{


	GLenum error;

	glBindVertexArray(vao_model);



	//glBindTexture(GL_TEXTURE_2D, Sort_Groups[i].tex);

	glDrawArrays(GL_POINTS, 0, CellPos.size() );

	error = glGetError();

	glBindVertexArray(0);

}


