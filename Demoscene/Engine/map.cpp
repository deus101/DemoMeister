#include "map.h"

#include <algorithm>
#include <stdio.h>
#include <iostream>

using namespace std;

using namespace NS_ENG;

//std::list <map> 
//map::classMapList = std::list <map>();

list<MapAsset*> MapAsset::classMapList = list<MapAsset*>();


MapAsset::MapAsset() : asset()
{
	//Mats.Clear();


}

void MapAsset::Draw()
{



}
//employ additional arguments:  type of map, origin
GLint MapAsset::LoadMaps(const char *param)
{
	string tmp_Path(param);
	bool duplicate = false;
	GLint R_MapId = -1;

	for (auto MapIter : NS_ENG::MapAsset::classMapList)
	{
		if (tmp_Path.compare(MapIter->Map_Path) == 0)
		{
			cout << " The Texture: " << MapIter->Map_MapID << " : have allready loaded the texture " << MapIter->Map_Path.data() << endl;
			//cout << " Using the GlName :" << MatIter.tUnit << endl;
			//meshy.m_Groups[u].matid = j;
			//meshy.m_Groups[u].matid = MatIter.matID;
			//NS_ENG::Material::classMaterialList.back().tUnit = MatIter.tUnit;
			//NS_ENG::Material::classMaterialList.back().tPath = tmp_Path;
			//MG.
			R_MapId = MapIter->Map_MapID;
			duplicate = true;
			break;
		}



	}

	if (duplicate)
		return R_MapId;

	MapAsset *tmp_Map = new MapAsset();

	GLuint tmp_TName = 0;
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(param, 0);
	FIBITMAP* imagen = FreeImage_Load(formato, param);

	//tmp_Map->bmp_Map

	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);

	int w = FreeImage_GetWidth(imagen);
	int h = FreeImage_GetHeight(imagen);
	cout << "The size of the image is: " << param << " es " << w << "*" << h << endl;
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLenum huboError = glGetError();
	if (huboError) {

		cout << "There was an error loading the texture" << endl;

	}

	//map::classMapList.push_back()
	//NS_ENG::map::classMapList.push_back(mtl);
	
	MapAsset::classMapList.push_front(tmp_Map);
	NS_ENG::MapAsset::classMapList.back()->Map_MapID =  NS_ENG::MapAsset::classMapList.size();
	//NS_ENG::MapAsset::classMapList.back()->MapIter = NS_ENG::MapAsset::classMapList.size();
	NS_ENG::MapAsset::classMapList.back()->Map_TUnit = tmp_TName;
	NS_ENG::MapAsset::classMapList.back()->Map_Path = tmp_Path;
	//NS_ENG::map::MapIter();
	//MapIter
	//NS_ENG::map::MapIter = NS_ENG::map::classMapList.begin();
	//classMapList
	return NS_ENG::MapAsset::classMapList.back()->Map_MapID;
}

//retrives MapAsset with MapId
MapAsset*  MapAsset::RetriveMap(GLint idx)
{

	//return NS_ENG::map::classMapList
	for (auto MapIter : NS_ENG::MapAsset::classMapList)
	{
		if (MapIter->Map_MapID == idx)
		{
			//cout << " The material: " << MatIter.matID << ":" << MatIter.name << " have allready loaded the texture " << MatIter.tPath << endl;
			//cout << " Using the GlName :" << MatIter.tUnit << endl;
			//meshy.m_Groups[u].matid = j;
			//meshy.m_Groups[u].matid = MatIter.matID;
			//NS_ENG::Material::classMaterialList.back().tUnit = MatIter.tUnit;
			//NS_ENG::Material::classMaterialList.back().tPath = tmp_Path;
			//MG.
			//duplicate = true;
			//break;
			return MapIter;
		}
	}
	
	return NULL;


}


/*
//load
GLuint tmp_TName = 0;
char path[80];
fscanf(mtlFile, "%79s", path);
FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(path, 0);
FIBITMAP* imagen = FreeImage_Load(formato, path);

FIBITMAP* temp = imagen;
imagen = FreeImage_ConvertTo32Bits(imagen);
FreeImage_Unload(temp);

int w = FreeImage_GetWidth(imagen);
int h = FreeImage_GetHeight(imagen);
cout << "The size of the image is: " << path << " es " << w << "*" << h << endl;
GLubyte* textura = new GLubyte[4 * w*h];
char* pixeles = (char*)FreeImage_GetBits(imagen);


for (int j = 0; j<w*h; j++){
textura[j * 4 + 0] = pixeles[j * 4 + 2];
textura[j * 4 + 1] = pixeles[j * 4 + 1];
textura[j * 4 + 2] = pixeles[j * 4 + 0];
textura[j * 4 + 3] = pixeles[j * 4 + 3];
}

glGenTextures(1, &tmp_TName);
glBindTexture(GL_TEXTURE_2D, tmp_TName);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)textura);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

GLenum huboError = glGetError();
if (huboError){

cout << "There was an error loading the texture" << endl;
}

*/