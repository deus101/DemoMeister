#include "ArrayMap.h"
#include <iostream>

using namespace NS_ENG;

ArrayMap::ArrayMap() : MapAsset()
{



}



void ArrayMap::Draw()
{



}



int ArrayMap::Load(ArrayTextureDesc* ArrayTexMeta)
{
	GLuint tmp_TName = 0;

	glGenTextures(1, &tmp_TName);


	//this->b




	//this->Base_Data = ArrayTexMeta-
	this->BaseArrayData = *ArrayTexMeta;
	this->Map_TName = tmp_TName;

	return tmp_TName;
}
void ArrayMap::Init()
{

	GLsizei NR_Layers = this->BaseArrayData.SubItemsID.size();
	GLsizei Width = (GLsizei)this->BaseArrayData.w;
	GLsizei Height = (GLsizei)this->BaseArrayData.h;
	
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->Map_TName);



	glTexStorage3D(GL_TEXTURE_2D_ARRAY,
		0,                    //5 mipmaps
		this->Base_Data.internalFormat,               //Internal format
		Width, Height,           //width,height
		NR_Layers                   //Number of layers
	);

	GLsizei Layer = 0;

	t_SharedMapPtr SubMap = NULL;
	std::list<GLint>::const_iterator iterator;
	for(iterator = this->BaseArrayData.SubItemsID.begin(); iterator != this->BaseArrayData.SubItemsID.end(); ++iterator)
	{
		
		SubMap = MapAsset::RetriveMap(iterator._Ptr->_Myval);



	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, Layer, Width, Height, 1, GL_RGBA, GL_UNSIGNED_BYTE, SubMap->textura);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	Layer++;
	}
	GLenum huboError = glGetError();
	if (huboError) {

		 std::cout << "There was an error loading the texture" << huboError << std::endl;

	}

}