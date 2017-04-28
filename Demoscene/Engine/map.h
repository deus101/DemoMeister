#ifndef MAP_HPP
#define MAP_HPP

#include "asset.h"
//#include "../Effect/GeomPacket.h"
#include "../Libs/FreeImage.h"
#include "../util.h"



namespace NS_ENG
{
	class MapAsset : public asset
	{
	private:
		list <MapAsset*>::iterator MapIter;
	public:
		static list <MapAsset*> classMapList;

		/*
		enum MAP_TYPE {
			MAP_TYPE_,
			GBUFFER_TEXTURE_TYPE_DIFFUSE,
			GBUFFER_TEXTURE_TYPE_NORMAL,
			GBUFFER_TEXTURE_TYPE_UV,
			GBUFFER_NUM_TEXTURES
		};
		*/
		MapAsset();
		static GLint LoadMaps(const char *param);

		static MapAsset* RetriveMap(GLint);
		//~map();
		//static void LoadMaps(const char *param);


		void Draw();

		GLint Map_MapID;
		//char path[80];
		//actually the proper place
		GLint Map_TUnit;

		//Location to map
		string Map_Path;
		
		FREE_IMAGE_FORMAT format;
		FIBITMAP* bmp_Map;

	//GL_NEAREST or point filtering.
	//Something something 
	//NS_VEC::VEC2 

	//There should be more arguments depending on what kind of map it is
		//for now keep it simple...also should Load* ve a virtual function toed to  asset?
		//I could use draw for that matter...AAAH BETTER GPUIFY!
		//static void LoadMaps(const char *param);
	};

}

#endif