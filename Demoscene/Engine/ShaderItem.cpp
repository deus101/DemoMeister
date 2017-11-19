#include "ShaderItem.h"
#include <boost/tokenizer.hpp>


//using namespace NS_ENG;
using namespace NS_ENG::NS_SHADER;
	//typedef boost::shared_ptr< FileTexture> FileTexturePtr;

	//typedef boost::shared_ptr<const  FileTexture> FileTextureConstPtr;
using namespace std;
using boost::tuple;

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	ShaderItem::ShaderItem() : asset()
	{

	}

	ShaderItem::ShaderItem(GLenum _ShaderType, const std::string &filePath, const std::string &deployPath, ShaderUtilityType type) : asset()
	{
		//there is no need todo this now, gather the path and the meta data first.
		this->TotalSize = 0;
		this->TotalLines = 0;
		//ReleaseFolder =  boost::filesystem::path(ReleaseFolder.c_str());
		AssetGlobalLocation =  boost::filesystem::path(filePath.c_str());
		this->IsLoaded = false;
		this->ShaderType = _ShaderType;
		this->UtilityType = type;


		
	}



	void ShaderItem::Draw()
	{



	}

	void ShaderItem::Load()
	{

		boost::iostreams::stream<boost::iostreams::mapped_file_source> file_stream(AssetGlobalLocation.string());

		for (std::string x; std::getline(file_stream, x, '\n');)
		{
			ShaderLines.push_back(x);
		}

		this->IsLoaded = true;
	}


	std::string* ShaderItem::GetString()
	{
		return &ShaderText;

	}

	std::vector<std::string> ShaderItem::GetStringLines()
	{
		return ShaderLines;

	}

	//	CompositeShader::CompositeShader(const std::string &filePath, const std::string &deployPath, TypeOfShader) : ShaderItem()


	/*
	class IncludeComponentItem : public ShaderItem
	{



	public:

		//CompositeShader(const std::string &filePath, const std::string &deployPath, TypeOfShader);
		IncludeComponentItem(std::string _Marker) : ShaderItem(), Marker(_Marker)
		{};
		IncludeComponentItem(const std::string &filePath, const std::string &deployPath, ShaderUtilityType Type, std::string _Marker) : ShaderItem(filePath, deployPath, Type), Marker(_Marker)
		{};
		//void AddShader(const std::string &filePath, const std::string &deployPath, TypeOfShader type);

		std::string Marker;
		size_t Start, Stop;
	private:
		//ShaderContainerPtr ShaderSourceComponents;

	};
	*/

	IncludeComponentItem::IncludeComponentItem(GLenum _ShaderType ,const std::string &filePath, const std::string &deployPath, ShaderUtilityType type, std::string _Marker)
		: ShaderItem(_ShaderType, filePath, deployPath, type)
	{
		
		this->TotalSize = 0;
		this->TotalLines = 0;

		this->Start = 0;
		this->Stop = 0;

		this->Marker = _Marker;

		this->IsLoaded = false;

		
	}
	//instead of loading everything, maybe just record the inputs and outputs to get requirements for the passes
	//void IncludeComponentItem::Load(ShaderLinesPtr ParentShader)
	std::string  IncludeComponentItem::Load( std::vector<string> &ParentShader)
	{
		this->Start = ParentShader.size();

		std::string ShaderSum = "";

		boost::iostreams::stream<boost::iostreams::mapped_file_source> file_stream(AssetGlobalLocation.string());
		size_t CurrentLine = 0;
		size_t CurrentSize = 0;
		size_t testS = file_stream->size();
		for (std::string x; std::getline(file_stream, x, '\n');)
		{
			CurrentLine++;
			x.append("\n");

			CurrentSize = CurrentSize + x.size();
			ParentShader.push_back(x);
			ShaderSum.append(x);
		}

		this->Stop = this->Start + CurrentLine;
		this->TotalSize = CurrentSize;
		this->TotalLines = CurrentLine;
		this->IsLoaded = true;

		return ShaderSum;
	}



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

	void CompositeShader::AddShader(ShaderItemPtr &newItem)
	{
		this->ShaderSourceComponents.push_back(newItem);

	}

	/*
	void CompositeShader::AddShader(const std::string & filePath, const std::string & deployPath, ShaderUtilityType type)
	{


	}
	*/

	BaseShaderItem::BaseShaderItem(GLenum _ShaderType , const std::string &filePath, const std::string &deployPath, ShaderUtilityType type) : CompositeShader(_ShaderType, filePath, deployPath, type)
	{
		//there is no need todo this now, gather the path and the meta data first.

		//ReleaseFolder =  boost::filesystem::path(deployPath.c_str());
		//AssetGlobalLocation = boost::filesystem::path(filePath.c_str());


		//boost::iostreams::stream<boost::iostreams::mapped_file_source> file_stream(AssetGlobalLocation.string());

		//for (std::string x; std::getline(file_stream, x, '\n');)
		//{
		//	ShaderLines.push_back(x);
		//}

	}

	//superfleus arguments here, the base would allready be qualified as something or other
	//void BaseShaderItem::AddShader(GLenum _ShaderType, const std::string &filePath, const std::string &Name, ShaderUtilityType type, std::string marker_id)

	void BaseShaderItem::AddShader(GLenum _ShaderType,  std::string filePath,  std::string Name, ShaderUtilityType type, std::string marker_id)
	{
		if (type == NS_ENG::NS_SHADER::Include)
		{
			CompositeShader::AddShader(ShaderItemPtr(new IncludeComponentItem(_ShaderType, filePath, Name, NS_ENG::NS_SHADER::Include, marker_id)));
			//this->ShaderSourceComponents.push_back(ShaderItemPtr(new IncludeComponentItem(_ShaderType, filePath, Name, NS_ENG::NS_SHADER::Include, marker_id)));
		}
		//

	}

	void BaseShaderItem::Load()
	{
		

		
		size_t CurrentLine = 0;
		size_t CurrentSize = 0;
		
		boost::iostreams::stream<boost::iostreams::mapped_file_source> file_stream(AssetGlobalLocation.string());

		size_t TestSize1 = file_stream->size();
		for (std::string x; std::getline(file_stream, x, '\n');)
		{
			CurrentLine++;
	


			if (x.front() == '#')
			{

				boost::char_separator<char> sep(" ");
				

				

				boost::tokenizer< boost::char_separator<char> > tokens(x, sep);
				//= "";
				std::string TagValue = "";
				//std::list< struct PointLightItem>::iterator
				
				//tokenizer::const_iterator()
				boost::tokenizer< boost::char_separator<char>>::iterator tok_it = tokens.begin();

				std::string Tag(tok_it->data());
				bool LineMerge = false;

				//if (Tag.compare("#include") == 0 || Tag.compare("#Material"))
				if (Tag.compare("#include") == 0 )
				{



					++tok_it;
					TagValue = string((tok_it)->data());
					TagValue.pop_back();
				
					std::string LocatedMarker = Tag + " " + TagValue;

				//for (size_t idx = 0; idx < this->ShaderSourceComponents.size(), idx++;)


				for(std::list<ShaderItemPtr>::iterator ip = this->ShaderSourceComponents.begin(); ip != this->ShaderSourceComponents.end(); ++ip)
				{
					//IncludeComponentItem *tmp_IncludeShader = dynamic_cast<IncludeComponentItem*>(this->ShaderSourceComponents.at(idx).get());

					IncludeComponentItem *tmp_IncludeShader = dynamic_cast<IncludeComponentItem*>(ip->get());

					//this->ShaderSourceComponents.at(idx)->
					//if (tmp_IncludeShader != NULL && tmp_IncludeShader->Marker.compare(Tag + " " + TagValue) == 0)
					if (tmp_IncludeShader != NULL )
					{

						
						int EqualValue = tmp_IncludeShader->Marker.compare(LocatedMarker);
						
						if(EqualValue == 0)
						{
							this->ShaderText.append(	tmp_IncludeShader->Load(this->ShaderLines));


						

						this->TotalSize = this->TotalSize + tmp_IncludeShader->GetSize();
						this->TotalLines = this->TotalLines + tmp_IncludeShader->GetLines();

						LineMerge = true;
						continue;
						}


					}

				}


				}

				if (LineMerge == true)
				{
					CurrentLine--;
					continue;

				}
			}

			x.append("\n");

			
			CurrentSize = CurrentSize + x.size();
			//tempCodePtr->push_back(x);
			this->ShaderLines.push_back(x);
			this->ShaderText.append(x);

		}

		this->ShaderText.push_back('\0');
		this->TotalSize = this->TotalSize + CurrentSize;
		this->TotalLines = this->TotalLines + CurrentLine;
		this->IsLoaded = true;


	}