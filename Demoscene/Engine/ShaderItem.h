#pragma once

#include "asset.h"

namespace NS_ENG
{

	//typedef boost::shared_ptr< FileTexture> FileTexturePtr;

	//typedef boost::shared_ptr<const  FileTexture> FileTextureConstPtr;

	class ShaderItem : public asset {

	public:

		ShaderItem();

		
		//int Init();
		void Draw();
		~ShaderItem() {};

		std::string Shader_Path;



	};




}