


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


GLint MapAsset::LoadMaps(TextureDesc  *ToCreate, TextureDesc *ToBind = NULL) //ArrayTextureDesc *ToBind = NULL)
{

	const TextureDesc BaseTexDesc = TextureDesc(*ToBind);
	ArrayTextureDesc ArrayTexDesc = ArrayTextureDesc(BaseTexDesc);

	NS_ENG::ArrayMap *ToBindMap;
	//t_SharedMapPtr ToBindMapShrdPtr;

	//t_SharedArrayMapPtr ToBindMapArrayShrdPtr;
	//t_WeakArrayMapPtr ToBindMapArrayWeakPtr;


	GLint R_ArrayMapID = -1;


	if (ToBind != NULL)
	{

		//BindTo->MapCategory = NS_ENG::MAP_ASSEMBLY_TYPE::ARRAY_TEXTURE;
		for (auto MapIter : NS_ENG::MapAsset::classMapList)
		{
			if (ToBind->MapCategory == NS_ENG::MAP_ASSEMBLY_TYPE::ARRAY_TEXTURE && ToBind->Name.compare(MapIter->Base_Data.Name) == 0)
			{
				cout << "Found Array Texture: " << ToBind->Name << MapIter->Map_MapID << endl;

				R_ArrayMapID = MapIter->Map_MapID;

				//ToBindMapShrdPtr = MapIter;
				

				ToBindMap = (ArrayMap*)MapIter.get();

				ArrayTexDesc = ToBindMap->BaseArrayData;

				break;
			}
		}

		if (R_ArrayMapID == -1)
		{
			classMapList.push_back(boost::make_shared<NS_ENG::ArrayMap>());

			((ArrayMap*)NS_ENG::MapAsset::classMapList.back().get())->Load( &ArrayTexDesc );

			NS_ENG::MapAsset::classMapList.back()->Map_MapID = (GLint)NS_ENG::MapAsset::classMapList.size();
			R_ArrayMapID = NS_ENG::MapAsset::classMapList.back()->Map_MapID;

			//ToBindMapShrdPtr = NS_ENG::MapAsset::classMapList.back();
			ToBindMap = (ArrayMap*)NS_ENG::MapAsset::classMapList.back().get();
			ToBindMap->Base_Data =  *ToBind;
		}
		
		//ToBindMap
		//ToBindMapArrayShrdPtr =  t_SharedArrayMapPtr(ToBindMapShrdPtr.get());
		//ToBindMapArrayShrdPtr = t_SharedArrayMapPtr(ToBindMap);

		//dynamic_cast<NS_ENG::SubArrayTextureDesc*>
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



	NS_ENG::MapAsset *ToCreateMap;

	t_SharedMapPtr ToCreateMap_sPtr;
	//NS_ENG::MapAsset *ToCreateMapPtr;


	NS_ENG::SubArrayMap *tmpSubMap;
	//boost::shared_ptr<NS_ENG::SubArrayMap> tmpSubMap;
	//t_SharedMapPtr tmpSubMap;

	switch (ToCreate->MapCategory)
	{

	case  NS_ENG::MAP_ASSEMBLY_TYPE::FILE_TEXTURE:{


		FileTextureDesc *TmpFileTextureDesc = dynamic_cast<FileTextureDesc*>(ToCreate);
		
		//ToCreateMap = dynamic_cast<NS_ENG::FileTexture*>(new  NS_ENG::FileTexture());
		ToCreateMap = new NS_ENG::FileTexture();

		((NS_ENG::FileTexture*)ToCreateMap)->Load(TmpFileTextureDesc);
		//ToCreateMap = (ToCreateMapPtr);
		//ToCreateMap_sPtr
		if (ToBind == NULL)
		{

			//classMapList.push_back(boost::make_shared<NS_ENG::FileTexture>(ToCreateMap) );
			classMapList.push_back(t_SharedMapPtr(ToCreateMap));

			NS_ENG::MapAsset::classMapList.back()->Map_MapID = (GLint)NS_ENG::MapAsset::classMapList.size();
		}
		//((FileTexture*)NS_ENG::MapAsset::classMapList.back().get())->Load(TmpFileTextureDesc);
		
		//classMapList.back()->Load(TmpFileTextureDesc);

	}

	if (ToBind != NULL) {

		NS_ENG::SubArrayTextureDesc *tmpSubArrayTextureDesc = new NS_ENG::SubArrayTextureDesc(ToCreateMap->Base_Data);

		tmpSubArrayTextureDesc->ParentArrayID = ToBindMap->Map_MapID;
		//tmpSubArrayTextureDesc->

		classMapList.push_back((t_SharedMapPtr)ToCreateMap);
		

		NS_ENG::MapAsset::classMapList.back()->Map_MapID = (GLint)NS_ENG::MapAsset::classMapList.size();

		NS_ENG::SubArrayMap* FUAAE;
		FUAAE = (NS_ENG::SubArrayMap*)NS_ENG::MapAsset::classMapList.back().get();

		FUAAE->Load(tmpSubArrayTextureDesc);

	}

	

	return NS_ENG::MapAsset::classMapList.back()->Map_MapID;


	}
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
			//NS_ENG::Material::ClassMaterialList.back()- = MatIter.tUnit;
			//NS_ENG::Material::ClassMaterialList.back().tPath = tmp_Path;
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