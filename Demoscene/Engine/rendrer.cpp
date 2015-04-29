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
	//std::cout << Node->getName() << std::endl;
	//std::cout << Node->getType() << std::endl;   showed 0 1 4 4 
	if (NS_SG::node::NODE_ASSET == Node->getType())
	{
		//std::cout << Node->getName() << std::endl;
		RendrerItem Tmp;
		//aabb checks of culling her
		modelNode *mesh = reinterpret_cast<modelNode*>(&Node);
		if (NULL != mesh->Magic)
		{
			M3DMatrix44f world; 
			//Node->g
			Node->getAbsoluteTransform(world);
			//	std::cout << "[" << world[0] << "] ";
			//	std::cout << "[" << world[1] << "] ";
			//	std::cout << "[" << world[2] << "] ";
			//	std::cout << "[" << world[3] << "] " << endl;
			//	std::cout << "[" << world[4] << "] ";
			//	std::cout << "[" << world[5] << "] ";
			//	std::cout << "[" << world[6] << "] ";
			//	std::cout << "[" << world[7] << "] " << endl;
			//	std::cout << "[" << world[8] << "] ";
			//	std::cout << "[" << world[9] << "] ";
			//	std::cout << "[" << world[10] << "] ";
			//	std::cout << "[" << world[11] << "] " << endl;
			//	std::cout << "[" << world[12] << "] ";
			//	std::cout << "[" << world[13] << "] ";
			//	std::cout << "[" << world[14] << "] ";
			//	std::cout << "[" << world[15] << "] " << endl;



			M3DMatrix44f wv, wvp;

			//assert(NULL != p);
			M3DMatrix44f world_view_proj, matWVP_inv;
			m3dMatrixMultiply44(wv, world, view);


			m3dMatrixMultiply44(wvp, wv, projection);
			
			
			m3dCopyMatrix44(Tmp.sWVP, wvp);
			m3dCopyMatrix44(Tmp.sWVP, world);
			//m3dInvertMatrix44(matWVP_inv, world_view_proj);

			//mesh->Magic->setMatrices(world , view, projection);
			//mesh->Magic->commitChanges();
		}
		Tmp.sNode = mesh;

		//mesh->draw();
		Visible.push_back(Tmp);

		//Ide: en drawque item som har Matrisene og informasjonen den trenger, må sorte denne skikkelig uansett. Transformasjons matrisen iallefall.

		//kansje der kan jeg bruke den kompliserte matrise genererings funksjonne

	}

	if (NS_SG::node::NODE_LIGHT_POINT == Node->getType())
	{
		std::cout << "yes there is light" << endl;
		if (NS_SG::node::NODE_ASSET == Node->getType())
		{
			//std::cout << Node->getName() << std::endl;
			PointLightItem Tmp;
			//aabb checks of culling her
			pointLightNode *mesh = reinterpret_cast<pointLightNode*>(&Node);
			if (NULL != mesh->Magic)
			{
				M3DMatrix44f world;
				//Node->g
				Node->getAbsoluteTransform(world);




				M3DMatrix44f wv, wvp;

				//assert(NULL != p);
				M3DMatrix44f world_view_proj, matWVP_inv;
				m3dMatrixMultiply44(wv, world, view);


				m3dMatrixMultiply44(wvp, wv, projection);


				m3dCopyMatrix44(Tmp.sWVP, wvp);
				m3dCopyMatrix44(Tmp.sWVP, world);
				//m3dInvertMatrix44(matWVP_inv, world_view_proj);

				//mesh->Magic->setMatrices(world , view, projection);
				//mesh->Magic->commitChanges();
			}
			Tmp.sNode = mesh;

			//mesh->draw();
			VisiblePoint.push_back(Tmp);
		}

	}

	for (node::child_iterator i = Node->beginChildren(); i != Node->endChildren(); ++i)
		visit(*i, world);
}


void rendrer::draw()
{
	Visible.clear();
	//don't do this also USE EIGEN OF GLM OR WRITE YOUR OWN MATH3D IS SHIT!
	M3DMatrix44f world;
	m3dLoadIdentity44(world);
	visit(scene, world );

	//sceneloadern bør få en referance til context objektet men hvordan rettferdigjør jeg valg av effekt filen? Utifra en haug med assetnoder
	//scene->c
	//mContext->
	//m_DSGeomPassTech.Enable();

	//m_gbuffer.BindForGeomPass();
	mContext->mGBuffer.BindForGeomPass();
	// Only the geometry pass updates the depth buffer
	gl::DepthMask(gl::TRUE_);

	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	gl::Enable(gl::DEPTH_TEST);

	
	//p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
	//p.SetPerspectiveProj(m_persProjInfo);
	//p.Rotate(0.0f, m_scale, 0.0f);

	for (vIT = Visible.begin(); vIT != Visible.end(); ++vIT) {
		//p.WorldPos(m_boxPositions[i]);
		//eller visible i ->magic->enable og modellen bare kjører draw array Men det må gjøres i modelnode

		vIT->sNode->Magic->Enable();
		vIT->sNode->Magic->SetWVP(vIT->sWVP);
		vIT->sNode->Magic->SetWorldMatrix(vIT->sTransform);

	}
	mContext->mGBuffer.BindForLightPass();


	// When we get here the depth buffer is already populated and the stencil pass
	// depends on it, but it does not write to it.
	gl::DepthMask(gl::FALSE_);

}