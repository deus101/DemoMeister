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

#include <limits.h>
#include <string.h>

#include "DirLightPacket.h"
//#include "ogldev_util.h"
using namespace NS_EFF;

DirLightPacket::DirLightPacket()
{
}

bool DirLightPacket::Init()
{
	if (!renderPacket::Init()) {
		return false;
	}

	if (!LoadShader(gl::VERTEX_SHADER, "shaders/light_pass.vs")) {
		return false;
	}

	if (!LoadShader(gl::FRAGMENT_SHADER, "shaders/dir_light_pass.fs")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}

	m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
	m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
	m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
	m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");

	if (m_dirLightLocation.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.Color == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.Direction == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return lightPacket::Init();
}



void DirLightPacket::SetDirectionalLight(const DirectionalLight& Light)
{
	gl::Uniform3f(m_dirLightLocation.Color, Light.Color.X, Light.Color.Y, Light.Color.Z);
	gl::Uniform1f(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
	NS_VEC::VEC3 Direction = Light.Direction;
	Direction.NormIt();
	gl::Uniform3f(m_dirLightLocation.Direction, Direction.X, Direction.Y, Direction.Z);
	gl::Uniform1f(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
}


