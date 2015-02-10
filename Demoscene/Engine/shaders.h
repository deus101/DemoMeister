#ifndef SHADERS_HPP
#define SHADERS_HPP

#include "world.h"
//#include "vsGLInfoLib.h"

class Shader_Progs
{
public:
	GLint ShaderObject;
	GLint VertexShader;
	GLint FragmentShader;
	//GLint GeometryShader;
	GLint POSLoc;
	GLint UVLoc;
	GLint NORMLoc;
	Shader_Progs();

	void CompileProgram(void);


	GLchar  *LoadShaderText(const char *fileName);

	void Sleep(unsigned int );




};












#endif
