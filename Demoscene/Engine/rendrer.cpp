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
	if (4 == Node->getType())
	{
		modelNode *mesh = reinterpret_cast<modelNode*>(&Node);
		if (NULL != mesh->Magic)
		{
			M3DMatrix44f world; 
			Node->getAbsoluteTransform(world);

			mesh->Magic->setMatrices(world , view, projection);
			//mesh->Magic->commitChanges();
		}
		//mesh->draw();
		Visible.push_back(mesh);

		//Ide: en drawque item som har Matrisene og informasjonen den trenger, må sorte denne skikkelig uansett. Transformasjons matrisen iallefall.

		//kansje der kan jeg bruke den kompliserte matrise genererings funksjonne

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

	for (unsigned int i = 0; i < Visible.size(); i++) {
		//p.WorldPos(m_boxPositions[i]);
		//eller visible i ->magic->enable og modellen bare kjører draw array Men det må gjøres i modelnode
		Visible.at(i)->draw();
	}

	// When we get here the depth buffer is already populated and the stencil pass
	// depends on it, but it does not write to it.
	gl::DepthMask(gl::FALSE_);
}