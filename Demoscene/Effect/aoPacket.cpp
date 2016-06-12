#include "aoPacket.h"
#include <vector>

#include <random> 
#include <string>
using namespace NS_EFF;


aoPacket::aoPacket()
{
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

	//m_ProjectionLocation = GetUniformLocation("gProjection");
	

	 m_ProjectionLocation = GetUniformLocation("gProjection");
	 m_WorldMatrixLocation = GetUniformLocation("gWorld");
	 m_ViewLocation = GetUniformLocation("gView");
	//m_KernelLocation = GetUniformLocation("gKernel[0]");
	
	//gTexNoise
	

	m_posTextureUnitLocation = GetUniformLocation("gPositionMap");

	m_normalTextureUnitLocation = GetUniformLocation("gNormalMap");

	m_NoiseLocation = GetUniformLocation("gTexNoise");


	m_ScreenSizeLocation = GetUniformLocation("gScreenSize");


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
		glUniform3fv(GetUniformLocation(string("gKernel[" + std::to_string(i) + "]").c_str()), 1, (const GLfloat*)&kernel[i]);

	}
}


void aoPacket::InitNoise()
{	//bah no not here ffs
	std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0);
	std::default_random_engine generator;


	std::vector<NS_VEC::VEC3> ssaoNoise;
	for (GLuint i = 0; i < 16; i++)
	{
		NS_VEC::VEC3 noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f); // rotate around z-axis (in tangent space)
		ssaoNoise.push_back(noise);
	}
	glGenTextures(1, &NoiseTexure);
	glBindTexture(GL_TEXTURE_2D, NoiseTexure);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	this->SetNoiseTextureUnit(NoiseTexure);

}
//ugh why dont I virtualize these in the base class
void aoPacket::SetWVP(const M3DMatrix44f& WVP)
{
	//glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, WVP);

	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, WVP);
}


void aoPacket::SetWorldMatrix(const M3DMatrix44f& W)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_FALSE, W);
}




void  aoPacket::SetViewMatrix(const M3DMatrix44f& V)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ViewLocation, 1, GL_FALSE, V);
}


void  aoPacket::SetProjectionMatrix(const M3DMatrix44f& P)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, W);

	glUniformMatrix4fv(m_ProjectionLocation, 1, GL_FALSE, P);

}

void aoPacket::SetScreenSize(unsigned int Width, unsigned int Height)
{
	glUniform2f(m_ScreenSizeLocation, (float)Width, (float)Height);
}


void aoPacket::SetPositionTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_posTextureUnitLocation, TextureUnit);

	std::cout << "AO_Packet Position Uniform Location is " << m_posTextureUnitLocation << "Sampler Id is" << TextureUnit << std::endl;
}


void aoPacket::SetNoiseTextureUnit(unsigned int TextureUnit)
{
	
	glUniform1i(m_NoiseLocation, TextureUnit);
	//glUniform1i(m_NoiseLocation, m_NoiseLocation);
	std::cout << "AO_Packet Noise Uniform Location is " << m_NoiseLocation << "Sampler Id is" << TextureUnit << std::endl;

}


void aoPacket::SetNormalTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_normalTextureUnitLocation, TextureUnit);
	std::cout << "AO_Packet Normal Uniform Location is " << m_normalTextureUnitLocation << "Sampler Id is" << TextureUnit << std::endl;

}