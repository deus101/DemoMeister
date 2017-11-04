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

	std::cout << "Texture==========" << std::endl;
	std::cout << "The ArrayTexture" << ArrayTexMeta->Name << " Have been declared" <<std::endl;

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
	std::cout << "ArrayTexture==========" << std::endl;
	std::cout << "The " << this->Base_Data.Name << " is initialising." << std::endl;


	GLsizei NR_Layers = this->BaseArrayData.SubItemsID.size();
	GLsizei Width = (GLsizei)this->BaseArrayData.w;
	GLsizei Height = (GLsizei)this->BaseArrayData.h;

	//GLsizei Width = (GLsizei)this->BaseArrayData.w;
	//GLsizei Height = (GLsizei)this->BaseArrayData.h;
	
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->Map_TName);


	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(NR_Layers) - 1);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_R, Format.Swizzle[0]);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_G, Format.Swizzle[1]);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_B, Format.Swizzle[2]);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_A, Format.Swizzle[3]);

	glTexStorage3D(
		GL_TEXTURE_2D_ARRAY,
		static_cast<GLint>(NR_Layers) -1 , GL_RGBA8,
		//this->Base_Data.internalFormat,              
		static_cast<GLsizei>(Width), static_cast<GLsizei>(Height),
		static_cast<GLsizei>(1)
	);



	GLsizei Layer = 0;
	//glTexImage3D
	t_SharedMapPtr SubMap = NULL;
	std::list<GLint>::const_iterator iterator;
	for(iterator = this->BaseArrayData.SubItemsID.begin(); iterator != this->BaseArrayData.SubItemsID.end(); ++iterator)
	{
		
		SubMap = MapAsset::RetriveMap(iterator._Ptr->_Myval);



	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, static_cast<GLint>(Layer), static_cast<GLsizei>(Width), static_cast<GLsizei>(Height), static_cast<GLsizei>(1), SubMap->Base_Data.format, SubMap->Base_Data.type, (GLvoid*)SubMap->textura);
	
	//glTexSubImage2D(GL_TEXTURE_2D_ARRAY, Layer,0,0,Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, SubMap->textura);
	//SubMap->Base_Data.wrap
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Layer++;
	}
	GLenum huboError = glGetError();
	if (huboError) {

		 std::cout << "There was an error loading the texture " <<huboError << std::endl;
	
	}

}