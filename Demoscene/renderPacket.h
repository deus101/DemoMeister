#ifndef RENDERPACKET_HPP
#define RENDERPACKET_HPP
#include "vec.h"
#include "mesh.h"
#include "shaders.h"
#include "model.h"
#include <glload/gl_3_3.hpp>

class renderPacket
{


public:
	renderPacket();

	void DrawNode(NS_MESH::MESH o, NS_MAT::MATERIALS m, M3DMatrix44f MODEL);
	
};



#endif