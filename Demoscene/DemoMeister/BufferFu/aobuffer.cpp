
#include <stdio.h>

#include "../util.h"
#include "../Rendrer/context.h"
#include "aobuffer.h"


AoBuffer::AoBuffer()
{
	
	m_fbo = 0;
	Nr_LocalPasses = 1;

	this->RegionalPassList.clear();
	this->LocalPassProperties.clear();
	this->LocalPassProperties.resize(Nr_LocalPasses);
	//ZERO_MEM(this->LocalPassProperties.clear());
	//m_AoTexture = 0;
	//m_depthTexture = 0;
	//m_finalTexture = 0;
	//ZERO_MEM(m_textures);
	ZERO_MEM(ao_textures);
}

AoBuffer::~AoBuffer()
{
	if (m_fbo != 0) {
		glDeleteFramebuffers(1, &m_fbo);

	}

	if (ao_textures[0] != 0) {
		glDeleteTextures(ARRAY_SIZE_IN_ELEMENTS(ao_textures), ao_textures);
	}
	this->LocalPassProperties.clear();

}


bool AoBuffer::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{


	GLenum error;




	glGenFramebuffers(1, &m_fbo);

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);


	glGenTextures(ARRAY_SIZE_IN_ELEMENTS(ao_textures), ao_textures);


	glBindTexture(GL_TEXTURE_2D, ao_textures[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, WindowWidth, WindowHeight, 0, GL_RED, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ao_textures[0], 0);

	GLenum Status1 = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	printf(" AO FBO Status, status: 0x%x\n", Status1);
	if (Status1 != GL_FRAMEBUFFER_COMPLETE) {
		printf("AO FBO error, status: 0x%x\n", Status1);
		return false;
	}


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}






void AoBuffer::BindForAoPass()
{

	GBuffer *test = (GBuffer*)TheDisc->MasterList_Buffers[0].get();


	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	GLuint faen = test->m_textures[test->GBUFFER_TEXTURE_TYPE_NORMAL];
	




	glActiveTexture(NS_ENG::asset::CurrentStage->TextureUnits[TypeOfTexture::GBuffer_WorldPos_UNIT]);
	glBindTexture(GL_TEXTURE_2D, test->m_textures[test->GBUFFER_TEXTURE_TYPE_POSITION]);

	glActiveTexture(NS_ENG::asset::CurrentStage->TextureUnits[TypeOfTexture::GBuffer_Normal_UNIT]);
	glBindTexture(GL_TEXTURE_2D, test->m_textures[test->GBUFFER_TEXTURE_TYPE_NORMAL]);

}


void AoBuffer::EnablePass(int PassId) {

	switch (PassId) {
	case 0:
		this->BindForAoPass();
		break;
	}

}