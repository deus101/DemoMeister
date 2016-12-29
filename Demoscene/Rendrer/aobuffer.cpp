
#include <stdio.h>

#include "../util.h"
#include "../Rendrer/context.h"
#include "aobuffer.h"


AoBuffer::AoBuffer()
{
	//m_fbo = 0;
	m_fbo = 0;
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

	//if (m_depthTexture != 0) {
	//	glDeleteTextures(1, &m_depthTexture);
	//}

	//if (m_finalTexture != 0) {
	//	glDeleteTextures(1, &m_finalTexture);
	//}
}
bool AoBuffer::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{


	GLenum error;



	//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glGenFramebuffers(1, &m_fbo);

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);


	glGenTextures(ARRAY_SIZE_IN_ELEMENTS(ao_textures), ao_textures);


	glBindTexture(GL_TEXTURE_2D, ao_textures[0]);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, WindowWidth, WindowHeight, 0, GL_RGB, GL_FLOAT, NULL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, WindowWidth, WindowHeight, 0, GL_RED, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_AoTexture, 0);
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

	GBuffer *test = (GBuffer*)TheDisc->BufferContainer[0];

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	//glClear(GL_COLOR_BUFFER_BIT);

	GLuint faen = test->m_textures[test->GBUFFER_TEXTURE_TYPE_NORMAL];
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, test->m_textures[test->GBUFFER_TEXTURE_TYPE_POSITION]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, test->m_textures[test->GBUFFER_TEXTURE_TYPE_NORMAL]);




	
	//glActiveTexture(GL_TEXTURE0);
	////glBindTexture(GL_TEXTURE_2D, gb_PosDepth);
	//glBindTexture(GL_TEXTURE_2D, 
	//glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_2D, gb_Normal);
	
	//glActiveTexture(GL_TEXTURE0 );
	//glBindTexture(GL_TEXTURE_2D, GLuint(5));
	//glActiveTexture(GL_TEXTURE2 );
	//glBindTexture(GL_TEXTURE_2D, GLuint(3));
	//glActiveTexture(GL_TEXTURE7);
	//glBindTexture(GL_TEXTURE_2D, GLuint(5));

}


void AoBuffer::EnablePass(int PassId) {

	switch (PassId) {
	case 0:
		this->BindForAoPass();
		break;
	}

}