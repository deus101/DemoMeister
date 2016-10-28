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

#ifndef GBUFFER_H
#define	GBUFFER_H

#include "base_buffer.h"
#include "../Math/vec.h"

class GBuffer : public base_buffer
{
public:


	enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_NUM_TEXTURES
	};
	/*
	enum AO_TEXTURE_TYPE {
		AO_TEXTURE_TYPE_AO_MAP,
		//AO_TEXTURE_TYPE_NOISE,
		//AO_TEXTURE_TYPE_NORMAL,
		AO_NUM_TEXTURES
	};
	*/
	GBuffer();

	~GBuffer();

	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	//bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

	void EnablePass(int PassId);

	void StartFrame();
	void BindForGeomPass();
	//void BindForAoPass();
	void BindForStencilPass();
	void BindForLightPass();
	void BindForFinalPass();


	GLuint m_textures[GBUFFER_NUM_TEXTURES];
	GLuint m_depthTexture;
	GLuint m_finalTexture;
private:

	//GLuint m_fbo, geo_fbo, ao_fbo, light_fbo;
	//GLuint m_fbo;
	//GLuint m_uniforms[GBUFFER_NUM_UNIFORMS];
	

	//GLuint ao_textures[AO_NUM_TEXTURES];

	//GLuint m_AoTexture;

	

};

#endif	

