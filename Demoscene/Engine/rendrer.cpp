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


		//Math3d.cpp you still remain 10 years since I encountered you in the OpenGL bluebook, GLFrame is around here somewhere
		//One of these days I'll jump over to Eigen...but not this year
		M3DMatrix44f CamWorld, tmpProj, CamWorldInv, ReverseTranslation, tmpRTinvView;
		M3DVector4f tranComp2;
		m3dLoadIdentity44(CamWorld);

		cammy->getParent()->getLocalTransform(CamWorld);
		
		
		m3dInvertMatrix44(CamWorldInv, CamWorld);
		m3dGetMatrixColumn44(tranComp2, CamWorldInv, 3);
		EyeWorldPos = NS_VEC::VEC3(CamWorldInv[12], CamWorldInv[13], CamWorldInv[14]);

		m3dTranslationMatrix44(ReverseTranslation, -EyeWorldPos.X, -EyeWorldPos.Y, -EyeWorldPos.Z);

		

		m3dMatrixMultiply44(tmpRTinvView, CamWorldInv, ReverseTranslation);
		m3dCopyMatrix44(InvViewRT, CamWorldInv);

		m3dCopyMatrix44(view, CamWorld);
		cammy->getProjection(tmpProj);
		m3dCopyMatrix44(projection, tmpProj);



	}

	if (NS_SG::node::NODE_ASSET == Node->getType())
	{

		RendrerItem Tmp;

		assetNode *mesh = reinterpret_cast<assetNode*>(Node);
		if (NULL != mesh->getMagic())
		{
	
			Node->getAbsoluteTransform(world);

			M3DMatrix44f wv, wvp, vp;


	

			m3dMatrixMultiply44(vp, projection, view);


			m3dMatrixMultiply44(wvp, vp, world);
			m3dCopyMatrix44(Tmp.sWVP, wvp);
			m3dCopyMatrix44(Tmp.sTransform, world);


			Tmp.gpuEff = mesh->getMagic();
			Tmp.gpuIn = mesh->getAsset();
			
		}
		

		
		Visible.push_back(Tmp);

		


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

			Node->getAbsoluteTransform(world);

			

			s_LPL = lPoint->GetPointLight();

			M3DMatrix44f wvp, vp;

			M3DMatrix44f w_scale, w_scaled;
			float f_scale = CalcPointLightBSphere(s_LPL);
	
			
			m3dScaleMatrix44(w_scale, f_scale, f_scale, f_scale);

			m3dMatrixMultiply44(w_scaled, world, w_scale);
			
			
		
			m3dMatrixMultiply44(vp, projection, view);

			
			m3dMatrixMultiply44(wvp, vp, w_scaled);


			m3dCopyMatrix44(Tmp.sWVP, wvp);

			m3dCopyMatrix44(Tmp.sW, w_scaled);
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
			M3DMatrix44f swp;
			m3dLoadIdentity44(swp);
			M3DMatrix44f world;
			m3dLoadIdentity44(world);
			m3dMatrixMultiply44(swp, projection, view);
			Tmp.sNode = lDir;
			Tmp.sDL = lDir->GetDirLight();
			//lDir->LightMagic->SetProjectionMatrix
			m3dCopyMatrix44(Tmp.sW, world);
			m3dCopyMatrix44(Tmp.sWVP, swp);
			//m3dCopyMatrix44(Tmp.sWVP, view);


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
	std::cout << "Started!==================!" << std::endl;
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

	//

	Visible.clear();
	VisiblePoint.clear();
	VisibleDir.clear();




	//don't do this also USE EIGEN OF GLM OR WRITE YOUR OWN! MATH3D IS SHIT!
	M3DMatrix44f world;
	m3dLoadIdentity44(world);

	
	//scene->an

	visit(scene, world );


	//M3DMatrix44f inverseView;
	//m3dInvertMatrix44(inverseView, view);

	//NS_VEC::VEC3 EyeWorldPos(view[12], view[13], view[14]);

	//NS_VEC::VEC3 EyeWorldPos(inverseView[12], inverseView[13], inverseView[14]);



	TheDisc->MasterList_Buffers[0]->EnablePass(0);
	//mgBuffer->StartFrame();
	//Geom pass---------------------------------------------
	//mgBuffer->BindForGeomPass();
	TheDisc->MasterList_Buffers[0]->EnablePass(1);

	glDepthMask(GL_TRUE);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Geometry_RayMarcher_Vert.glsl
	glEnable(GL_DEPTH_TEST);
	GeoRayMarch->Enable();
	GeoRayMarch->SetViewMatrix(view); //Views Looks to be correct
	GeoRayMarch->SetProjectionMatrix(projection);

	M3DMatrix44f ModelView, toCam;
	m3dLoadIdentity44(ModelView);

	glActiveTexture(NS_ENG::asset::CurrentStage->TextureUnits[TypeOfTexture::DiffuseArrayMap_UNIT]);
	//glActiveTexture(TypeOfTexture::GBuffer_WorldPos_UNIT);
	glBindTexture(GL_TEXTURE_2D_ARRAY, base_buffer::DiffArrayMapTexure);
	//GL_TEXTURE_BINDING_2D_ARRAY
	glActiveTexture(NS_ENG::asset::CurrentStage->TextureUnits[TypeOfTexture::baseMaterialMap_UNIT]);
	//glActiveTexture(TypeOfTexture::baseMaterialMap_UNIT);
	glBindTexture(GL_TEXTURE_2D, NS_ENG::Material::GeneratebaseMaterialMap());

	//PointLess Identity Matrix to Geometry_RayMarcher_Vert.glsl
	GeoRayMarch->SetWVP(ModelView);
	GeoRayMarch->SetEyeWorldPos(EyeWorldPos);
	//GeoRayMarch->
	//If I want a Raymarcher here should the depth test be disable?
	glFrontFace(GL_CW);
	quad->Draw();//need generic quad assembly here, maybe create something static?
	glFrontFace(GL_CCW);

	

	
	//Idea is to have a system that sets up these drawquees and render process.
	//But not this year!
	for (vIT iv = beginVisible(); iv != endVisible(); ++iv) {

		//eller visible i ->magic->enable og modellen bare kjører draw array Men det må gjøres i modelnode
		
		NS_EFF::GeomPacket *geoEff = dynamic_cast<NS_EFF::GeomPacket*>(iv->gpuEff);

		if (geoEff != NULL)
		{
			geoEff->Enable();
			geoEff->SetWVP(iv->sWVP);
			geoEff->SetWorldMatrix(iv->sTransform);
			geoEff->SetViewMatrix(view);
			geoEff->SetProjectionMatrix(projection);

			glActiveTexture(NS_ENG::asset::CurrentStage->TextureUnits[TypeOfTexture::DiffuseArrayMap_UNIT]);
			glBindTexture(GL_TEXTURE_2D_ARRAY, base_buffer::DiffArrayMapTexure);
			
			glActiveTexture(NS_ENG::asset::CurrentStage->TextureUnits[TypeOfTexture::baseMaterialMap_UNIT]);
			glBindTexture(GL_TEXTURE_2D, NS_ENG::Material::GeneratebaseMaterialMap());




		}

		
		iv->gpuIn->Draw();
		

	}

	//Screen spaced Ambient Occulsion pass


	//gather what uniforms actually matters, the idea I have with DemoMeister is to 
	//have a callback statemachine system which feeds nessescary paramaters to packets, shaders, buffers,etc.
	//high fucking hopes....but not this year
	M3DMatrix44f IdentSWP, ViewProAO;
	m3dLoadIdentity44(ViewProAO);//pointless
	m3dLoadIdentity44(IdentSWP);//pointless

	m3dLoadIdentity44(ModelView);//pointless

	AoPass->Enable();


	//god im lazy 
	m3dMatrixMultiply44(ViewProAO, projection, view); //Redundant


	//Rendrer is a nice place to hack, but god its messy.
	//My ideas for a pass system is meant to organize all this
	//Though I still want a couple of sections free for hacks
	//an callback interface perhaps. NOT THIS YEAR
	AoPass->SetWVP(ModelView);

	AoPass->SetViewMatrix(view);
	AoPass->SetProjectionMatrix(projection);

	TheDisc->MasterList_Buffers[1]->EnablePass(0);


	glActiveTexture(NS_ENG::asset::CurrentStage->TextureUnits[TypeOfTexture::AOBuffer_NOISE]);
	glBindTexture(GL_TEXTURE_2D, AoPass->NoiseTexure);



	glDisable(GL_DEPTH_TEST);


	glFrontFace(GL_CW);
	quad->Draw(0);
	glFrontFace(GL_CCW);

	//glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Stencil Pass og Lys pass------------------------------------------


	glDepthMask(GL_FALSE);

	glEnable(GL_STENCIL_TEST);
	




	for (vPITc ip = beginVisiblePoint(); ip != endVisiblePoint(); ++ip) {
		ip->sNode->NullMagic->Enable();

		TheDisc->MasterList_Buffers[0]->EnablePass(2);


		glEnable(GL_DEPTH_TEST);

		glDisable(GL_CULL_FACE);

		glClear(GL_STENCIL_BUFFER_BIT);

		/////////////////////////////////////////////////////////
		//Years ago I was desperate to release something cool
		//So in all the tutorials I watched I didnt even bother
		//to type the code, hell I couldnt get it to work so I had to make sure
		//everything was excactly as it was....of course it was just a damn quad
		//drawn the wrong way...typical
		//Anyway OGLDEV has a lot of credit for my deferred rendrer
		//I used to keep the liscenc agreement up there, but I changed it so much....
		//Well that still makes it derivative...should probably put the liscence back up
		/////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////
		// We need the stencil test to be enabled but we want it
		// to succeed always. Only the depth test matters.
		//////////////////////////////////////////////////////////
		glStencilFunc(GL_ALWAYS, 0, 0);

		glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
		glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

		ip->sNode->NullMagic->SetWorldMatrix(ip->sW);



		ip->sNode->NullMagic->SetProjectionMatrix(projection);
		ip->sNode->NullMagic->SetViewMatrix(view);
		

		sphere_null->Draw(0);
		
		
		
		
		//pointlys pass--------------------------------
		//kjøre spotlight her også?
		ip->sNode->LightMagic->Enable();

		TheDisc->MasterList_Buffers[0]->EnablePass(3);

		ip->sNode->LightMagic->SetEyeWorldPos(EyeWorldPos);

		glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);


		ip->sNode->LightMagic->SetProjectionMatrix(projection);
		ip->sNode->LightMagic->SetViewMatrix(view);
		
		ip->sNode->LightMagic->SetWorldMatrix(ip->sW);


		ip->sNode->LightMagic->SetPointLight(ip->sPL);
		
		sphere_light->Draw(0);
		
		glCullFace(GL_BACK);

		glDisable(GL_BLEND);
	}

	glDisable(GL_STENCIL_TEST);

	//dir lys pass  dritt som ikke vil fungere -------------------
	for (vDIT id = beginVisibleDir(); id != endVisibleDir(); ++id) {

		id->sNode->LightMagic->Enable();
		id->sNode->LightMagic->SetProjectionMatrix(projection);

		TheDisc->MasterList_Buffers[0]->EnablePass(3);



		id->sNode->LightMagic->SetEyeWorldPos(EyeWorldPos);
		id->sNode->LightMagic->SetDirectionalLight(id->sDL);
		id->sNode->LightMagic->SetWorldMatrix(id->sW);

		id->sNode->LightMagic->SetViewMatrix(view);
		id->sNode->LightMagic->SetProjectionMatrix(projection);


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

	TheDisc->MasterList_Buffers[0]->EnablePass(4);

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