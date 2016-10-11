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



		M3DMatrix44f CamWorld, tmpProj, CamWorldInv, ReverseTranslation, tmpRTinvView;
		M3DVector4f tranComp2;
		m3dLoadIdentity44(CamWorld);

		//cammy->getAbsoluteTransform(CamWorld);
		cammy->getParent()->getLocalTransform(CamWorld);
		
		
		m3dInvertMatrix44(CamWorldInv, CamWorld);
		m3dGetMatrixColumn44(tranComp2, CamWorldInv, 3);
		//EyeWorldPos = NS_VEC::VEC3(tranComp2[0], tranComp2[1], tranComp2[2]);
		EyeWorldPos = NS_VEC::VEC3(CamWorldInv[12], CamWorldInv[13], CamWorldInv[14]);

		m3dTranslationMatrix44(ReverseTranslation, -EyeWorldPos.X, -EyeWorldPos.Y, -EyeWorldPos.Z);
		//m3dTranslationMatrix44(ReverseTranslation, EyeWorldPos.X*-1.0f, EyeWorldPos.Y*-1.0f, EyeWorldPos.Z*-1.0f);


		//there there, hide the shame.
		/*
		M3DMatrix44f RotInv, SortaScale, AnotherFuckingIntermediate, CamWorld, CamWorldInv, local, tmpProj, ModelView, ModelView2, TransposedMat, ReverseTranslation, TransposedRot, PreTransposedRot;
		M3DVector4f tranComp, tranComp2, tranComp3;
		M3DVector3f forwardComp, cameraViewFix;
		M3DMatrix33f RotComp, RotComp2, TransposeRotComp, TransposeRotComp2, Invert;

		m3dLoadIdentity44(SortaScale);
		m3dLoadIdentity44(AnotherFuckingIntermediate);

		m3dLoadIdentity44(CamWorld);
		m3dLoadIdentity44(CamWorldInv);
		m3dLoadIdentity44(ModelView);
		m3dLoadIdentity44(ModelView2);
		m3dLoadIdentity44(TransposedMat);
		m3dLoadIdentity44(ReverseTranslation);
		m3dLoadIdentity44(TransposedRot);
		m3dLoadIdentity44(PreTransposedRot);
		
		
		m3dLoadIdentity33(RotComp);
		m3dLoadIdentity33(TransposeRotComp);
		m3dLoadIdentity33(Invert);
		cammy->getAbsoluteTransform(CamWorld);
		cammy->getInverseRotation(RotInv);
		//TransposedRot
		m3dExtractRotationMatrix33(RotComp2, CamWorld);
		
		//cameraViewFix
		
		m3dInjectRotationMatrix44(PreTransposedRot, RotComp2);

		//m3dTransposeMatrix44(TransposedRot, PreTransposedRot);
		

		m3dGetMatrixColumn44(tranComp3, TransposedRot, 2);
		tranComp3[0] = tranComp3[0] * 1.0;
		tranComp3[1] = tranComp3[1] * 1.0;
		tranComp3[2] = tranComp3[2] * 1.0;
		m3dGetMatrixColumn44(tranComp2, CamWorld, 3);
		EyeWorldPos = NS_VEC::VEC3(tranComp2[0], tranComp2[1], tranComp2[2]);
		m3dTranslationMatrix44(ReverseTranslation, -EyeWorldPos.X, -EyeWorldPos.Y, -EyeWorldPos.Z);
		//m3dTranslationMatrix44(ReverseTranslation, EyeWorldPos.X*-1.0f, EyeWorldPos.Y*-1.0f, EyeWorldPos.Z*-1.0f);


		m3dTransposeMatrix44(TransposedRot, PreTransposedRot);
		m3dMatrixMultiply44(AnotherFuckingIntermediate, ReverseTranslation, ReverseTranslation);
		//m3dMatrixMultiply44(AnotherFuckingIntermediate, ReverseTranslation, SortaScale);

		//m3dMatrixMultiply44(ModelView2, ReverseTranslation, AnotherFuckingIntermediate);
		m3dMatrixMultiply44(ModelView2, SortaScale, AnotherFuckingIntermediate);

		//m3dMatrixMultiply44(ModelView2, ReverseTranslation, TransposedRot);
		m3dInvertMatrix44(CamWorldInv, CamWorld);
		//EyeWorldPos = NS_VEC::VEC3(CamWorldInv[12], CamWorldInv[13], CamWorldInv[14]);
		//EyeWorldPos = NS_VEC::VEC3(CamWorldInv[12], CamWorldInv[13], CamWorldInv[14]);


		m3dTransposeMatrix44(TransposedMat, CamWorld);
		m3dExtractRotationMatrix33(RotComp, TransposedMat);
		//TransposeRotComp
		m3dGetMatrixColumn33(forwardComp, RotComp, 2);
		m3dScaleVector3(forwardComp, -1.0f);
		m3dCopyMatrix33(TransposeRotComp, RotComp);
		m3dSetMatrixColumn33(TransposeRotComp, forwardComp, 2);
		
		m3dLoadIdentity44(view);
		m3dLoadIdentity44(InvViewRT);
		//CamWorldModelView2
		m3dInjectRotationMatrix44(ModelView, TransposeRotComp);
		m3dSetMatrixColumn44(ModelView, tranComp, 3);
		m3dInjectRotationMatrix44(CamWorldInv, TransposeRotComp);
		float VCollumn_x, VCollumn_y, VCollumn_z, VCollumn_w;
		//VCollumn_x = CamWorld[8];
		//VCollumn_y = CamWorld[9];
		//VCollumn_z = CamWorld[10];
		//VCollumn_w = CamWorldInv[11];

		//CamWorld[8] = VCollumn_x * -1.0f;
		//CamWorld[9] = VCollumn_y * -1.0f;
		//CamWorld[10] = VCollumn_z * -1.0f;
		//CamWorldInv[11] =  VCollumn_w * -1.0f;
		*/

		m3dMatrixMultiply44(tmpRTinvView, CamWorldInv, ReverseTranslation);
		m3dCopyMatrix44(InvViewRT, CamWorldInv);
		//m3dCopyMatrix44(view, CamWorld);
		//m3dCopyMatrix44(view, tmpRTinvView);

		//M3DMatrix44f LocalTr;
		//cammy->getParent()->getLocalTransform(LocalTr);

		m3dCopyMatrix44(view, CamWorld);
		cammy->getProjection(tmpProj);
		m3dCopyMatrix44(projection, tmpProj);
		//cammy->ge

		//PIVVOT PIVVOT BRUK DEN TARGETNODEN!
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
			m3dCopyMatrix44(Tmp.sW, world);

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
			
			Tmp.sNode = lDir;
			Tmp.sDL = lDir->GetDirLight();
			m3dCopyMatrix44(Tmp.sW, world);
			m3dCopyMatrix44(Tmp.sWVP, swp);


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


	//M3DMatrix44f inverseView;
	//m3dInvertMatrix44(inverseView, view);

	//NS_VEC::VEC3 EyeWorldPos(view[12], view[13], view[14]);

	//NS_VEC::VEC3 EyeWorldPos(inverseView[12], inverseView[13], inverseView[14]);



	
	mgBuffer->StartFrame();
	//Geom pass---------------------------------------------
	mgBuffer->BindForGeomPass();


	glDepthMask(GL_TRUE);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	GeoRayMarch->Enable();
	GeoRayMarch->SetViewMatrix(view);
	GeoRayMarch->SetProjectionMatrix(projection);

	M3DMatrix44f ModelView, toCam;
	m3dLoadIdentity44(ModelView);
	//m3dLoadIdentity44(toCam);
	//m3dMatrixMultiply44(toCam, view, ModelView);
	//m3dInvertMatrix44(toCam, view);
	//m3dTransposeMatrix44(ModelView, toCam);
	//m3dCopyMatrix44(Tmp.sWVP, wvp);
	GeoRayMarch->SetWVP(ModelView);
	GeoRayMarch->SetEyeWorldPos(EyeWorldPos);
	//If I want a Raymarcher here should the depth test be disable?
	glFrontFace(GL_CW);
	quad->Draw();
	glFrontFace(GL_CCW);

	

	

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
			geoEff->SetViewMatrix(view);
			geoEff->SetProjectionMatrix(projection);
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

	//Screen spaced Ambient Occulsion pass

	M3DMatrix44f IdentSWP;
	m3dLoadIdentity44(IdentSWP);
	AoPass->Enable();
	mgBuffer->BindForAoPass();



	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, AoPass->NoiseTexure);


	AoPass->SetWVP(IdentSWP);
	//AoPass->SetWorldMatrix(IdentSWP);
	AoPass->SetViewMatrix(view);
	AoPass->SetProjectionMatrix(projection);
	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glDrawBuffer(GL_COLOR_ATTACHMENT0);

	glFrontFace(GL_CW);
	quad->Draw();
	glFrontFace(GL_CCW);

	//glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Stencil Pass og Lys pass------------------------------------------


	glDepthMask(GL_FALSE);

	glEnable(GL_STENCIL_TEST);
	




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

		ip->sNode->NullMagic->SetWorldMatrix(ip->sW);

		ip->sNode->NullMagic->SetProjectionMatrix(projection);
		ip->sNode->NullMagic->SetViewMatrix(view);
		
		sphere_null->Draw();
		
		
		
		
		//pointlys pass--------------------------------
		//kjøre spotlight her også?
		ip->sNode->LightMagic->Enable();

		mgBuffer->BindForLightPass();

		ip->sNode->LightMagic->SetEyeWorldPos(EyeWorldPos);

		glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		//ip->sNode->LightMagic->SetWVP(ip->sWVP);
		ip->sNode->LightMagic->SetProjectionMatrix(projection);
		ip->sNode->LightMagic->SetViewMatrix(view);
		ip->sNode->LightMagic->SetWorldMatrix(ip->sW);
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
		//swp

		id->sNode->LightMagic->SetEyeWorldPos(EyeWorldPos);
		id->sNode->LightMagic->SetDirectionalLight(id->sDL);
		id->sNode->LightMagic->SetWorldMatrix(id->sW);
		id->sNode->LightMagic->SetViewMatrix(id->sWVP);
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