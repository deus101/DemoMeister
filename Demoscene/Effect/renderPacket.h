#ifndef RENDERPACKET_HPP
#define RENDERPACKET_HPP

#include <iostream>
#include <list>
#include "../Math/vec.h"

#include "../Engine/asset.h"
#include "../Math/math3d.h"
//#include "../Rendrer/context.h"
#include "../util.h"

namespace NS_EFF{

	class renderPacket
	{

		//renderPacket(const NS_REND::context &aContext);
	public:
		renderPacket();

		virtual ~renderPacket();


		//void SetUniMat()
		//{


		//}

		virtual bool Init();

		void Enable();

	

	protected:

		bool LoadShader(GLenum ShaderType, const char *fileName);
		bool Finalize();

		GLint GetUniformLocation(const char* pUniformName);

		GLint GetProgramParam(GLint param);

		GLuint m_shaderProg;

	private:

		typedef std::list<GLuint> ShaderObjList;


		ShaderObjList m_shaderObjList;


		GLuint world, world_inv, view, view_inv, projection, worldview, worldview_inv, worldviewprojection, matWVP_inv;
		GLuint viewPos, viewDir;


	};


}
#endif