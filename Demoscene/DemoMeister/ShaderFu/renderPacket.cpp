#include "renderPacket.h"


//#include "../util.h"
//#include "../Engine/asset.h"
//using namespace NS_ENG;
using namespace NS_VEC;
using namespace NS_EFF;

#include "../Rendrer/context.h"

#include <boost/make_shared.hpp>
#include <boost/tuple/tuple.hpp>
//I should go back to using context class/objects
//renderPacket::renderPacket(const NS_REND::context &aContext)
renderPacket::renderPacket()
{

	//typedef boost::shared_ptr< struct EffectStage > EffectStagePtr;
	//typedef boost::shared_ptr<const struct EffectStage> EffectStageConstPtr;
	EffectType = "";
	EffectName = "";

	PassName = "";
	PassIndex = 0;
	this->PassLinked = false;
	ParsedVertexCode = NULL;
	ParsedGeometryCode = NULL;
	ParsedFragmentCode = NULL;
	m_shaderProg = 0;

	m_StageParameters.iStageValue = 0;

	m_StageParamPtr = boost::make_shared<EffectStage>(m_StageParameters);

	m_StageParamConstPtr = boost::const_pointer_cast<const  EffectStage>(m_StageParamPtr);

}
renderPacket::~renderPacket()
{
	//m_StageParamPtr.
	//delete &m_StageParamPtr;
	//NS_ENG::asset::CurrentStage.
	//delete &this->m_StageParameters;
	//NS_ENG::asset::SetCurrentStage(NULL);
	//NS_ENG::asset::SetCurrentStage(m_StageParamConstPtr);
	//this->m_StageParamConstPtr.unique();
	//this->m_StageParamConstPtr.owner_before()
	//delete m_StageParamPtr;
	//delete this->m_StageParameters

}
bool renderPacket::Init()
{
	//I want to let my packets keep track of the samplers it needs
	//opprette bufferne her?
	m_shaderProg = glCreateProgram();

	//m_shaderProg = context.getProgram();
	if (m_shaderProg == 0) {
		fprintf(stderr, "Error creating shader program\n");
		return false;
	}
	//ParsedVertexCode, ParsedGeometryCode, ParsedFragmentCode;
	if (this->PassLinked)
	{
		sp_PassItemnator tmp_SP_Pass;
		tmp_SP_Pass = TheDisc->RetrivePass(this->PassIndex);

		if (tmp_SP_Pass->hasVertexShader == true)
			this->ParsedVertexCode = tmp_SP_Pass->GetShaderComposition(GL_VERTEX_SHADER);
		if (tmp_SP_Pass->hasGeometryShader == true)
			this->ParsedGeometryCode = tmp_SP_Pass->GetShaderComposition(GL_GEOMETRY_SHADER);
		if (tmp_SP_Pass->hasFragmentShader == true)
			this->ParsedFragmentCode = tmp_SP_Pass->GetShaderComposition(GL_FRAGMENT_SHADER);

	}


	return true;

}


bool renderPacket::LoadShader(GLenum ShaderType, const char *fileName)
{

	GLint success;
	GLint shaderLength = 0;
	//NS_ENG::NS_SHADER::ShaderItemPtr CurrShader;
	NS_ENG::NS_SHADER::BaseShaderItemPtr CurrShader;
	ShaderObj curr;

	curr.ShaderType = ShaderType;
	m_shaderObjList.push_back(curr);

	const GLchar *glslStringPtr[1];
	const GLchar *glslArray;

	GLchar *shaderText = NULL;

	FILE *fp;

	bool inMemory = false;

	if (ShaderType == GL_VERTEX_SHADER && this->ParsedVertexCode != NULL)
	{
		CurrShader = this->ParsedVertexCode;
		inMemory = true;
	}
	if (ShaderType == GL_GEOMETRY_SHADER && this->ParsedGeometryCode != NULL)
	{
		CurrShader = this->ParsedGeometryCode;
		inMemory = true;
	}
	if (ShaderType == GL_FRAGMENT_SHADER && this->ParsedFragmentCode != NULL)
	{
		CurrShader = this->ParsedFragmentCode;
		inMemory = true;
	}



	if (inMemory == false)
	{
		fp = fopen(fileName, "r");
		if (fp != NULL)
		{
			std::cout << "Loading: " << fileName << std::endl;
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

		glslStringPtr[0] = shaderText;


	}
	else
	{
		//CurrShader->
		CurrShader->Load();
		//m_SamplerUniforms;

	   //CurrShader->RetriveUniforms(&this->m_SamplerUniforms);
		CurrShader->RetriveUniforms(&this->m_shaderObjList.back().so_Uniforms);

		//shaderText = (GLchar *)malloc(CurrShader->GetSize);
		glslArray = (const GLchar *)CurrShader->GetString()->c_str();
		glslStringPtr[0] = glslArray;
		//return true;
		//CurrShader->na
		std::cout << "Loading: " << CurrShader->path << std::endl;
	}
	//tup_Uniform
	NS_ENG::NS_SHADER::UniformList::iterator itCurrent;
	NS_ENG::NS_SHADER::UniformList::iterator itAll;
	//m_shaderObjList.back().so_Uniforms
	for (
		itCurrent = m_shaderObjList.back().so_Uniforms.begin();
		itCurrent != m_shaderObjList.back().so_Uniforms.end();
		itCurrent++)
	{
		std::string curArg1 = boost::tuples::get<0>(*itCurrent);
		std::string curArg2 = boost::tuples::get<1>(*itCurrent);

		bool isDupe = false;

		for (
			itAll = this->m_SamplerUniforms.begin();
			itAll != this->m_SamplerUniforms.end();
			itAll++)
		{
			std::string allArg1 = boost::tuples::get<0>(*itAll);
			std::string allArg2 = boost::tuples::get<1>(*itAll);

			if (curArg1.compare(allArg1) == 0 && curArg2.compare(allArg2) == 0)
			{
				isDupe = true;
				break;
			}




		}

		if (isDupe)
			continue;

		this->m_SamplerUniforms.push_back(*itCurrent);

	}

	//CurrShader->RetriveUniforms(&this->m_shaderObjList.back().so_Uniforms
	//this->m_SamplerUniforms.

	m_shaderObjList.back().ShaderObject = glCreateShader(m_shaderObjList.back().ShaderType);
	//GLuint ShaderObj = glCreateShader(ShaderType);

	//m_shaderObjList.push_back(ShaderObj);

	//glShaderSource()
	glShaderSource(m_shaderObjList.back().ShaderObject, 1, glslStringPtr, NULL);


	glCompileShader(m_shaderObjList.back().ShaderObject);

	glGetShaderiv(m_shaderObjList.back().ShaderObject, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[2048];
		glGetShaderInfoLog(m_shaderObjList.back().ShaderObject, 2048, NULL, infoLog);
		fprintf(stderr, "epic ffffail in: %s #%d !\n", CurrShader->path.c_str(), m_shaderObjList.back().ShaderObject);
		fprintf(stderr, "%s\n", infoLog);
		Sleep(10000);
		return false;
	}

	glAttachShader(m_shaderProg, m_shaderObjList.back().ShaderObject);

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
		Sleep(10000);
		return false;
	}


	glValidateProgram(m_shaderProg);
	glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[2048];
		glGetProgramInfoLog(m_shaderProg, 2048, NULL, infoLog);

		fprintf(stderr, "%s\n", infoLog);
		Sleep(10000);
		return false;
	}
	std::cout << "ShaderObject! : " << m_shaderProg << std::endl;
	//glUseProgram(m_shaderProg);

	renderPacket::ParseUniformList();

	return true;

}


void renderPacket::Enable()
{
	NS_ENG::asset::SetCurrentStage(m_StageParamConstPtr);
	glUseProgram(m_shaderProg);
}


//void NS_EFF::renderPacket::SetName(std::string arg)
void renderPacket::SetName(std::string arg)
{
	EffectName = arg;
}
//std::string NS_EFF::renderPacket::GetName()
std::string renderPacket::GetName()
{
	return EffectName;
}

//Gonna go lazy at the moment
void renderPacket::SetType(std::string arg)
{
	EffectType = arg;
}

std::string renderPacket::GetType()
{
	return EffectType;
}

void renderPacket::SetStageValue(int val)
{
	m_StageParameters.iStageValue = val;
}

int renderPacket::GetStageValue()
{
	return m_StageParameters.iStageValue;
}

void renderPacket::SetPassIndex(std::size_t val)
{
	this->PassIndex = val;
}

void renderPacket::SetPassName(std::string arg)
{

	this->PassName = arg;
}

bool NS_EFF::renderPacket::PacketPassHandshake()
{
	this->PassLinked = false;
	size_t tmp_PIDX;
	tmp_PIDX = TheDisc->RetrivePassID("", this->PassName);

	std::string tmp_PName;
	tmp_PName = TheDisc->RetrivePass(tmp_PIDX)->GetName();

	if (this->PassName.compare(tmp_PName) == 0)
	{
		this->PassIndex = tmp_PIDX;
		this->PassLinked = true;
	}


	return this->PassLinked;


}


GLint renderPacket::GetUniformLocation(const char* pUniformName)
{
	GLuint Location = glGetUniformLocation(m_shaderProg, pUniformName);

	if (Location == INVALID_UNIFORM_LOCATION) {
		fprintf(stderr, "\n		|-(Warning! Unable to get the location of uniform '%s' )", pUniformName);
	}

	return Location;
}

bool renderPacket::ParseUniformList()
{

	NS_ENG::NS_SHADER::UniformList::iterator itAll;
	//m_shaderObjList.back().so_Uniforms
	std::fprintf(stdout, "The EffectPacket %s For  : the pass %s \n Has these uniforms: \n", this->GetName().c_str(), this->PassName.c_str());
	bool success = true;

	for (
		itAll = this->m_SamplerUniforms.begin();
		itAll != this->m_SamplerUniforms.end();
		itAll++)
	{
		std::string allArg1 = boost::tuples::get<0>(*itAll);
		std::string allArg2 = boost::tuples::get<1>(*itAll);
		std::fprintf(stdout, "	%s : %s  Location=",  allArg1.c_str(), allArg2.c_str());
		int UniLoc = GetUniformLocation(allArg2.c_str());

		boost::tuples::get<4>(*itAll) = UniLoc;


		std::fprintf(stdout, "[%i] \n", boost::tuples::get<4>(*itAll));
	}
	std::fprintf(stdout, "count: [%i] \n END\n \n", this->m_SamplerUniforms.size());
	return success;
}

GLint renderPacket::GetProgramParam(GLint param)
{
	GLint ret;
	glGetProgramiv(m_shaderProg, param, &ret);
	return ret;
}
