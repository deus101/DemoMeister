#include "rendrer.h"


#include "../SceneGraph/node.h"
#include "../SceneGraph/transform.h"
#include "../SceneGraph/assetNode.h"
#include "../SceneGraph/modelNode.h"


#include <vector>
#include <stack>


using namespace NS_ENG;
using namespace NS_SG;


void rendrer::visit(node *Node, M3DMatrix44f  world)
{
	
	
	//if (NS_SG::node::NODE_CAMERA == Node->getType())
	//{
	//	Node->

	//}

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


			//std::cout << "Node: " << Node->getName() << " Pos: ";
			//std::cout << "[" << world[12] << "] ";
			//std::cout << "[" << world[13] << "] ";
			//std::cout << "[" << world[14] << "] " << endl;

			M3DMatrix44f wv, wvp;

			//assert(NULL != p);
			M3DMatrix44f world_view_proj, matWVP_inv;
			m3dMatrixMultiply44(wv, world, view);


			m3dMatrixMultiply44(wvp, wv, projection);
			
			
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

			



			//std::cout << "Node: " << Node->getName() << " Pos: ";
			//	std::cout << "[" << world[12] << "] ";
			//	std::cout << "[" << world[13] << "] ";
			//	std::cout << "[" << world[14] << "] " << endl;
				


			s_LPL = lPoint->GetPointLight();
			M3DMatrix44f wv, wvp;

			//assert(NULL != p);
			M3DMatrix44f world_view_proj, matWVP_inv;
			m3dMatrixMultiply44(wv, world, view);

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


void rendrer::draw()
{	Visible.clear();
	VisiblePoint.clear();
	VisibleDir.clear();

	//don't do this also USE EIGEN OF GLM OR WRITE YOUR OWN MATH3D IS SHIT!
	M3DMatrix44f world;
	m3dLoadIdentity44(world);
	//std::cout << "Does it work";
	visit(scene, world );
	//sceneloadern bør få en referance til context objektet men hvordan rettferdigjør jeg valg av effekt filen? Utifra en haug med assetnoder
	//scene->c
	//mContext->
	//m_DSGeomPassTech.Enable();
	

	mContext->mGBuffer.StartFrame();
	//mContext->mGBuffer.BindForGeomPass();
	// Only the geometry pass updates the depth buffer
	gl::DepthMask(gl::TRUE_);
	
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	gl::Enable(gl::DEPTH_TEST);

	
	//p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
	//p.SetPerspectiveProj(m_persProjInfo);
	//p.Rotate(0.0f, m_scale, 0.0f);
	//std::cout << "before geom loop" << std::endl;
	for (vIT iv = beginVisible(); iv != endVisible(); ++iv) {
		//p.WorldPos(m_boxPositions[i]);
		//eller visible i ->magic->enable og modellen bare kjører draw array Men det må gjøres i modelnode
		
		
		iv->sNode->Magic->Enable();
		//std::cout << "Inside geom loop2" << std::endl;
		mContext->mGBuffer.BindForGeomPass();
		//std::cout << "Inside geom loop3" << std::endl;
		iv->sNode->Magic->SetWVP(iv->sWVP);
		iv->sNode->Magic->SetWorldMatrix(iv->sTransform);
		iv->sNode->Model->Draw();
	}

	
	// When we get here the depth buffer is already populated and the stencil pass
	// depends on it, but it does not write to it.
	gl::DepthMask(gl::FALSE_);


	NS_VEC::VEC3 EyeWorldPos(view[12], view[13], view[14]);

	for (vPITc ip = beginVisiblePoint(); ip != endVisiblePoint(); ++ip) {
		ip->sNode->NullMagic->Enable();

		// Disable color/depth write and enable stencil
		mContext->mGBuffer.BindForStencilPass();
		gl::Enable(gl::DEPTH_TEST);

		gl::Disable(gl::CULL_FACE);

		gl::Clear(gl::STENCIL_BUFFER_BIT);

		// We need the stencil test to be enabled but we want it
		// to succeed always. Only the depth test matters.
		gl::StencilFunc(gl::ALWAYS, 0, 0);

		gl::StencilOpSeparate(gl::BACK, gl::KEEP, gl::INCR_WRAP, gl::KEEP);
		gl::StencilOpSeparate(gl::FRONT, gl::KEEP, gl::DECR_WRAP, gl::KEEP);



		ip->sNode->NullMagic->SetWVP(ip->sWVP);
		sphere.Draw();
		
		
		
		
		
		mContext->mGBuffer.BindForLightPass();
		//p.WorldPos(m_boxPositions[i]);
		//eller visible i ->magic->enable og modellen bare kjører draw array Men det må gjøres i modelnode

		ip->sNode->LightMagic->Enable();
		ip->sNode->LightMagic->SetEyeWorldPos(EyeWorldPos);


		gl::StencilFunc(gl::NOTEQUAL, 0, 0xFF);

		gl::Disable(gl::DEPTH_TEST);
		gl::Enable(gl::BLEND);
		gl::BlendEquation(gl::FUNC_ADD);
		gl::BlendFunc(gl::ONE, gl::ONE);

		gl::Enable(gl::CULL_FACE);
		gl::CullFace(gl::FRONT);
		ip->sNode->LightMagic->SetWVP(ip->sWVP);
		ip->sNode->LightMagic->SetPointLight(ip->sPL);

		sphere.Draw();

		gl::CullFace(gl::BACK);

		gl::Disable(gl::BLEND);
	}
	gl::Disable(gl::STENCIL_TEST);

	for (vDIT id = beginVisibleDir(); id != endVisibleDir(); ++id) {
		mContext->mGBuffer.BindForLightPass();
		id->sNode->LightMagic->Enable();
		id->sNode->LightMagic->SetEyeWorldPos(EyeWorldPos);
		id->sNode->LightMagic->SetDirectionalLight(id->sDL);
		gl::Disable(gl::DEPTH_TEST);
		gl::Enable(gl::BLEND);
		gl::BlendEquation(gl::FUNC_ADD);
		gl::BlendFunc(gl::ONE, gl::ONE);

		quad.Draw();
		gl::Disable(gl::BLEND);

	
	
	}

	//std::cout << "height: " << mContext->GetPixelHeight() << " width: " << mContext->GetPixelHeight() << std::endl;
	
	mContext->mGBuffer.BindForFinalPass();
	gl::BlitFramebuffer(0, 0, mContext->GetPixelWidth(), mContext->GetPixelHeight(),
		0, 0, mContext->GetPixelWidth(), mContext->GetPixelHeight(), gl::COLOR_BUFFER_BIT, gl::LINEAR);

}