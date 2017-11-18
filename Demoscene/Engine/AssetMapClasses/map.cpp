


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
	this->Map_TName = 0;
	this->textura = NULL;
}


GLint MapAsset::LoadMaps(TextureDesc  *ToCreate, TextureDesc *ToBind = NULL) //ArrayTextureDesc *ToBind = NULL)
{

	const TextureDesc BaseTexDesc = TextureDesc(*ToBind);
	ArrayTextureDesc ArrayTexDesc = ArrayTextureDesc(BaseTexDesc);

	NS_ENG::ArrayMap *ToBindMap;


	GLint R_ArrayMapID = -1;

	//All ArrayMaps should be able to be bound at once
	//we set this so we can keep track of the TextureUnits.
	GLint CurrentArraySamplerID = 0;

	if (ToBind != NULL)
	{

		//BindTo->MapCategory = NS_ENG::MAP_ASSEMBLY_TYPE::ARRAY_TEXTURE;
		for (auto MapIter : NS_ENG::MapAsset::classMapList)
		{
			if (ToBind->MapCategory == NS_ENG::MAP_ASSEMBLY_TYPE::ARRAY_TEXTURE) 
			{
				
				CurrentArraySamplerID++;

				if( ToBind->Name.compare(MapIter->Base_Data.Name) == 0)
				{
					cout << "Found Array Texture: " << ToBind->Name << MapIter->Map_MapID << endl;

					R_ArrayMapID = MapIter->Map_MapID;

					//ToBindMapShrdPtr = MapIter;
				

					ToBindMap = (ArrayMap*)MapIter.get();

					ArrayTexDesc = ToBindMap->BaseArrayData;

					break;
				}
			}
		}

		if (R_ArrayMapID == -1)
		{

			CurrentArraySamplerID++;
			//ArrayTexDesc.
			classMapList.push_back(boost::make_shared<NS_ENG::ArrayMap>());

			((ArrayMap*)NS_ENG::MapAsset::classMapList.back().get())->Load( &ArrayTexDesc );

			NS_ENG::MapAsset::classMapList.back()->Map_MapID = 
				(GLint)NS_ENG::MapAsset::classMapList.size();


			R_ArrayMapID = NS_ENG::MapAsset::classMapList.back()->Map_MapID;
			NS_ENG::MapAsset::classMapList.back()->SamplerID = CurrentArraySamplerID;
			//ToBindMapShrdPtr = NS_ENG::MapAsset::classMapList.back();
			ToBindMap = (ArrayMap*)NS_ENG::MapAsset::classMapList.back().get();
			ToBindMap->Base_Data =  *ToBind;
		}
		

	}






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



	NS_ENG::SubArrayMap *tmpSubMap;

	switch (ToCreate->MapCategory)
	{

	case  NS_ENG::MAP_ASSEMBLY_TYPE::FILE_TEXTURE:{

		
		FileTextureDesc *TmpFileTextureDesc = dynamic_cast<FileTextureDesc*>(ToCreate);
		

		ToCreateMap = new NS_ENG::FileTexture();

		((NS_ENG::FileTexture*)ToCreateMap)->Load(TmpFileTextureDesc);

		if (ToBind == NULL)
		{

		
			classMapList.push_back(t_SharedMapPtr(ToCreateMap));

			NS_ENG::MapAsset::classMapList.back()->Map_MapID = (GLint)NS_ENG::MapAsset::classMapList.size();
		}


	}

	if (ToBind != NULL) {

		NS_ENG::SubArrayTextureDesc *tmpSubArrayTextureDesc = new NS_ENG::SubArrayTextureDesc(ToCreateMap->Base_Data);

		tmpSubArrayTextureDesc->ParentArrayID = ToBindMap->Map_MapID;
		//tmpSubArrayTextureDesc->

		classMapList.push_back((t_SharedMapPtr)ToCreateMap);
		

		NS_ENG::MapAsset::classMapList.back()->Map_MapID = (GLint)NS_ENG::MapAsset::classMapList.size();

		//Remove, I'm not into pointless singletons just some pointless OOP that wasnt finished
		NS_ENG::SubArrayMap* FUAAE;
		FUAAE = (NS_ENG::SubArrayMap*)NS_ENG::MapAsset::classMapList.back().get();

		FUAAE->Load(tmpSubArrayTextureDesc);

	}

	

	return NS_ENG::MapAsset::classMapList.back()->Map_MapID;


	}
}



//add a damn template
t_SharedMapPtr MapAsset::RetriveMap(GLint idx)
{

	
	for (auto MapIter : NS_ENG::MapAsset::classMapList)
	{
		if (MapIter->Map_MapID == idx)
		{

			return MapIter;
		}
	}
	
	return NULL;


}

//Keep this in mind, having the assets completed before shading are being compiled is important
void  MapAsset::InitAll()
{
	for (auto MapIter : NS_ENG::MapAsset::classMapList)
	{
		MapIter->Init();
	
	}


}