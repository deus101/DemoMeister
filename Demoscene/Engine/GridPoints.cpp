#include "GridPoints.h"

using namespace NS_ENG;

//since we only deal with quadratics we only need one argument for size
//float Size_X, float Size_Y
GridPoints::GridPoints(int GridSize_X, int GridSize_Y, float CellSize, NS_VEC::VEC3 col) : asset()
{
	GLenum error;
	//Half size

	//CellPos = vector < NS_VEC::VEC2>;

	HalfSize = CellSize / 2;

	//start
	int i = GridSize_X / 2;
	int j = GridSize_Y / 2;

	int LimI = -GridSize_X / 2;
	int LimJ = -GridSize_Y / 2;
	while (j >= LimJ)
	{
		float ypos = j * CellSize;
		while (i >= LimI)
		{
			float xpos = i * CellSize;

			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			//just for testing
			CellAttrib.push_back(CellAttributes(NS_VEC::VEC2(xpos, ypos), NS_VEC::VEC3(r,g,b), r+g+b));

			//CellAttrib.push_back(CellAttributes(NS_VEC::VEC2(xpos, ypos), col, 0.01f));
					i--;

			}
		j--;
		i = GridSize_X / 2;


	}

	for (i = 0; CellAttrib.size() > i; i++)
	{
		NS_VEC::VEC2 atPos = CellAttrib[i].pos;

		NS_VEC::VEC3 atCol = CellAttrib[i].cellCol;

		float atHei = CellAttrib[i].cellHeight;

		CellPos.push_back(atPos);
		CellCols.push_back(atCol);
		ColHeights.push_back(atHei);



	}

	
	glGenVertexArrays(1, &vao_model);
	glBindVertexArray( vao_model);
	




	glGenBuffers(1, &vbo_points);


	glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBufferData(GL_ARRAY_BUFFER, CellPos.size() * sizeof(GLfloat) * 2, CellPos.data(), GL_STATIC_DRAW);
	//, 0, CellPos.size() *sizeof(NS_VEC::VEC2)
	error = glGetError();


	glGenBuffers(1, &vbo_color_fff);


	glBindBuffer(GL_ARRAY_BUFFER, vbo_color_fff);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBufferData(GL_ARRAY_BUFFER, CellCols.size() * sizeof(GLfloat) * 3, CellCols.data(), GL_STATIC_DRAW);
	//, 0, CellPos.size() *sizeof(NS_VEC::VEC2)
	error = glGetError();

	glGenBuffers(1, &vbo_height_f);


	glBindBuffer(GL_ARRAY_BUFFER, vbo_height_f);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBufferData(GL_ARRAY_BUFFER, ColHeights.size() * sizeof(GLfloat), ColHeights.data(), GL_DYNAMIC_DRAW);
	//, 0, CellPos.size() *sizeof(NS_VEC::VEC2)
	error = glGetError();


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void GridPoints::Draw()
{


	GLenum error;

	glBindVertexArray(vao_model);



	//glBindTexture(GL_TEXTURE_2D, Sort_Groups[i].tex);

	glDrawArrays(GL_POINTS, 0, CellPos.size() );

	error = glGetError();

	glBindVertexArray(0);

	UpdateLists();

}

void GridPoints::UpdateLists()
{
	ColHeights.clear();
	for (int i = 0; CellAttrib.size() > i; i++)
	{
		

		//NS_VEC::VEC3 atCol = CellAttrib[i].cellCol;

		if (CellAttrib[i].cellHeight > CellAttrib[i].defaultHeight)
			CellAttrib[i].cellHeight = -0.01;
		else if (CellAttrib[i].cellHeight < CellAttrib[i].defaultHeight)
			CellAttrib[i].cellHeight = CellAttrib[i].defaultHeight;

		float atHei = CellAttrib[i].cellHeight;

		//CellPos.push_back(atPos);
		//CellCols.push_back(atCol);
		ColHeights.push_back(atHei);



	}
	GLenum error;
	glBindVertexArray(vao_model);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_height_f);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBufferData(GL_ARRAY_BUFFER, ColHeights.size() * sizeof(GLfloat), ColHeights.data(), GL_DYNAMIC_DRAW);
	//, 0, CellPos.size() *sizeof(NS_VEC::VEC2)
	error = glGetError();


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}
