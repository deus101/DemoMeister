#include "ShaderItem.h"

using namespace std;

using namespace NS_ENG;
using namespace NS_ENG::NS_SHADER;
	//typedef boost::shared_ptr< FileTexture> FileTexturePtr;

	//typedef boost::shared_ptr<const  FileTexture> FileTextureConstPtr;

	
	ShaderItem::ShaderItem(const std::string &filePath, const std::string &deployPath, TypeOfShader) : asset()
	{
		//there is no need todo this now, gather the path and the meta data first.

		//ReleaseFolder =  boost::filesystem::path(ReleaseFolder.c_str());
		AssetGlobalLocation =  boost::filesystem::path(filePath.c_str());


		boost::iostreams::stream<boost::iostreams::mapped_file_source> file_stream(AssetGlobalLocation.string());
		
		for (std::string x; std::getline(file_stream, x, '\n');)
		{
			ShaderLines.push_back(x);
		}
		
	}

	ShaderItem::ShaderItem() : asset()
	{
		
	}

	void ShaderItem::Draw()
	{



	}

	std::string ShaderItem::GetString()
	{
		return ShaderText;

	}

	std::vector<std::string> ShaderItem::GetStringLines()
	{
		return ShaderLines;

	}

	//	CompositeShader::CompositeShader(const std::string &filePath, const std::string &deployPath, TypeOfShader) : ShaderItem()

	CompositeShader::CompositeShader() : ShaderItem ()
	{
		//there is no need todo this now, gather the path and the meta data first.

		//ReleaseFolder =  boost::filesystem::path(ReleaseFolder.c_str());
		//AssetGlobalLocation = boost::filesystem::path(filePath.c_str());


		//boost::iostreams::stream<boost::iostreams::mapped_file_source> file_stream(AssetGlobalLocation.string());

		//for (std::string x; std::getline(file_stream, x, '\n');)
		//{
		//	ShaderLines.push_back(x);
		//}

	}

	BaseShaderItem::BaseShaderItem(const std::string &filePath, const std::string &deployPath, TypeOfShader type) : CompositeShader()
	{
		//there is no need todo this now, gather the path and the meta data first.

		ReleaseFolder =  boost::filesystem::path(ReleaseFolder.c_str());
		AssetGlobalLocation = boost::filesystem::path(filePath.c_str());


		//boost::iostreams::stream<boost::iostreams::mapped_file_source> file_stream(AssetGlobalLocation.string());

		//for (std::string x; std::getline(file_stream, x, '\n');)
		//{
		//	ShaderLines.push_back(x);
		//}

	}

	void BaseShaderItem::AddShader(const std::string &filePath, const std::string &deployPath, TypeOfShader type)
	{

	}