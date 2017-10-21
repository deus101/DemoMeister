#ifndef RENDERPACKET_HPP
#define RENDERPACKET_HPP

#include <iostream>
//#include <list>
//#include "../Math/vec.h"

#include "../Engine/asset.h"
//#include "../Math/math3d.h"
//#include "../Rendrer/context.h"


#include "../util.h"

#include "../Engine/ShaderItem.h"
namespace NS_EFF{



	class renderPacket
	{


	public:
		//renderPacket(const std::string &name) : EffectName(name) { assert(name.length() > 0); }
		renderPacket();


		virtual ~renderPacket();


		//void SetUniMat()
		//{


		//}

		virtual bool Init();

		void Enable();

		
		void SetName(std::string arg);
		std::string GetName();

		//Terrible 
		void SetType(std::string arg);
		std::string GetType();

		void SetStageValue(int val);
		int GetStageValue();

		void SetPassIndex(std::size_t val);
		void SetPassName(std::string arg);

		bool PacketPassHandshake();


	protected:

		std::string EffectName;
		std::string EffectType;

		bool LoadShader(GLenum ShaderType, const char *fileName);
		bool Finalize();


		GLint GetUniformLocation(const char* pUniformName);

		GLint GetProgramParam(GLint param);

		GLuint m_shaderProg;

		EffectStage m_StageParameters;
		EffectStagePtr m_StageParamPtr;
		EffectStageConstPtr m_StageParamConstPtr;


		std::string PassName;
		//int PassIndex;
		std::size_t PassIndex;
		
		bool PassLinked;
		
		bool b_Custom_GLSL_Targets;

		//NS_ENG::NS_SHADER::ShaderItem *ParsedVertexCode, *ParsedGeometryCode, *ParsedFragmentCode;
		//NS_ENG::NS_SHADER::ShaderItemPtr ParsedVertexCode, ParsedGeometryCode, ParsedFragmentCode;
		NS_ENG::NS_SHADER::BaseShaderItemPtr ParsedVertexCode, ParsedGeometryCode, ParsedFragmentCode;

		//sp_PassItemnator

		boost::filesystem::path Vertex_Target, Geometry_Target, Fragment_Target;

		GLuint m_WVPLocation, m_WorldMatrixLocation, m_ViewLocation, m_ProjectionLocation;
		GLuint m_eyeWorldPosLocation, m_screenSizeLocation, v4_FarNearLocation;


	private:

		typedef std::list<GLuint> ShaderObjList;


		ShaderObjList m_shaderObjList;


		GLuint world, world_inv, view, view_inv, projection, worldview, worldview_inv, worldviewprojection, matWVP_inv;
		GLuint viewPos, viewDir;

		

	};


}
#endif