#pragma once
//#include "C:\Users\Deus\Source\Repos\DemoEngine\Demoscene\Engine\AssetMapClasses\map.h"

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

	class SubArrayMap : public MapAsset
	{


	public:
		SubArrayMap() {};
		//SubArrayMap(const TextureDesc  B) { }
		


		~SubArrayMap() {};

		int Load(SubArrayTextureDesc* SubArrayTexMeta)
		{ 
			SubArrayTexMeta->ParentArray.lock()->BaseArrayData.SubItemsID.push_back(this->Map_MapID);
			this->Map_Layer = (GLint)SubArrayTexMeta->ParentArray.lock()->BaseArrayData.SubItemsID.size();
		
		};

		void Init() { };


	};




}
