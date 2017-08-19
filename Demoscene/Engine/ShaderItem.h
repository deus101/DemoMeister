#pragma once

#include "asset.h"
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
namespace NS_ENG
{
	namespace NS_SHADER
	{

		enum TypeOfShader
		{
			BaseVertex, BaseGeometry, BaseFragment,
			IncludeVertex, IncludeGeometry, IncludeFragment,
			MaterialFetchVertex, MaterialFetchGeometry, MaterialFetchFragment,
			TextureFetchVertex, TextureFetchGeometry, TextureFetchFragment
		};

		//char Tags[3][4] = {{"#Include"}}
		//typedef boost::shared_ptr< FileTexture> FileTexturePtr;

		//typedef boost::shared_ptr<const  FileTexture> FileTextureConstPtr;
		typedef boost::shared_ptr< class ShaderItem > ShaderItemPtr;

		typedef std::deque< ShaderItemPtr > herd;


		class ShaderItem : public asset {

		public:

			ShaderItem(const std::string &filePath, const std::string &deployPath, TypeOfShader type);
			ShaderItem();

			//int Init();
			void Draw();
			~ShaderItem() {};

			std::string GetString();
			std::vector<std::string>  GetStringLines();

			std::vector<const GLchar*> veccstr;

			std::vector<std::string> ShaderLines;

			std::string ShaderText;

			boost::filesystem::path AssetGlobalLocation;
			boost::filesystem::path AssetProduction;
			boost::filesystem::path ReleaseFolder;

			GLenum ShaderType;

		};
	

	
		class CompositeShader : public ShaderItem
		{

		

		public:

			//CompositeShader(const std::string &filePath, const std::string &deployPath, TypeOfShader);
			CompositeShader();
			void AddShader(const std::string &filePath, const std::string &deployPath, TypeOfShader type);


		};

		class BaseShaderItem : public CompositeShader
		{



		public:

			BaseShaderItem(void);
			BaseShaderItem(const std::string &filePath, const std::string &deployPath, TypeOfShader type);
			void AddShader(const std::string &filePath, const std::string &deployPath, TypeOfShader type);


		};
		
	}
}
