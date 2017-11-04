#include "FileTexture.h"
#include <iostream>



using namespace NS_ENG;

FileTexture::FileTexture() : MapAsset()
{


}


/*
void FileTexture::Draw()
{



}

void FileTexture::Load()
{

}

*/


int FileTexture::Load(FileTextureDesc* FileTexMeta)
{
	GLuint tmp_TName = 0;
	glGenTextures(1, &tmp_TName);


	

	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(FileTexMeta->Map_Path.c_str(), 0);
	FIBITMAP* imagen = FreeImage_Load(formato, FileTexMeta->Map_Path.c_str());

	//tmp_Map->bmp_Map

	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);

	int w = FreeImage_GetWidth(imagen);
	int h = FreeImage_GetHeight(imagen);
	//is it worthwhile to try scale the texture?
	FileTexMeta->w = w;
	FileTexMeta->h = h;
	// << "The size of the image is: " << TextureMeta->Map_Path.c_str() << " es " << w << "*" << h << endl;
	//GLubyte* textura = new GLubyte[4 * w*h];
	this->textura = new GLubyte[4 * w*h];
	char* pixeles = (char*)FreeImage_GetBits(imagen);


	for (int j = 0; j<w*h; j++) {
		this->textura[j * 4 + 0] = pixeles[j * 4 + 2];
		this->textura[j * 4 + 1] = pixeles[j * 4 + 1];
		this->textura[j * 4 + 2] = pixeles[j * 4 + 0];
		this->textura[j * 4 + 3] = pixeles[j * 4 + 3];
	}
	this->Base_Data = *FileTexMeta;

	
	this->Map_TName = tmp_TName;
	return tmp_TName;
}





//Overload with ArrayTextureDesc
//int FileTexture::Init(FileTextureDesc *tmpFileTexMeta)
//int FileTexture::Init(FileTextureDesc* FileTexMeta)
void FileTexture::Init()
{

	
	/*
	//FileTextureDesc TextureMeta
	if(this->Map_TName == 0)
	{ 
	
	GLuint tmp_TName = 0;

	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(FileTexMeta->Map_Path.c_str(), 0);
	FIBITMAP* imagen = FreeImage_Load(formato, FileTexMeta->Map_Path.c_str());

	//tmp_Map->bmp_Map

	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);

	int w = FreeImage_GetWidth(imagen);
	int h = FreeImage_GetHeight(imagen);
	//is it worthwhile to try scale the texture?
	FileTexMeta->w = w;
	FileTexMeta->h = h;
	// << "The size of the image is: " << TextureMeta->Map_Path.c_str() << " es " << w << "*" << h << endl;
	//GLubyte* textura = new GLubyte[4 * w*h];
	char* pixeles = (char*)FreeImage_GetBits(imagen);


	for (int j = 0; j<w*h; j++) {
		this->textura[j * 4 + 0] = pixeles[j * 4 + 2];
		this->textura[j * 4 + 1] = pixeles[j * 4 + 1];
		this->textura[j * 4 + 2] = pixeles[j * 4 + 0];
		this->textura[j * 4 + 3] = pixeles[j * 4 + 3];
	}

	

	glGenTextures(1,&tmp_TName);

	this->Map_TName = tmp_TName;
	}
	*/

	if(this->Base_Data.MapCategory == MAP_ASSEMBLY_TYPE::FILE_TEXTURE)
	{
	glBindTexture(GL_TEXTURE_2D, this->Map_TName);
	glTexImage2D(GL_TEXTURE_2D, 0, this->Base_Data.internalFormat, this->Base_Data.w, this->Base_Data.h, 0, this->Base_Data.format, this->Base_Data.type, (GLvoid*)textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	
	GLenum huboError = glGetError();
	if (huboError) {

		std::cout << "There was an error loading the texture" << std::endl;

	}
	
	}
	


	
	//this->Base_Data = (tmpFileTexMeta)FileTexMeta;
	
	//this->Map_TName = tmp_TName;
	//return tmp_TName;
	//return this->Map_TName;
}






/*
FileTexture::~FileTexture()
{
}
*/