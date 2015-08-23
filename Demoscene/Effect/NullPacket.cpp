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
#include "../util.h"
#include "NullPacket.h"
using namespace NS_EFF;

NullPacket::NullPacket()
{
}

bool NullPacket::Init()
{
	if (!renderPacket::Init()) {
		return false;
	}

	if (!LoadShader(gl::VERTEX_SHADER, "shaders/null_technique.vs")) {
		return false;
	}

	if (!LoadShader(gl::FRAGMENT_SHADER, "shaders/null_technique.fs")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}

	m_WVPLocation = GetUniformLocation("gWVP");

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}


void NullPacket::SetWVP(const M3DMatrix44f& WVP)
{
	gl::UniformMatrix4fv(m_WVPLocation, 1, gl::TRUE_, (const GLfloat*)WVP);
}

