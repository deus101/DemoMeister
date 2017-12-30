#pragma once

#include "asset.h"

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include "boost/tuple/tuple.hpp"
//#include <typeinfo> 

namespace NS_ENG
{
	namespace NS_SHADER
	{

		
		/*
		enum TypeOfShader
		{
			BaseVertex, BaseGeometry, BaseFragment,
			IncludeVertex, IncludeGeometry, IncludeFragment,
			MaterialFetchVertex, MaterialFetchGeometry, MaterialFetchFragment,
			TextureFetchVertex, TextureFetchGeometry, TextureFetchFragment
		};
		*/


		/*
		enum ShaderUtilityType
		{
			BaseVertex, IncludeVertex, MaterialFetchVertex, TextureFetchVertex,
			BaseGeometry, IncludeGeometry, MaterialFetchGeometry, TextureFetchGeometry,
			BaseFragment, IncludeFragment, MaterialFetchFragment, TextureFetchFragment,
		};
		

		enum ShaderUtilityType
		{
			Base, Include, MaterialFetch, TextureFetch,

		};
		*/
		enum ShaderUtilityType
		{
			Base, Include,

		};
	
		//They are within a name space, still.

		//these should go to their respective classes

		typedef boost::shared_ptr< class ShaderItem > ShaderItemPtr;

		typedef boost::shared_ptr< class BaseShaderItem > BaseShaderItemPtr;
		typedef boost::shared_ptr< class IncludeComponentItem > IncludeComponentItemPtr;

		
		typedef boost::tuple< std::string, std::string, int, GLint, GLenum> tup_InnOut;
		typedef boost::tuple< std::string, std::string, int, GLint, GLenum> tup_Uniform;
		typedef std::list<NS_ENG::NS_SHADER::tup_Uniform> UniformList;
		//typedef std::list<NS_ENG::NS_SHADER::tup_Uniform*> UniformList_Ptr;

		//typedef std::list< ShaderItem* > Nodes;
		typedef std::list< ShaderItemPtr > ShaderContainerPtr;

		//const std::type_info *Test[] = { &typeid(BaseShaderItem), &typeid(IncludeComponentItem) };

		class ShaderItem : public asset {

		public:
			ShaderItem();
			ShaderItem(GLenum _ShaderType ,const std::string &filePath, const std::string &deployPath, ShaderUtilityType type);
			

			void Load();
			
			void Init() {};
			void Save();
			void Deploy();


			void Draw();
			~ShaderItem() {};



			void RetriveCharArray(GLchar** SharerChar);

			std::string *GetString();
			std::vector<std::string>  GetStringLines();

			std::vector<std::string*> GetCopyShader();

			void CopyShaderPerLine(std::string*);

			bool StartExpressionList(std::string, std::string,int Start);
			bool AddTuple(std::string);
			bool StopExpressionList(std::string,int Stop);
			size_t GetSize() { return TotalSize; };
			size_t GetLines() { return TotalLines; };

			std::string path;
		//private:
		protected:
			size_t TotalSize;
			size_t TotalLines;

			bool IsLoaded;

			std::vector<const GLchar*> veccstr;
		
			std::vector<std::string> ShaderLines;

			std::vector<std::string*> CopyShader;

			std::string ShaderText;

			boost::filesystem::path AssetGlobalLocation;
			boost::filesystem::path AssetProduction;
			boost::filesystem::path ReleaseFolder;

			GLenum ShaderType;
			ShaderUtilityType UtilityType;

			NS_ENG::NS_SHADER::UniformList m_Uniforms;
			//CurrShader->RetriveUniforms(&this->m_SamplerUniforms);



		};
	
		class IncludeComponentItem : public ShaderItem
		{



		public:

			//CompositeShader(const std::string &filePath, const std::string &deployPath, TypeOfShader);
			IncludeComponentItem( std::string _Marker) : ShaderItem(), Marker(_Marker)
			{};
			//IncludeComponentItem(GLenum _ShaderType, const std::string &filePath, const std::string &deployPath, ShaderUtilityType Type, std::string _Marker) : ShaderItem(_ShaderType, filePath, deployPath, Type), Marker(_Marker){};
			IncludeComponentItem(GLenum _ShaderType, const std::string &filePath, const std::string &deployPath, ShaderUtilityType Type, std::string _Marker);
			

			std::string Load(std::vector<std::string> &ParentShader);

			std::string Marker;
			size_t Start, Stop;
		private:
			//ShaderContainerPtr ShaderSourceComponents;

		};


	
		class CompositeShader : public ShaderItem
		{

		

		public:

			//CompositeShader(const std::string &filePath, const std::string &deployPath, TypeOfShader);
			CompositeShader();
			CompositeShader(GLenum _ShaderType , const std::string &filePath, const std::string &deployPath, ShaderUtilityType Type)
				: ShaderItem(_ShaderType, filePath, deployPath, Type) { };
			

			//void AddShader(const std::string &filePath, const std::string &deployPath, TypeOfShader type);
			void AddShader(ShaderItemPtr &newItem);
			
		//private:
		protected:

			ShaderContainerPtr ShaderSourceComponents;

		};


		class BaseShaderItem : public CompositeShader
		{



		public:

			
			//std::vector<tup_Uniform> Uniforms;

			BaseShaderItem(void);
			BaseShaderItem(GLenum _ShaderType ,const std::string &filePath, const std::string &deployPath, ShaderUtilityType type);
			//void AddShader(GLenum _ShaderType, const std::string &filePath, const std::string &Name, ShaderUtilityType type, std::string marker_id);
			void AddShader(GLenum _ShaderType , std::string filePath,  std::string Name, ShaderUtilityType type,std::string marker_id);

			void Load();
			//void RetriveUniforms(UniformList_Ptr);
			void RetriveUniforms(UniformList * Current);
		private:
			//Tuple_List Vec_Markers;
			//std::vector<std::string> ShaderLines;

		};
		
	}
}
