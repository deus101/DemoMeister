#pragma once

#include "map.h"

namespace NS_ENG
{


class FileTexture : public MapAsset{

public:

	FileTexture();


	int Load(FileTextureDesc* FileTexMeta);


	void Init();


	void Draw() {  };


	~FileTexture() {};

	std::string Map_Path;

	//this one needs proper garbage handling, hell all of my classes do.
	FREE_IMAGE_FORMAT format;
	FIBITMAP* bmp_Map;


};




}