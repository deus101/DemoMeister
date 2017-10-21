#include "GridPoints.h"

//Should rename this to CellPoints
using namespace NS_ENG;

//since we only deal with quadratics we only need one argument for size
//float Size_X, float Size_Y
GridPoints::GridPoints(int GridSize_X, int GridSize_Y, float CellSize, NS_VEC::VEC3 col) : asset()
{
	GLenum error;
	//Half size

	//CellPos = vector < NS_VEC::VEC2>;
	
	HalfSize = CellSize / 2;
	UniformCellSize = HalfSize;
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

			//just for testing //r+g+b
			CellAttrib.push_back(CellAttributes(NS_VEC::VEC2(xpos, ypos), NS_VEC::VEC3(r, g, b), 0.1f));
			//CellAttrib.push_back(CellAttributes(NS_VEC::VEC2(xpos, ypos), NS_VEC::VEC3(r, g, b), r + g + b));

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
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBufferData(GL_ARRAY_BUFFER, ColHeights.size() * sizeof(GLfloat), ColHeights.data(), GL_DYNAMIC_DRAW);
	//, 0, CellPos.size() *sizeof(NS_VEC::VEC2)
	error = glGetError();


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void GridPoints::Draw()
{

	UpdateLists();
	GLenum error;

	glBindVertexArray(vao_model);


	//glBindTexture(GL_TEXTURE_2D, Sort_Groups[i].tex);

	glDrawArrays(GL_POINTS, 0, (GLsizei)CellPos.size() );

	error = glGetError();

	glBindVertexArray(0);

	
	//UpdateLists();

	for (int i = 0; i < GridEffects.size(); i++)
	{
		//if false delete
		if (GridEffects[i].Increment(1+DeltaTime) == false)
		{ 
		GridEffects.erase((GridEffects.begin() + i));
		}
	}

}
void GridPoints::CreateGridActor(NS_VEC::VEC2 _pos, NS_VEC::VEC3 col, float high)
{
	GridEffects.push_back( AbstractModifier(this->UniformCellSize, this->UniformCellSize, _pos, high, col, 0.5f, 0.1f));



}
//maybe at the asset base class?
void GridPoints::SetDelta(double del)
{
	DeltaTime = float(del);



}

void GridPoints::Asciify(const char *word, int size)
{
	


}

void GridPoints::UpdateLists()
{
	GLenum error;
	//ColHeights.clear();
	//glBindVertexArray(vao_model);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color_fff);
	float *ColPtr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_height_f);
	float *HiPtr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	error = glGetError();
	if (HiPtr || ColPtr)
	{
		// wobble vertex in and out along normal
		//updateVertices(ptr, srcVertices, teapotNormals, vertexCount, (float)timer.getElapsedTime());
		//*ptr = *ColHeights.data();

		for (int i = 0; CellAttrib.size() > i; i++)
		{

			bool Modified = false;
			//the modified color
			NS_VEC::VEC3 modCol;
			float modHeight;
			
				for (int j = 0; j < GridEffects.size(); j++)
				{
					//CellAttrib[i].pos
					if (GridEffects[j].ModifyCell(CellAttrib[i].pos, modCol, modHeight) == true)
						Modified = true;
				}


				if (Modified == true)
				{
					CellAttrib[i].cellHeight = modHeight;
					*HiPtr = modHeight;
					HiPtr++;
					
					CellAttrib[i].cellCol.X = (modCol.X + *ColPtr) / 2 ;
					*ColPtr = CellAttrib[i].cellCol.X;
					ColPtr++;

					CellAttrib[i].cellCol.Y = (modCol.Y + *ColPtr) / 2;
					*ColPtr = CellAttrib[i].cellCol.Y;
					ColPtr++;

					CellAttrib[i].cellCol.Z = (modCol.Z + *ColPtr) / 2;
					*ColPtr = CellAttrib[i].cellCol.Z;
					ColPtr++;
				}
				else
				{
			if (CellAttrib[i].cellHeight > CellAttrib[i].defaultHeight)
				CellAttrib[i].cellHeight = CellAttrib[i].cellHeight - 0.1f;
			else if (CellAttrib[i].cellHeight < CellAttrib[i].defaultHeight)
				CellAttrib[i].cellHeight = CellAttrib[i].defaultHeight;

			float atHei = CellAttrib[i].cellHeight;

			*HiPtr = atHei;
			HiPtr++;

			//Color
			if (CellAttrib[i].cellCol.X > CellAttrib[i].defaultCol.X)
				CellAttrib[i].cellCol.X = CellAttrib[i].cellCol.X - 0.01f;
			else if (CellAttrib[i].cellCol.X < CellAttrib[i].defaultCol.X)
				CellAttrib[i].cellCol.X = CellAttrib[i].cellCol.X + 0.01f;
			*ColPtr = CellAttrib[i].cellCol.X;
			ColPtr++;

			if (CellAttrib[i].cellCol.Y > CellAttrib[i].defaultCol.Y)
				CellAttrib[i].cellCol.Y = CellAttrib[i].cellCol.Y - 0.01f;
			else if (CellAttrib[i].cellCol.Y < CellAttrib[i].defaultCol.Y)
				CellAttrib[i].cellCol.Y = CellAttrib[i].cellCol.Y + 0.01f;
			*ColPtr = CellAttrib[i].cellCol.Y;
			ColPtr++;


			if (CellAttrib[i].cellCol.Z > CellAttrib[i].defaultCol.Z)
				CellAttrib[i].cellCol.Z = CellAttrib[i].cellCol.Z - 0.01f;
			else if (CellAttrib[i].cellCol.Z < CellAttrib[i].defaultCol.Z)
				CellAttrib[i].cellCol.Z = CellAttrib[i].cellCol.Z + 0.01f;
			*ColPtr = CellAttrib[i].cellCol.Z;
			ColPtr++;

			
				}
			//CellPos.push_back(atPos);
			//CellCols.push_back(atCol);
			//ColHeights.push_back(atHei);


		}

		 // release pointer to mapping buffer
		
		error = glGetError();
		glBindBuffer(GL_ARRAY_BUFFER, vbo_height_f);
		glUnmapBuffer(GL_ARRAY_BUFFER);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_color_fff);
		glUnmapBuffer(GL_ARRAY_BUFFER);

		glMemoryBarrier(GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT);
	}
	
	//glBindVertexArray(vao_model);

	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glBufferData(GL_ARRAY_BUFFER, ColHeights.size() * sizeof(GLfloat), ColHeights.data(), GL_DYNAMIC_DRAW);

	

	//, 0, CellPos.size() *sizeof(NS_VEC::VEC2)
	error = glGetError();


	//glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}
