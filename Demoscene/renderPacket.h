#ifndef RENDERPACKET_HPP
#define RENDERPACKET_HPP

#include <list>
#include "vec.h"
#include "mesh.h"
#include "shaders.h"
#include "model.h"
#include "asset.h"
#include "math3d.h"
//#include <glload/gl_3_3.hpp>




class renderPacket
{


public:
	renderPacket();

	virtual ~renderPacket();
	

	//void SetUniMat()
	//{


	//}

	virtual bool Init();

	void Enable();

	void Draw(model *o, const M3DMatrix44f mMat);

	void setMatrices(const M3DMatrix44f &mWorld, const M3DMatrix44f&mview, const M3DMatrix44f &proj)
	{
		//world GetUniformLocation("gWVP");

		M3DMatrix44f wv, wvp;

		//assert(NULL != p);
		M3DMatrix44f world_view_proj, matWVP_inv;
		m3dMatrixMultiply44(wv, mWorld, mview);


		m3dMatrixMultiply44(wvp, wv, proj);
		m3dCopyMatrix44(world_view_proj, wvp);
		m3dInvertMatrix44(matWVP_inv, world_view_proj);
		//https://github.com/progschj/OpenGL-Examples/blob/master/06instancing3_uniform_buffer.cpp

		M3DMatrix44f world_view;
		m3dMatrixMultiply44(world_view, mWorld, mview);
		M3DMatrix44f world_inv;
		M3DMatrix44f world_view_inv;
		m3dInvertMatrix44(world_inv, mWorld);
		m3dInvertMatrix44(world_view_inv, world_view);

		if (this->world != NULL)
			setMatrix(this->world, mWorld);
		if (this->world_inv != NULL)
			setMatrix(this->world_inv, world_inv);
		if (this->view != NULL)
			setMatrix(this->view, mview);
		if (this->view_inv != NULL)
			//setMatrix(this->view, view.inverse());
		if (this->projection != NULL)
			setMatrix(this->projection, proj);
		if (this->worldview != NULL)
			setMatrix(this->worldview, world_view);
		if (this->worldview_inv != NULL)
			setMatrix(this->worldview_inv, world_view_inv);
		if (this->worldviewprojection != NULL)
			setMatrix(this->worldviewprojection, world_view_proj);
		if (this->matWVP_inv)
			setMatrix(this->matWVP_inv, matWVP_inv);

	//	if (this->viewPos != NULL) setVector3(this->viewPos, world_view_inv.getTranslation());
	//	if (this->viewDir != NULL) setVector3(this->viewDir, world_view.getZAxis());

	};
	//https://github.com/222464/EvolvedVirtualCreaturesRepo/tree/master/VirtualCreatures/Volumetric_SDL/Source/SceneEffects
	void setMatrix(GLuint param, const M3DMatrix44f &mat)
	{
		//https://github.com/222464/EvolvedVirtualCreaturesRepo/blob/master/VirtualCreatures/Volumetric_SDL/Source/Renderer/Shader/UBOShaderInterface.cpp
		//hva med noe annet for å sjekke om konteksten programmet er oppe?
		//assert(NULL != p);
	//	p->SetMatrix(param, &mat);

	
	};

	

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



#endif