#include "rendrer.h"


#include "../SceneGraph/node.h"
#include "../SceneGraph/transform.h"
#include "../SceneGraph/assetNode.h"
#include "../SceneGraph/modelNode.h"
#include "../SceneGraph/gridNode.h"


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

		M3DMatrix44f CamWorld, local;
		cammy->getAbsoluteTransform(CamWorld);
		m3dInvertMatrix44(view, CamWorld);
		//cammy->getParent()->getLocalTransform(view);


	}

	if (NS_SG::node::NODE_ASSET == Node->getType())
	{
		//std::cout << Node->getName() << std::endl;
		RendrerItem Tmp;
		//aabb checks of culling her
		assetNode *mesh = reinterpret_cast<assetNode*>(Node);
		if (NULL != mesh->getMagic())
		{
			//M3DMatrix44f world; 

			Node->getAbsoluteTransform(world);

			M3DMatrix44f wv, wvp, vp;


			M3DMatrix44f world_view_proj, matWVP_inv;

			m3dMatrixMultiply44(vp, projection, view);


			m3dMatrixMultiply44(wvp, vp, world);
			m3dCopyMatrix44(Tmp.sWVP, wvp);
			m3dCopyMatrix44(Tmp.sTransform, world);


			Tmp.gpuEff = mesh->getMagic();
			Tmp.gpuIn = mesh->getAsset();
			//Tmp.sNode = mesh;
		}
		

		
		Visible.push_back(Tmp);

		//Ide: en drawque item som har Matrisene og informasjonen den trenger, må sorte denne skikkelig uansett. Transformasjons matrisen iallefall.



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

			

			s_LPL = lPoint->GetPointLight();
			M3DMatrix44f wv, wvp , vp;


			M3DMatrix44f w_scale, w_scaled;
			float f_scale = CalcPointLightBSphere(s_LPL);
	
			
			m3dScaleMatrix44(w_scale, f_scale, f_scale, f_scale);

			m3dMatrixMultiply44(w_scaled, world, w_scale);
			
			
		
			m3dMatrixMultiply44(vp, projection, view);

			
			m3dMatrixMultiply44(wvp, vp, w_scaled);

			m3dCopyMatrix44(Tmp.sWVP, wvp);
			

		}
		Tmp.sPL = s_LPL;
		Tmp.sNode = lPoint;

		VisiblePoint.push_back(Tmp);
		

	}

	if (NS_SG::node::NODE_LIGHT_DIR == Node->getType())
	{
		DirLightItem Tmp;
		dirLightNode *lDir = reinterpret_cast<dirLightNode*>(Node);
		if (NULL != lDir->LightMagic)
		{
			M3DMatrix44f world;
			m3dLoadIdentity44(world);

			
			Tmp.sNode = lDir;
			Tmp.sDL = lDir->GetDirLight();
			m3dCopyMatrix44(Tmp.sWVP, world);



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
	
	BASS_Start();
	BASS_ChannelPlay(stream, false);

	ContextRun(this);
	Ctan = Timer();
	currentCtan = Ctan.elapsed();
}

void rendrer::RenderSceneCB()
{	
	double deltaCtan;
	double nowCtan = Ctan.elapsed();

	deltaCtan = nowCtan - currentCtan;
	currentCtan = nowCtan;
	//deltaTime = deltaCtan;
	//currentTime = currentCtan;


	//float test = GetDeltaTime();
	//double testD = GetDeltaTimeD();

	Visible.clear();
	VisiblePoint.clear();
	VisibleDir.clear();

	//don't do this also USE EIGEN OF GLM OR WRITE YOUR OWN! MATH3D IS SHIT!
	M3DMatrix44f world;
	m3dLoadIdentity44(world);

	
	//scene->an

	visit(scene, world );

	
	mgBuffer->StartFrame();
	//Geom pass---------------------------------------------
	mgBuffer->BindForGeomPass();


	glDepthMask(GL_TRUE);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	

	for (vIT iv = beginVisible(); iv != endVisible(); ++iv) {

		//eller visible i ->magic->enable og modellen bare kjører draw array Men det må gjøres i modelnode
		
		NS_EFF::GeomPacket *geoEff = dynamic_cast<NS_EFF::GeomPacket*> (iv->gpuEff);
		NS_EFF::HeightMapPacket *hmapEff = dynamic_cast<NS_EFF::HeightMapPacket*> (iv->gpuEff);
		NS_ENG::GridPoints *gridAss = dynamic_cast<NS_ENG::GridPoints*> (iv->gpuIn);
		
		if (hmapEff != NULL)
		{
			hmapEff->Enable();
			hmapEff->SetWVP(iv->sWVP);
			hmapEff->SetWorldMatrix(iv->sTransform);
			hmapEff->SetHalfSize();
		}
		if (geoEff != NULL)
		{
			geoEff->Enable();
			geoEff->SetWVP(iv->sWVP);
			geoEff->SetWorldMatrix(iv->sTransform);
		}

		if (gridAss != NULL)
		{
			gridAss->SetDelta(deltaCtan);
		}

		iv->gpuIn->Draw();
		
		//old
		//in truth the gridnode should derive from modelnode with virtual functions that can be overridden
		//iv->sNode->Magic->Enable();

		//iv->sNode->Magic->SetWVP(iv->sWVP);
		//iv->sNode->Magic->SetWorldMatrix(iv->sTransform);
		//iv->sNode->Model->Draw();
	}

	
	//Stencil Pass og Lys pass------------------------------------------
	glDepthMask(GL_FALSE);

	glEnable(GL_STENCIL_TEST);
	
	M3DMatrix44f inverseView;
	m3dInvertMatrix44(inverseView, view);

	//NS_VEC::VEC3 EyeWorldPos(view[12], view[13], view[14]);
	
	NS_VEC::VEC3 EyeWorldPos(inverseView[12], inverseView[13], inverseView[14]);



	for (vPITc ip = beginVisiblePoint(); ip != endVisiblePoint(); ++ip) {
		ip->sNode->NullMagic->Enable();

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
		
		
		
		
		//pointlys pass--------------------------------
		//kjøre spotlight her også?
		mgBuffer->BindForLightPass();

		ip->sNode->LightMagic->Enable();
		ip->sNode->LightMagic->SetEyeWorldPos(EyeWorldPos);

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

	//dir lys pass  dritt som ikke vil fungere -------------------
	for (vDIT id = beginVisibleDir(); id != endVisibleDir(); ++id) {

		id->sNode->LightMagic->Enable();

		mgBuffer->BindForLightPass();


		id->sNode->LightMagic->SetEyeWorldPos(EyeWorldPos);
		id->sNode->LightMagic->SetDirectionalLight(id->sDL);
		id->sNode->LightMagic->SetWVP(id->sWVP);


		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);
		glFrontFace(GL_CW);
 		quad->Draw();
		glFrontFace(GL_CCW);
		glDisable(GL_BLEND);

	
	
	}

	//final pass
	unsigned int w = GetPixelWidth();
	unsigned int h = GetPixelHeight();
	mgBuffer->BindForFinalPass();

	glBlitFramebuffer(0, 0, w, h,
		0, 0, w, h, GL_COLOR_BUFFER_BIT, GL_LINEAR);


	
	Swap();




}

float rendrer::CalcPointLightBSphere(const PointLight& Light)
{
	float MaxChannel = fmax(fmax(Light.Color.X, Light.Color.Y), Light.Color.Z);

	float ret = (-Light.Attenuation.Linear + sqrtf(Light.Attenuation.Linear * Light.Attenuation.Linear - 4 * Light.Attenuation.Exp * (Light.Attenuation.Exp - 256 * MaxChannel * Light.DiffuseIntensity)))
		/
		2 * Light.Attenuation.Exp;

	return ret;
}