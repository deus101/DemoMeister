#include "aoPacket.h"
#include <vector>

#include <random> 
#include <string>
using namespace NS_EFF;


aoPacket::aoPacket()
{
	//REGISTER_CLASS(DeferredPipeMother);
}


aoPacket::~aoPacket()
{
}


bool aoPacket::Init() {

	if (!renderPacket::Init()) {
		return false;
	}

	if (!LoadShader(GL_VERTEX_SHADER, "shaders/IdentityPacket.vert")) {
		return false;
	}


	if (!LoadShader(GL_FRAGMENT_SHADER, "shaders/ao_Pass_Frag.glsl")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}
	//Im just using this for ID matrise 
	m_WVPLocation = GetUniformLocation("gWVP");

	//m_ProjectionLocation = GetUniformLocation("commonProjectionMatrix");
	

	 m_ProjectionLocation = GetUniformLocation("commonProjectionMatrix");
	 m_WorldMatrixLocation = GetUniformLocation("commonWorldMatrix");
	 m_ViewLocation = GetUniformLocation("commonViewMatrix");
	//m_KernelLocation = GetUniformLocation("gKernel[0]");
	
	//gTexNoise
	

	m_posTextureUnitLocation = GetUniformLocation("gbPositionMap");

	m_normalTextureUnitLocation = GetUniformLocation("gbNormalMap");

	m_NoiseLocation = GetUniformLocation("aoTexNoise");


	m_screenSizeLocation = GetUniformLocation("gScreenSize");


	//We dont need this do we?
	//m_depthTextureUnitLocation = GetUniformLocation("gDepthMap");


	//m_sampleRadLocation = GetUniformLocation("gSampleRad");


	//trenger ikke view ray
	//m_aspectRatioLocation = GetUniformLocation("gAspectRatio");
	//m_tanHalfFOVLocation = GetUniformLocation("gTanHalfFOV");

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_KernelLocation == INVALID_UNIFORM_LOCATION ||
		m_posTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
		m_normalTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
		m_NoiseLocation == INVALID_UNIFORM_LOCATION  ) {
			return false;
	}




	return true;


}


void aoPacket::InitKernel()
{
	NS_VEC::VEC3 kernel[KERNEL_SIZE];
	//std::vector<NS_VEC::VEC3> kernel;
	for( unsigned int i  = 0; i < KERNEL_SIZE; i++)
	{
		float scale = (float)i / (float)(KERNEL_SIZE);
		NS_VEC::VEC3 v;

		v.X = 2.0f *(float)rand() / RAND_MAX - 1.0f;
		v.Y = 2.0f *(float)rand() / RAND_MAX - 1.0f;
		v.Z = 0.0f *(float)rand() / RAND_MAX + 1.0f;

		v *= (0.1f + 0.9f * scale * scale);

		//kernel.push_back(v);
		kernel[i] = v;
	}

	//glUniform3fv(m_KernelLocation, KERNEL_SIZE, (const GLfloat*)&kernel[0]);
	for (GLuint i = 0; i < 64; ++i) {
		glUniform3fv(GetUniformLocation(std::string("gKernel[" + std::to_string(i) + "]").c_str()), 1, (const GLfloat*)&kernel[i]);

	}
}

void aoPacket::SetNoiseTextureUnit(GLenum TextureUnit)
{
	int SamplerID = TextureUnit - GL_TEXTURE0;
	glUniform1i(m_NoiseLocation, SamplerID);
	//glUniform1i(m_NoiseLocation, m_NoiseLocation);
	this->m_StageParamPtr->TextureUnits[TypeOfTexture::AOBuffer_NOISE] = TextureUnit;
	std::cout << "AO_Packet Noise Uniform Location is " << m_NoiseLocation <<
		" Textureunit: " << TextureUnit << " SamplerID: " << SamplerID << std::endl;
}

void aoPacket::InitNoise()
{	//bah no not here ffs
	std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0);
	std::default_random_engine generator;


	std::vector<NS_VEC::VEC3> ssaoNoise;
	for (GLuint i = 0; i < 16; i++)
	{
		NS_VEC::VEC3 noise(randomFloats(generator) * 2.0f - 1.0f, randomFloats(generator) * 2.0f - 1.0f, 0.0f); // rotate around z-axis (in tangent space)
		ssaoNoise.push_back(noise);
	}
	glGenTextures(1, &NoiseTexure);
	glBindTexture(GL_TEXTURE_2D, NoiseTexure);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//this->SetNoiseTextureUnit(NoiseTexure);
	//this->SetNoiseTextureUnit(GL_TEXTURE0+15u);
	this->SetNoiseTextureUnit(GL_TEXTURE7);
}





