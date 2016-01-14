#include "renderPacket.h"

#include "../util.h"
#include "../Engine/asset.h"

//using namespace NS_ENG;
using namespace NS_VEC;
using namespace NS_EFF;

//dropper dette for �yeblikket
//renderPacket::renderPacket(const NS_REND::context &aContext)
renderPacket::renderPacket()
{
 //gi den shaderne
	//m_shaderProg = aContext.Program;

	m_shaderProg = 0;

}
renderPacket::~renderPacket()
{

}
bool renderPacket::Init()
{

	//opprette bufferne her?
	m_shaderProg = glCreateProgram();

	//m_shaderProg = context.getProgram();
	if (m_shaderProg == 0) {
		fprintf(stderr, "Error creating shader program\n");
		return false;
	}
	return true;

}
/*
//ehm....Jo vent jeg satt den der fordi m_shaderProg var der men n� har jo model klassen den informasjonen.
//faen her skal jo asset v�re drit I � legge til model, dette er jo Asset som jeg tror model er ment � arve fra.
void renderPacket::Draw(NS_ENG::model *o, const M3DMatrix44f mMat)
{

	//gl::BindVertexArray(vao_model);
	//Sett opp egne programmer
	gl::UseProgram(m_shaderProg);
	GLint ModelLoc = gl::GetUniformLocation(m_shaderProg, "M");
	if (ModelLoc != -1)
	{
		//cout << "In Model found uniform for Model Matrix" << endl;
		//gl::UniformMatrix4fv(ModelLoc, 1, gl::FALSE_, this->Model);
		//"this" i rendrenren henter model matrisen
	}

	GLint DifLoc = gl::GetUniformLocation(m_shaderProg, "Diffuse");
	GLint AmbLoc = gl::GetUniformLocation(m_shaderProg, "Ambiant");
	GLint SpecLoc = gl::GetUniformLocation(m_shaderProg, "Specular");
	GLint ShiLoc = gl::GetUniformLocation(m_shaderProg, "Shininess");

	if (ModelLoc != -1)
	{
		//cout << "In Model found uniform for Model Matrix" << endl;
		//gl::UniformMatrix4fv(AmbLoc, 1, gl::TRUE_, this->  );
		//"this" i rendrenren henter model matrisen
	}



	//gl::PolygonMode(gl::GL_FRONT_AND_BACK, gl::GL_FILL);

	for (unsigned int i = 0; i < o->Sort_Groups.size(); i++)
	{


		gl::BindVertexArray(o->Sort_Groups[i].vao);

		gl::Uniform4fv(DifLoc, 1, (const GLfloat *)o->palette.m_Materials[o->meshy.m_Groups[i].matid].diff);
		gl::Uniform4fv(AmbLoc, 1, (const GLfloat *)o->palette.m_Materials[o->meshy.m_Groups[i].matid].amb);
		gl::Uniform4fv(SpecLoc, 1, (const GLfloat *)o->palette.m_Materials[o->meshy.m_Groups[i].matid].spec);
		gl::Uniform1f(ShiLoc, o->palette.m_Materials[o->meshy.m_Groups[i].matid].shiny);

		gl::DrawElements(gl::TRIANGLES, o->Sort_Groups[i].IBO.size(), gl::UNSIGNED_SHORT, (void*)0);
	}


}
*/

bool renderPacket::LoadShader(GLenum ShaderType, const char *fileName)
{
	
	std::cout << fileName << std::endl;
	const GLchar *glslStringPtr[1];
	GLint success;


	GLchar *shaderText = NULL;
	GLint shaderLength = 0;
	FILE *fp;


	fp = fopen(fileName, "r");
	if (fp != NULL)
	{
		while (fgetc(fp) != EOF)
		{
			shaderLength++;
		}
		rewind(fp);
		shaderText = (GLchar *)malloc(shaderLength + 1);
		if (shaderText != NULL)
		{
			fread(shaderText, 1, shaderLength, fp);
		}
		shaderText[shaderLength] = '\0';
		fclose(fp);
	}


	if (shaderText == NULL)
		return false;

	GLuint ShaderObj = glCreateShader(ShaderType);

	m_shaderObjList.push_back(ShaderObj);

	glslStringPtr[0] = shaderText;

	glShaderSource(ShaderObj, 1, glslStringPtr, NULL);


	glCompileShader(ShaderObj);

	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[2048];
		glGetShaderInfoLog(ShaderObj, 2048, NULL, infoLog);
		fprintf(stderr, "epic Vertex #%d ffffail!\n", ShaderObj);
		fprintf(stderr, "%s\n", infoLog);
		_sleep(10000);
		return false;
	}

	glAttachShader(m_shaderProg, ShaderObj);

	return true;
}

bool renderPacket::Finalize()
{
	glLinkProgram(m_shaderProg);

	GLint success;

	glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[2048];
		glGetProgramInfoLog(m_shaderProg, 2048, NULL, infoLog);

		fprintf(stderr, "%s\n", infoLog);
		_sleep(10000);
		return false;
	}


	glValidateProgram(m_shaderProg);
	glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[2048];
		glGetProgramInfoLog(m_shaderProg, 2048, NULL, infoLog);

		fprintf(stderr, "%s\n", infoLog);
		_sleep(10000);
		return false;
	}
	//std::cout << "ShaderObject! : " << m_shaderProg << endl;
	return true;

}


void renderPacket::Enable()
{
	glUseProgram(m_shaderProg);
}


GLint renderPacket::GetUniformLocation(const char* pUniformName)
{
	GLuint Location = glGetUniformLocation(m_shaderProg, pUniformName);

	if (Location == INVALID_UNIFORM_LOCATION) {
		fprintf(stderr, "Warning! Unable to get the location of uniform '%s'\n", pUniformName);
	}

	return Location;
}

GLint renderPacket::GetProgramParam(GLint param)
{
	GLint ret;
	glGetProgramiv(m_shaderProg, param, &ret);
	return ret;
}