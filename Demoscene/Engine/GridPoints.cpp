#include "GridPoints.h"


GridPoints::GridPoints()
{
}


void GridPoints::Draw()
{




	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (unsigned int i = 0; i < Sort_Groups.size(); i++)
	{


		glBindVertexArray(Sort_Groups[i].vao);

		if (Sort_Groups[i].tex != NULL)
		{
			glActiveTexture(COLOR_TEXTURE_UNIT);
			glBindTexture(GL_TEXTURE_2D, Sort_Groups[i].tex);
		}
		//gl::Uniform4fv(DifLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].diff);
		//gl::Uniform4fv(AmbLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].amb);
		//gl::Uniform4fv(SpecLoc, 1, (const GLfloat *)palette.m_Materials[meshy.m_Groups[i].matid].spec);
		//gl::Uniform1f(ShiLoc, palette.m_Materials[meshy.m_Groups[i].matid].shiny);
		//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, (GLintptr)_data.indices.length, _data.indices.bytes);
		//glDrawElements(GL_TRIANGLES, Sort_Groups[i].IBO.size(), GL_UNSIGNED_SHORT, (void*)0);

		glDrawElements(GL_TRIANGLES, Sort_Groups[i].IBO.size(), GL_UNSIGNED_INT, (void*)0);


	}
	glBindVertexArray(0);

}


