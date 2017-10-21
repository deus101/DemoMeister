#include "ArrayMap.h"


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






	this->Map_TName = tmp_TName;

	return tmp_TName;
}
void ArrayMap::Init()
{



	
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->Map_TName);

	glTexStorage3D(GL_TEXTURE_2D_ARRAY,
		5,                    //5 mipmaps
		GL_RGB,               //Internal format
		1024, 1024,           //width,height
		256                   //Number of layers
	);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);




}