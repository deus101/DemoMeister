#pragma once
//#ifndef MAP_HPP
//#define MAP_HPP


//#include "asset.h"
#include "../asset.h"

//#include "../ShaderFu/GeomPacket.h"
//
//#include "../Libs/FreeImage.h"
#include "../../FreeImage.h"
#include "../../util.h"





namespace NS_ENG
{
	typedef enum MAP_TYPE {
		UNDEFINED,
		FILE_TEXTURE,
		FBO_TEXTURE,
		DATA_TEXTURE,
	} e_CategoryType;



	struct TextureDesc
	{
		e_CategoryType MapCategory;
		GLenum Target;
		std::string Name;
		std::string Origin;
		std::string Description;
		GLenum format;
		GLenum type;
		GLint internalFormat;
		GLint  wrap;
		GLint  filter;
		unsigned int w;
		unsigned int h;

	public:
		TextureDesc()
			:MapCategory(MAP_TYPE::UNDEFINED)
			, Target(GL_TEXTURE_2D)
			, Name("")
			, Origin("")
			, Description("")
			, format(0)
			, type(0)
			, internalFormat(0)
			, wrap(GL_CLAMP_TO_EDGE)
			, filter(GL_NEAREST)
			, w(0)
			, h(0)
		{
		}
		virtual ~TextureDesc() {}
	};

	//typedef boost::shared_ptr< struct TextureDesc > TextureDescPtr;
	//typedef boost::shared_ptr<const struct TextureDesc> TextureDescConstPtr;



	struct FileTextureDesc : public TextureDesc
	{
		std::string Map_Path;
	public:
		FileTextureDesc() : TextureDesc()
			, Map_Path("")
		{
			MapCategory = MAP_TYPE::FILE_TEXTURE;
		}

		FileTextureDesc(const TextureDesc & B)
			: TextureDesc(B)
		{
			MapCategory = MAP_TYPE::FILE_TEXTURE;
		}
		

	};


	//typedef boost::shared_ptr< struct FileTextureDesc > FileTextureDescPtr;
	//typedef boost::shared_ptr<const struct FileTextureDesc> FileTextureDescConstPtr;

	struct FboTextureDesc : public TextureDesc
	{

		GLint FBO;
		GLenum Extension;
	public:
		FboTextureDesc()
			: TextureDesc()
			, FBO(0)
			, Extension(0)
		{}

		FboTextureDesc(const TextureDesc & B)
			: TextureDesc(B)
			,FBO(0)
			, Extension(0)
		{
		}

	};

	struct DataTextureDesc : public TextureDesc
	{
	public:
		DataTextureDesc()
			: TextureDesc()
		{

		}

		DataTextureDesc(const TextureDesc & B)
			: TextureDesc(B)
		{
		}

		//GLint  wrap;
		//GLint  filter;
		//string Map_Path;

	};


	//typedef boost::shared_ptr< class MapAsset& > MapAssetPtr;
	//typedef boost::shared_ptr<const class MapAsset& > MapAssetConstPtr;
	
	
	//typedef boost::shared_ptr<const  MapAsset> MapAssetConstPtr;

	class MapAsset : public asset
	{


	private:
		//list <MapAsset>::iterator MapIter;
		std::list <boost::shared_ptr<  MapAsset >>::iterator MapIter;
	public:
		//static list <MapAsset*> classMapList;
		static std::list<boost::shared_ptr<  MapAsset >> classMapList;

		//typedef enum MAP_TYPE;

		//https://stackoverflow.com/questions/3106206/template-object-as-static-member-of-the-template-class
		public:

		MapAsset();
		~MapAsset() {};
		//static GLint LoadMaps(const char *param);
		static GLint LoadMaps( TextureDesc *ToCreate);
		static MapAsset* RetriveMap(GLint MapID);

		//static MapAsset* RetriveMap(string origin, string name);


		void Draw();


		//this should be called AssetID
		GLint Map_MapID;
		//char path[80];
		//actually the proper place
		
		//Texture names are unsigned integers.The value zero is reserved to represent the default texture for each texture target.
		GLint Map_TName;
		GLint Map_TUnit;


		GLint Map_Layer;
		//protected:

		TextureDesc Base_Data;




	//GL_NEAREST or point filtering.
	//Something something 
	//NS_VEC::VEC2 

	//There should be more arguments depending on what kind of map it is
		//for now keep it simple...also should Load* ve a virtual function toed to  asset?
		//I could use draw for that matter...AAAH BETTER GPUIFY!
		//static void LoadMaps(const char *param);
	};
	//typedef boost::shared_ptr<  MapAsset > MapAssetPtr;
}

//#endif