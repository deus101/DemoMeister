#pragma once

#include "map.h"

namespace NS_ENG
{

	//typedef boost::shared_ptr< FileTexture> FileTexturePtr;

	//typedef boost::shared_ptr<const  FileTexture> FileTextureConstPtr;

class FileTexture : public MapAsset{

public:

	FileTexture();

	//int Init(FileTextureDesc *BaseMapMeta);
	//void Load();
	
	int Load(FileTextureDesc* FileTexMeta);


	void Init();


	void Draw() {  };


	~FileTexture() {};

	std::string Map_Path;


	FREE_IMAGE_FORMAT format;
	FIBITMAP* bmp_Map;

	//FileTextureDesc FileTexMeta;

};




}