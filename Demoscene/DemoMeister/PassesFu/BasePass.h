#pragma once

#include <DemoMeister\world.h>


class BasePass
{
public:
	BasePass();

	int load(const std::string &filename);
	void save();
	void deploy();

	void SetName(std::string arg) { Name = arg; }


	std::string GetName() { return Name; }

	/*
	NS_ENG::NS_SHADER::BaseShaderItemPtr GetShaderComposition(GLenum Type) {
		if (hasVertexShader && Type == GL_VERTEX_SHADER)
			return VertexCode;
		if (hasGeometryShader && Type == GL_GEOMETRY_SHADER)
			return GeometryCode;
		if (hasFragmentShader  && Type == GL_FRAGMENT_SHADER)
			return FragmentCode;

	}
	*/

private:
	tinyxml2::XMLDocument xml_PassRepo;

	std::string Name;
	boost::filesystem::path path_PassDeffinition;



	~BasePass();
};

