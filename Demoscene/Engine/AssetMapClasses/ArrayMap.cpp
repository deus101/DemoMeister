#include "ArrayMap.h"
#include <iostream>

#include "FileTexture.h"
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

	glGenTextures(1, &this->Map_TName);






	this->BaseArrayData = *ArrayTexMeta;


	return this->Map_TName;
}


void ArrayMap::Init()
{
	std::cout << "ArrayTexture==========" << std::endl;
	std::cout << "The " << this->Base_Data.Name << " is initialising." << std::endl;


	GLsizei NR_Layers = this->BaseArrayData.SubItemsID.size();


	unsigned int Width = this->BaseArrayData.w;
	unsigned int Height = this->BaseArrayData.h;

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D_ARRAY, this->Map_TName);
	
	GLenum Binderror = glGetError();
	if (Binderror) {

		std::cout << "There was an error loading the texture " << Binderror << std::endl;
		fprintf(stderr, "Error: %s\n", glewGetErrorString(Binderror));
	}


	GLenum Format = (GLenum)this->BaseArrayData.format;
	GLenum InternalFormat = (GLenum)this->BaseArrayData.internalFormat;
	GLenum Type = (GLenum)this->BaseArrayData.type;




	std::cout << std::endl << "ArrayTexture Parameters"<< std::endl;
	std::cout << "Height:Width" << std::endl;
	std::cout << (GLsizei)Height << std::endl;
	std::cout << Width << std::endl;

	fprintf(stdout, "Version: %s\n", glGetString(GL_VERSION));

	fprintf(stdout, "InternalFormat: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));




	GLsizei test = std::max<GLsizei>((GLsizei)1, ((GLsizei)Width / 4));


	
	
	//

	GLsizei WidthOffset = std::max<GLsizei>((GLsizei)1, ((GLsizei)Width / 4));
	GLsizei HeightOffset = std::max<GLsizei>((GLsizei)1, ((GLsizei)Height / 4));
	GLsizei LayerOffset = std::max<GLsizei>((GLsizei)1, ((GLsizei)NR_Layers / 4));

	GLsizei MaxWidth= std::max<GLsizei>((GLsizei)1, ((GLsizei)Width ));
	GLsizei MaxHeight = std::max<GLsizei>((GLsizei)1, ((GLsizei)Height ));
	GLsizei MaxLayer = std::max<GLsizei>((GLsizei)1, ((GLsizei)NR_Layers ));


	glTexStorage3D(
		GL_TEXTURE_2D_ARRAY,
		GLsizei(1),
		GL_RGBA8,
		std::max<GLsizei>((GLsizei)1, ((GLsizei)Width)),
		std::max<GLsizei>((GLsizei)1, ((GLsizei)Height)),
		MaxLayer  
		
	);

	/*
	glTexImage3D(GL_TEXTURE_2D_ARRAY,
		0,
		eFormat,
		uiWidth, uiHeight,
		static_cast<uint32>(vPixelData.size()),
		0,
		eFormat,
		GL_UNSIGNED_BYTE,
		NULL);

	*/




	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);


	//glGetInternalformativ(GL_TEXTURE_2D, GL_RGBA8, GL_TEXTURE_IMAGE_FORMAT, 1, &prefFormat);
	
	GLenum StorrageError = glGetError();
	if (StorrageError) {

		fprintf(stderr, "glTexStorage3D: %s\n", glewGetErrorString(StorrageError));
	}

	GLint Layer = 0;


	std::list<GLint>::const_iterator iterator;
	for(iterator = this->BaseArrayData.SubItemsID.begin(); iterator != this->BaseArrayData.SubItemsID.end(); ++iterator)
	{
		

	NS_ENG::FileTexture *Data = dynamic_cast<NS_ENG::FileTexture*>( MapAsset::RetriveMap(iterator._Ptr->_Myval).get()  );


	Data->Total_Layers = NR_Layers;
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 
		0,
		0, 0, Layer,
		MaxHeight, MaxHeight, 1,
		GL_BGRA, GL_UNSIGNED_BYTE,
		(GLvoid*)Data->textura);



	Layer++;
	}

	GLenum huboError = glGetError();
	if (huboError) {

		 std::cout << "There was an error loading the texture " << huboError << std::endl;
		 fprintf(stderr, "Error: %s\n", glewGetErrorString(huboError));
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}