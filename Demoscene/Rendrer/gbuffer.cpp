/*
Copyright 2011 Etay Meiri

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>

#include "../util.h"
#include "gbuffer.h"
//#include "ogldev_texture.h"

GBuffer::GBuffer()
{
	m_fbo = 0;
	m_depthTexture = 0;
	m_finalTexture = 0;
	ZERO_MEM(m_textures);
}

GBuffer::~GBuffer()
{
	if (m_fbo != 0) {
		gl::DeleteFramebuffers(1, &m_fbo);
	}

	if (m_textures[0] != 0) {
		gl::DeleteTextures(ARRAY_SIZE_IN_ELEMENTS(m_textures), m_textures);
	}

	if (m_depthTexture != 0) {
		gl::DeleteTextures(1, &m_depthTexture);
	}

	if (m_finalTexture != 0) {
		gl::DeleteTextures(1, &m_finalTexture);
	}
}

bool GBuffer::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
	// Create the FBO
	gl::GenFramebuffers(1, &m_fbo);
	gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, m_fbo);

	// Create the gbuffer textures
	gl::GenTextures(ARRAY_SIZE_IN_ELEMENTS(m_textures), m_textures);

	gl::GenTextures(1, &m_depthTexture);

	gl::GenTextures(1, &m_finalTexture);

	for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_textures); i++) {
		gl::BindTexture(gl::TEXTURE_2D, m_textures[i]);
		gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGB32F, WindowWidth, WindowHeight, 0, gl::RGB, gl::FLOAT, NULL);
		gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST);
		gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST);
		gl::FramebufferTexture2D(gl::DRAW_FRAMEBUFFER, gl::COLOR_ATTACHMENT0 + i, gl::TEXTURE_2D, m_textures[i], 0);
	}

	// depth
	gl::BindTexture(gl::TEXTURE_2D, m_depthTexture);
	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::DEPTH32F_STENCIL8, WindowWidth, WindowHeight, 0, gl::DEPTH_STENCIL, gl::FLOAT_32_UNSIGNED_INT_24_8_REV, NULL);
	gl::FramebufferTexture2D(gl::DRAW_FRAMEBUFFER, gl::DEPTH_STENCIL_ATTACHMENT, gl::TEXTURE_2D, m_depthTexture, 0);

	// final
	gl::BindTexture(gl::TEXTURE_2D, m_finalTexture);
	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, WindowWidth, WindowHeight, 0, gl::RGB, gl::FLOAT, NULL);
	gl::FramebufferTexture2D(gl::DRAW_FRAMEBUFFER, gl::COLOR_ATTACHMENT4, gl::TEXTURE_2D, m_finalTexture, 0);

	GLenum Status = gl::CheckFramebufferStatus(gl::FRAMEBUFFER);

	if (Status != gl::FRAMEBUFFER_COMPLETE) {
		printf("FB error, status: 0x%x\n", Status);
		return false;
	}

	// restore default FBO
	gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, 0);

	return true;
}


void GBuffer::StartFrame()
{
	gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, m_fbo);
	gl::DrawBuffer(gl::COLOR_ATTACHMENT4);
	gl::Clear(gl::COLOR_BUFFER_BIT);
}


void GBuffer::BindForGeomPass()
{
	gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, m_fbo);

	GLenum DrawBuffers[] = { gl::COLOR_ATTACHMENT0,
		gl::COLOR_ATTACHMENT1,
		gl::COLOR_ATTACHMENT2 };

	gl::DrawBuffers(ARRAY_SIZE_IN_ELEMENTS(DrawBuffers), DrawBuffers);
}


void GBuffer::BindForStencilPass()
{
	// must disable the draw buffers 
	gl::DrawBuffer(gl::NONE);
}





void GBuffer::BindForLightPass()
{
	gl::DrawBuffer(gl::COLOR_ATTACHMENT4);

	for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_textures); i++) {
		gl::ActiveTexture(gl::TEXTURE0 + i);
		gl::BindTexture(gl::TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION + i]);
	}
}


void GBuffer::BindForFinalPass()
{
	gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, 0);
	gl::BindFramebuffer(gl::READ_FRAMEBUFFER, m_fbo);
	gl::ReadBuffer(gl::COLOR_ATTACHMENT4);
}