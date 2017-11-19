#pragma once


#include "map.h"

namespace NS_ENG
{

	class ArrayMap : public MapAsset 
	{  



	public:
		ArrayMap();
		//~ArrayMap();
		~ArrayMap() {};

		int Load(ArrayTextureDesc* ArrayTexMeta);

		void Draw();

		void Init();

		NS_ENG::ArrayTextureDesc BaseArrayData;

	};


	//pointless oop fuckery, remove and replace with a common function,
	//modifying the texturedesc is good enough.
	class SubArrayMap : public MapAsset
	{


	public:
		SubArrayMap() {};
		//SubArrayMap(const TextureDesc  B) { }
		


		~SubArrayMap() {};

		int Load(SubArrayTextureDesc* SubArrayTexMeta)
		{ 
			GLuint ToDelete = (GLuint)this->Map_TName;

			//glDeleteTextures(1, &ToDelete);
			
			NS_ENG::ArrayMap* tmpMapArrayPtr;
			tmpMapArrayPtr = dynamic_cast<NS_ENG::ArrayMap*>(MapAsset::RetriveMap(SubArrayTexMeta->ParentArrayID).get());

			this->Map_TName = tmpMapArrayPtr->Map_TName;
			tmpMapArrayPtr->BaseArrayData.SubItemsID.push_back(this->Map_MapID);
			this->Map_Layer = (GLint)tmpMapArrayPtr->BaseArrayData.SubItemsID.size();

			/*
			this->Map_TName = SubArrayTexMeta->ParentArray.lock()->Map_TName;
			SubArrayTexMeta->ParentArray.lock()->BaseArrayData.SubItemsID.push_back(this->Map_MapID);
			this->Map_Layer = (GLint)SubArrayTexMeta->ParentArray.lock()->BaseArrayData.SubItemsID.size();
			*/
			this->Base_Data = *SubArrayTexMeta;
			return this->Map_MapID;
		};

		void Init() {};


	};




}
