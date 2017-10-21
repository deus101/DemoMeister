


#include <algorithm>
#include <stdio.h>
#include <iostream>

#include "map.h"
#include "FileTexture.h"
#include "ArrayMap.h"
#include <boost/make_shared.hpp>
using namespace std;

using namespace NS_ENG;





list<boost::shared_ptr<  MapAsset >> NS_ENG::MapAsset::classMapList;


MapAsset::MapAsset() : asset()
{
	//Mats.Clear();
	//FileTextureDesc test;
	//test.
	this->textura = NULL;
}


GLint MapAsset::LoadMaps(TextureDesc  *ToCreate, ArrayTextureDesc *ToBind = NULL)
{


	if (ToBind != NULL)
	{
		for (auto MapIter : NS_ENG::MapAsset::classMapList)
		{
			if (ToBind->Name.compare(MapIter->Base_Data.Name) == 0)
			{
				cout << " The Texture: " << ToCreate->Name << " From " << ToCreate->Origin << " Have Allready been Declared by:  "

					<< MapIter->Map_MapID << endl;

				//_MapId = MapIter->Map_MapID;
				//duplicate = true;
				break;
			}
		}
	}










	//FileTextureDesc Meta();
	bool duplicate = false;
	GLint R_MapId = -1;

	//GAH! Fuck it! I can't derail on optimasation, get it working
	//https://stackoverflow.com/questions/2236482/data-structure-that-maps-unique-id-to-an-object
	for (auto MapIter : NS_ENG::MapAsset::classMapList)
	{
		if (ToCreate->Name.compare(MapIter->Base_Data.Name) == 0)
		{
			cout << " The Texture: " << ToCreate->Name << " From " << ToCreate->Origin << " Have Allready been Declared by:  " 

				<< MapIter->Map_MapID << endl; 

			R_MapId = MapIter->Map_MapID;
			duplicate = true;
			break;
		}



	}

	if (duplicate)
		return R_MapId;







	switch (ToCreate->MapCategory)
	{

	case  NS_ENG::MAP_ASSEMBLY_TYPE::FILE_TEXTURE:{


		FileTextureDesc *TmpFileTextureDesc = dynamic_cast<FileTextureDesc*>(ToCreate);
	
		classMapList.push_back(boost::make_shared<NS_ENG::FileTexture>() );


		((FileTexture*)NS_ENG::MapAsset::classMapList.back().get())->Load(TmpFileTextureDesc);
		//classMapList.back()->Load(TmpFileTextureDesc);

		
	}
/*
	case  NS_ENG::MAP_ASSEMBLY_TYPE::ARRAY_TEXTURE: {


		ArrayTextureDesc *TmpArrayTextureDesc = dynamic_cast<ArrayTextureDesc*>(ToCreate);

		classMapList.push_back(boost::make_shared<NS_ENG::ArrayMap>() );


		((ArrayMap*)NS_ENG::MapAsset::classMapList.back().get())->Load(TmpArrayTextureDesc);
		//classMapList.back()->Load(TmpFileTextureDesc);


	}

	
	case  NS_ENG::MAP_ASSEMBLY_TYPE::SUB_ARRAY_TEXTURE:{


		SubArrayTextureDesc *TmpSubArrayTextureDesc = dynamic_cast<SubArrayTextureDesc*>(ToCreate);



		if (TmpSubArrayTextureDesc->LoadedAs == NS_ENG::MAP_ASSEMBLY_TYPE::FILE_TEXTURE)
		{



		}



		classMapList.push_back(boost::make_shared<NS_ENG::SubArrayMap>());

		//((ArrayTextureDesc*)NS_ENG::MapAsset::classMapList.back().get())->Load(TmpSubArrayTextureDesc);
		//classMapList.back()->Load(TmpFileTextureDesc);


	}
	*/

	}
	//NS_ENG::MapAsset::classMapList.back()->Base_Data = FileTextureDesc(*ToCreate);
	//FileTexture *test = static_pointer_cast<FileTexture&>( NS_ENG::MapAsset::classMapList.back()).get();
		//reinterpret_cast<FileTexture&> (NS_ENG::MapAsset::classMapList.back()).Init(reinterpret_cast<FileTextureDesc>(NS_ENG::MapAsset::classMapList.back()->Base_Data));
	//}



	



	//((FileTexture*)NS_ENG::MapAsset::classMapList.back().get())->Init(reinterpret_cast<FileTextureDesc&>(ToCreate));
	//((FileTexture*)NS_ENG::MapAsset::classMapList.back().get())->Init(test);
	


	
	//I sorely need a more durable and conscice ID, what more it should store a direct access index.
    //http://en.cppreference.com/w/cpp/types/ptrdiff_t
	NS_ENG::MapAsset::classMapList.back()->Map_MapID = (GLint)NS_ENG::MapAsset::classMapList.size();
	//NS_ENG::MapAsset::classMapList.push_back(tmp_TexMap);
	//NS_ENG::MapAsset::classMapList.back().Map_MapID = NS_ENG::MapAsset::classMapList.size();
	//NS_ENG::MapAsset::classMapList.back()->MapIter = NS_ENG::MapAsset::classMapList.size();
	//NS_ENG::MapAsset::classMapList.back()->Map_TUnit = tmp_TName;
	//NS_ENG::MapAsset::classMapList.back()->Map_Path = tmp_Path;
	//NS_ENG::map::MapIter();
	//MapIter
	//NS_ENG::map::MapIter = NS_ENG::map::classMapList.begin();
	//classMapList
	//return NS_ENG::MapAsset::classMapList.back()->Map_MapID;


	return NS_ENG::MapAsset::classMapList.back()->Map_MapID;



}


//MapAsset* MapAsset::RetriveMap(GLint idx)

t_SharedMapPtr MapAsset::RetriveMap(GLint idx)
{

	
	for (auto MapIter : NS_ENG::MapAsset::classMapList)
	{
		if (MapIter->Map_MapID == idx)
		{
			//cout << " The material: " << MatIter.matID << ":" << MatIter.name << " have allready loaded the texture " << MatIter.tPath << endl;
			//cout << " Using the GlName :" << MatIter.tUnit << endl;
			//meshy.m_Groups[u].matid = j;
			//meshy.m_Groups[u].matid = MatIter.
			//NS_ENG::Material::classMaterialList.back()- = MatIter.tUnit;
			//NS_ENG::Material::classMaterialList.back().tPath = tmp_Path;
			//MG.
			//duplicate = true;
			//break;
			//return MapIter.get();
			return MapIter;
		}
	}
	
	return NULL;


}

void  MapAsset::InitAll()
{
	for (auto MapIter : NS_ENG::MapAsset::classMapList)
	{
		MapIter->Init();
	
	}


}