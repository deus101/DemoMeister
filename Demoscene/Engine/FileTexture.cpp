#include "FileTexture.h"
#include <iostream>



using namespace NS_ENG;

FileTexture::FileTexture() : MapAsset()
{


}



void FileTexture::Draw()
{



}
//int FileTexture::Init(FileTextureDesc *tmpFileTexMeta)
int FileTexture::Init(FileTextureDesc* FileTexMeta)
{

	
	//FileTextureDesc TextureMeta = (FileTextureDesc)BaseMapMeta;
	//FileTextureDesc TextureMeta = static_cast<FileTextureDesc>(BaseMapMeta);
	//FileTextureDesc TextureMeta = reinterpret_cast<FileTextureDesc>(tmpFileTexMeta);
	//FileTextureDesc TextureMeta( (FileTextureConstPtr)tmpFileTexMeta);
	//FileTextureDesc TextureMeta = FileTextureDesc((FileTextureConstPtr)tmpFileTexMeta);
	//FileTextureDesc TextureMeta = reinterpret_cast<FileTextureDesc&>(tmpFileTexMeta);
	//FileTextureDesc TextureMeta = reinterpret_cast<FileTextureDesc&>(tmpFileTexMeta);
	//FileTextureDesc TextureMeta(*(TextureDescPtr)this->Base_Data );
	//FileTextureDesc TextureMeta(*tmpFileTexMeta);
	//FileTextureDesc TextureMeta = FileTexMeta;
		
		//this->Base_Data;
	//FileTextureDesc TextureMeta = FileTextureDesc((dynamic_cast<FileTextureConstPtr>(tmpFileTexMeta)));

	
	//FileTextureDesc TextureMeta
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
	GLubyte* textura = new GLubyte[4 * w*h];
	char* pixeles = (char*)FreeImage_GetBits(imagen);


	for (int j = 0; j<w*h; j++) {
		textura[j * 4 + 0] = pixeles[j * 4 + 2];
		textura[j * 4 + 1] = pixeles[j * 4 + 1];
		textura[j * 4 + 2] = pixeles[j * 4 + 0];
		textura[j * 4 + 3] = pixeles[j * 4 + 3];
	}

	glGenTextures(1, &tmp_TName);
	glBindTexture(GL_TEXTURE_2D, tmp_TName);
	glTexImage2D(GL_TEXTURE_2D, 0, FileTexMeta->internalFormat, w, h, 0, FileTexMeta->format, FileTexMeta->type, (GLvoid*)textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	
	GLenum huboError = glGetError();
	if (huboError) {

		std::cout << "There was an error loading the texture" << endl;

	}
	


	this->Base_Data = *FileTexMeta;

	
	//this->Base_Data = (tmpFileTexMeta)FileTexMeta;
	
	this->Map_TName = tmp_TName;
	return tmp_TName;
}






/*
FileTexture::~FileTexture()
{
}
*/