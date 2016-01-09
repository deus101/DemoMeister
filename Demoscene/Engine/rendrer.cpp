#include "rendrer.h"


#include "../SceneGraph/node.h"
#include "../SceneGraph/transform.h"
#include "../SceneGraph/assetNode.h"
#include "../SceneGraph/modelNode.h"


#include <vector>
#include <stack>


using namespace NS_ENG;
using namespace NS_SG;

// I might be making a mistake using this as a the callback interface
void rendrer::visit(node *Node, M3DMatrix44f  world)
{
	
	
	if (NS_SG::node::NODE_CAMERA == Node->getType())
	{
		camera *cammy = reinterpret_cast<camera*>(Node);

		M3DMatrix44f world, local;
		cammy->getAbsoluteTransform(world);

		std::cout << "Node: " << Node->getName() << " Pos: " << endl;
		std::cout << "[" << world[0] << "] ";
		std::cout << "[" << world[1] << "] ";
		std::cout << "[" << world[2] << "] ";
		std::cout << "[" << world[3] << "] " << endl;

		std::cout << "[" << world[4] << "] ";
		std::cout << "[" << world[5] << "] ";
		std::cout << "[" << world[6] << "] ";
		std::cout << "[" << world[7] << "] " << endl;

		std::cout << "[" << world[8] << "] ";
		std::cout << "[" << world[9] << "] ";
		std::cout << "[" << world[10] << "] ";
		std::cout << "[" << world[11] << "] " << endl;

		std::cout << "[" << world[12] << "] ";
		std::cout << "[" << world[13] << "] ";
		std::cout << "[" << world[14] << "] ";
		std::cout << "[" << world[15] << "] " << endl;


		cammy->getLocalTransform(local);
		std::cout << "Node: " << Node->getName() << " local transform matrix: " << endl;

		std::cout << "[" << local[0] << "] ";
		std::cout << "[" << local[1] << "] ";
		std::cout << "[" << local[2] << "] ";
		std::cout << "[" << local[3] << "] " << endl;

		std::cout << "[" << local[4] << "] ";
		std::cout << "[" << local[5] << "] ";
		std::cout << "[" << local[6] << "] ";
		std::cout << "[" << local[7] << "] " << endl;

		std::cout << "[" << local[8] << "] ";
		std::cout << "[" << local[9] << "] ";
		std::cout << "[" << local[10] << "] ";
		std::cout << "[" << local[11] << "] " << endl;

		std::cout << "[" << local[12] << "] ";
		std::cout << "[" << local[13] << "] ";
		std::cout << "[" << local[14] << "] ";
		std::cout << "[" << local[15] << "] " << endl;

		//cammy

	}

	if (NS_SG::node::NODE_ASSET == Node->getType())
	{
		//std::cout << Node->getName() << std::endl;
		RendrerItem Tmp;
		//aabb checks of culling her
		modelNode *mesh = reinterpret_cast<modelNode*>(Node);
		if (NULL != mesh->Magic)
		{
			M3DMatrix44f world; 
			//Node->g
			Node->getAbsoluteTransform(world);


			std::cout << "Node: " << Node->getName() << " Pos: " << endl;
			std::cout << "[" << world[0] << "] ";
			std::cout << "[" << world[1] << "] ";
			std::cout << "[" << world[2] << "] ";
			std::cout << "[" << world[3] << "] " << endl;

			std::cout << "[" << world[4] << "] ";
			std::cout << "[" << world[5] << "] ";
			std::cout << "[" << world[6] << "] ";
			std::cout << "[" << world[7] << "] " << endl;

			std::cout << "[" << world[8] << "] ";
			std::cout << "[" << world[9] << "] ";
			std::cout << "[" << world[10] << "] ";
			std::cout << "[" << world[11] << "] " << endl;

			std::cout << "[" << world[12] << "] ";
			std::cout << "[" << world[13] << "] ";
			std::cout << "[" << world[14] << "] ";
			std::cout << "[" << world[15] << "] " << endl;
			M3DMatrix44f wv, wvp;

			//assert(NULL != p);
			M3DMatrix44f world_view_proj, matWVP_inv;
			m3dMatrixMultiply44(wv, world, view);

			std::cout << "World View Matrix " << endl;
			std::cout << "[" << wv[0] << "] ";
			std::cout << "[" << wv[1] << "] ";
			std::cout << "[" << wv[2] << "] ";
			std::cout << "[" << wv[3] << "] " << endl;

			std::cout << "[" << wv[4] << "] ";
			std::cout << "[" << wv[5] << "] ";
			std::cout << "[" << wv[6] << "] ";
			std::cout << "[" << wv[7] << "] " << endl;

			std::cout << "[" << wv[8] << "] ";
			std::cout << "[" << wv[9] << "] ";
			std::cout << "[" << wv[10] << "] ";
			std::cout << "[" << wv[11] << "] " << endl;

			std::cout << "[" << wv[12] << "] ";
			std::cout << "[" << wv[13] << "] ";
			std::cout << "[" << wv[14] << "] ";
			std::cout << "[" << wv[15] << "] " << endl;

			m3dMatrixMultiply44(wvp, wv, projection);


			std::cout << "World View Projection " << endl;
			std::cout << "[" << wvp[0] << "] ";
			std::cout << "[" << wvp[1] << "] ";
			std::cout << "[" << wvp[2] << "] ";
			std::cout << "[" << wvp[3] << "] " << endl;

			std::cout << "[" << wvp[4] << "] ";
			std::cout << "[" << wvp[5] << "] ";
			std::cout << "[" << wvp[6] << "] ";
			std::cout << "[" << wvp[7] << "] " << endl;

			std::cout << "[" << wvp[8] << "] ";
			std::cout << "[" << wvp[9] << "] ";
			std::cout << "[" << wvp[10] << "] ";
			std::cout << "[" << wvp[11] << "] " << endl;

			std::cout << "[" << wvp[12] << "] ";
			std::cout << "[" << wvp[13] << "] ";
			std::cout << "[" << wvp[14] << "] ";
			std::cout << "[" << wvp[15] << "] " << endl;

			
			m3dCopyMatrix44(Tmp.sWVP, wvp);
			m3dCopyMatrix44(Tmp.sTransform, world);
			//m3dInvertMatrix44(matWVP_inv, world_view_proj);

			//mesh->Magic->setMatrices(world , view, projection);
			//mesh->Magic->commitChanges();
			Tmp.sNode = mesh;
		}
		

		//mesh->draw();
		Visible.push_back(Tmp);

		//Ide: en drawque item som har Matrisene og informasjonen den trenger, må sorte denne skikkelig uansett. Transformasjons matrisen iallefall.

		//kansje der kan jeg bruke den kompliserte matrise genererings funksjonne

	}

	if (NS_SG::node::NODE_LIGHT_POINT == Node->getType())
	{

		//std::cout << Node->getName() << std::endl;
		PointLightItem Tmp;
		//aabb checks of culling her
		pointLightNode *lPoint = reinterpret_cast<pointLightNode*>(Node);
		PointLight s_LPL;
		if (NULL != lPoint->LightMagic)
		{
			M3DMatrix44f world;
			//Node->g
			Node->getAbsoluteTransform(world);

			
			


				std::cout << "Node: " << Node->getName() << " Pos: " << endl;

				std::cout << "[" << world[0] << "] ";
				std::cout << "[" << world[1] << "] ";
				std::cout << "[" << world[2] << "] ";
				std::cout << "[" << world[3] << "] " << endl;

				std::cout << "[" << world[4] << "] ";
				std::cout << "[" << world[5] << "] ";
				std::cout << "[" << world[6] << "] ";
				std::cout << "[" << world[7] << "] " << endl;

				std::cout << "[" << world[8] << "] ";
				std::cout << "[" << world[9] << "] ";
				std::cout << "[" << world[10] << "] ";
				std::cout << "[" << world[11] << "] " << endl;

				std::cout << "[" << world[12] << "] ";
				std::cout << "[" << world[13] << "] ";
				std::cout << "[" << world[14] << "] ";
				std::cout << "[" << world[15] << "] " << endl;
				


			s_LPL = lPoint->GetPointLight();
			M3DMatrix44f wv, wvp;

			//assert(NULL != p);
			//M3DMatrix44f world_view_proj, matWVP_inv;
			M3DMatrix44f w_scale, w_scaled;
			float f_scale = CalcPointLightBSphere(s_LPL);
	
			
			m3dScaleMatrix44(w_scale, f_scale, f_scale, f_scale);

			m3dMatrixMultiply44(w_scaled, world, w_scale);
			m3dMatrixMultiply44(wv, w_scaled, view);

			m3dMatrixMultiply44(wvp, wv, projection);

			m3dCopyMatrix44(Tmp.sWVP, wvp);
			

			//m3dCopyMatrix44(Tmp.sWVP, wvp);
			//m3dCopyMatrix44(Tmp.sWVP, world);
			//m3dInvertMatrix44(matWVP_inv, world_view_proj);
			//lPoint->LightMagic->
			//mesh->Magic->setMatrices(world , view, projection);
			//mesh->Magic->commitChanges();
		}
		Tmp.sPL = s_LPL;
		Tmp.sNode = lPoint;

		//mesh->draw();
		VisiblePoint.push_back(Tmp);
		

	}

	if (NS_SG::node::NODE_LIGHT_DIR == Node->getType())
	{
		DirLightItem Tmp;
		dirLightNode *lDir = reinterpret_cast<dirLightNode*>(Node);
		if (NULL != lDir->LightMagic)
		{
			M3DMatrix44f world;
			//Node->g
			Node->getAbsoluteTransform(world);
			M3DMatrix44f wv, wvp;

			//assert(NULL != p);
			M3DMatrix44f world_view_proj, matWVP_inv;
			m3dMatrixMultiply44(wv, world, view);

			m3dMatrixMultiply44(wvp, wv, projection);

			
			Tmp.sNode = lDir;
			Tmp.sDL = lDir->GetDirLight();
			m3dCopyMatrix44(Tmp.sWVP, wvp);



		}
	
		VisibleDir.push_back(Tmp);
		

	}

	for (node::child_iterator i = Node->beginChildren(); i != Node->endChildren(); ++i)
	{
		if (NS_SG::node::NODE_COMPOSER != (*i)->getType())
		{
			visit(*i, world);
		}
	}

		
}

void rendrer::Run()
{
	ContextRun(this);

}

void rendrer::RenderSceneCB()
{	Visible.clear();
	VisiblePoint.clear();
	VisibleDir.clear();

	//don't do this also USE EIGEN OF GLM OR WRITE YOUR OWN MATH3D IS SHIT!
	M3DMatrix44f world;
	m3dLoadIdentity44(world);
	//std::cout << "Does it work";
	visit(scene, world );

	
	mgBuffer->StartFrame();

	mgBuffer->BindForGeomPass();

	//NS_REND::mGBuffer->BindForGeomPass();
	// Only the geometry pass updates the depth buffer
	glDepthMask(GL_TRUE);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	

	//std::cout << "before geom loop" << std::endl;
	for (vIT iv = beginVisible(); iv != endVisible(); ++iv) {
		//p.WorldPos(m_boxPositions[i]);
		//eller visible i ->magic->enable og modellen bare kjører draw array Men det må gjøres i modelnode
		
		
		iv->sNode->Magic->Enable();
		//std::cout << "Inside geom loop2" << std::endl;

		//std::cout << "Inside geom loop3" << std::endl;
		iv->sNode->Magic->SetWVP(iv->sWVP);
		iv->sNode->Magic->SetWorldMatrix(iv->sTransform);
		iv->sNode->Model->Draw();
	}

	
	// When we get here the depth buffer is already populated and the stencil pass
	// depends on it, but it does not write to it.
	glDepthMask(GL_FALSE);

	glEnable(GL_STENCIL_TEST);

	NS_VEC::VEC3 EyeWorldPos(view[12], view[13], view[14]);
	//kamera->
	std::cout << "ViewMatrix : " << endl;

	std::cout << "[" << view[0] << "] ";
	std::cout << "[" << view[1] << "] ";
	std::cout << "[" << view[2] << "] ";
	std::cout << "[" << view[3] << "] " << endl;

	std::cout << "[" << view[4] << "] ";
	std::cout << "[" << view[5] << "] ";
	std::cout << "[" << view[6] << "] ";
	std::cout << "[" << view[7] << "] " << endl;

	std::cout << "[" << view[8] << "] ";
	std::cout << "[" << view[9] << "] ";
	std::cout << "[" << view[10] << "] ";
	std::cout << "[" << view[11] << "] " << endl;

	std::cout << "[" << view[12] << "] ";
	std::cout << "[" << view[13] << "] ";
	std::cout << "[" << view[14] << "] ";
	std::cout << "[" << view[15] << "] " << endl;


	std::cout << "Projection : " << endl;
	
	std::cout << "[" << projection[0] << "] ";
	std::cout << "[" << projection[1] << "] ";
	std::cout << "[" << projection[2] << "] ";
	std::cout << "[" << projection[3] << "] " << endl;

	std::cout << "[" << projection[4] << "] ";
	std::cout << "[" << projection[5] << "] ";
	std::cout << "[" << projection[6] << "] ";
	std::cout << "[" << projection[7] << "] " << endl;

	std::cout << "[" << projection[8] << "] ";
	std::cout << "[" << projection[9] << "] ";
	std::cout << "[" << projection[10] << "] ";
	std::cout << "[" << projection[11] << "] " << endl;

	std::cout << "[" << projection[12] << "] ";
	std::cout << "[" << projection[13] << "] ";
	std::cout << "[" << projection[14] << "] ";
	std::cout << "[" << projection[15] << "] " << endl;

	for (vPITc ip = beginVisiblePoint(); ip != endVisiblePoint(); ++ip) {
		ip->sNode->NullMagic->Enable();

		// Disable color/depth write and enable stencil
		mgBuffer->BindForStencilPass();
		//NS_REND::mGBuffer->BindForStencilPass();
		glEnable(GL_DEPTH_TEST);

		glDisable(GL_CULL_FACE);

		glClear(GL_STENCIL_BUFFER_BIT);

		// We need the stencil test to be enabled but we want it
		// to succeed always. Only the depth test matters.
		glStencilFunc(GL_ALWAYS, 0, 0);

		glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
		glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);



		ip->sNode->NullMagic->SetWVP(ip->sWVP);
		sphere_null->Draw();
		
		
		
		
		
		mgBuffer->BindForLightPass();
		//NS_REND::mGBuffer->BindForLightPass();
		//p.WorldPos(m_boxPositions[i]);
		//eller visible i ->magic->enable og modellen bare kjører draw array Men det må gjøres i modelnode

		ip->sNode->LightMagic->Enable();
		ip->sNode->LightMagic->SetEyeWorldPos(EyeWorldPos);

		//look at this
		glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		ip->sNode->LightMagic->SetWVP(ip->sWVP);
		ip->sNode->LightMagic->SetPointLight(ip->sPL);

		sphere_light->Draw();
		
		glCullFace(GL_BACK);

		glDisable(GL_BLEND);
	}

	glDisable(GL_STENCIL_TEST);

	for (vDIT id = beginVisibleDir(); id != endVisibleDir(); ++id) {

		mgBuffer->BindForLightPass();

		//NS_REND::mGBuffer->BindForLightPass();

		id->sNode->LightMagic->Enable();
		id->sNode->LightMagic->SetEyeWorldPos(EyeWorldPos);
		id->sNode->LightMagic->SetDirectionalLight(id->sDL);
		id->sNode->LightMagic->SetWVP(id->sWVP);


		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		quad->Draw();
		glDisable(GL_BLEND);

	
	
	}

	//std::cout << "height: " << mContext->GetPixelHeight() << " width: " << mContext->GetPixelHeight() << std::endl;
	//mContext
	unsigned int w = GetPixelWidth();
	unsigned int h = GetPixelHeight();
	mgBuffer->BindForFinalPass();
	//NS_REND::mGBuffer->BindForFinalPass();
	glBlitFramebuffer(0, 0, w, h,
		0, 0, w, h, GL_COLOR_BUFFER_BIT, GL_LINEAR);


	
	Swap();
	//glutSwapBuffers();




}

float rendrer::CalcPointLightBSphere(const PointLight& Light)
{
	float MaxChannel = fmax(fmax(Light.Color.X, Light.Color.Y), Light.Color.Z);

	float ret = (-Light.Attenuation.Linear + sqrtf(Light.Attenuation.Linear * Light.Attenuation.Linear - 4 * Light.Attenuation.Exp * (Light.Attenuation.Exp - 256 * MaxChannel * Light.DiffuseIntensity)))
		/
		2 * Light.Attenuation.Exp;

	return ret;
}