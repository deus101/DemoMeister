#ifndef MAP_HPP
#define MAP_HPP

#include "asset.h"
//#include "../Effect/GeomPacket.h"
#include "../Libs/FreeImage.h"
#include "../util.h"



namespace NS_ENG
{
	class map : public asset
	{
	private:
		std::list <map*>::iterator MapIter;
	public:
		static std::list <map*> classMapList;

	//actually the proper place
	GLint Mat_TUnit;

	//Location to map
	string Mat_Path;

	//Something something 
	//NS_VEC::VEC2 

	//There should be more arguments depending on what kind of map it is
	//for now keep it simple...also should Load* ve a virtual function toed to  asset?
	//I could use draw for that matter...AAAH BETTER GPUIFY!
	void LoadMaps(const char *param);
	};

}

#endif