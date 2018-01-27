#ifndef RENDRER_HPP
#define RENDRER_HPP
//   model kaller på rendrer eller loop henter shader, matrial og modell indexer
#include <SceneGraph/composite.h>
#include <SceneGraph/camera.h>
//#include "../Math/math3d.h"
#include <Rendrer/context.h>
#include <Rendrer/callbacks.h>

#include <SceneGraph/modelNode.h>
#include <SceneGraph/gridNode.h>
#include <SceneGraph/pointLightNode.h>
#include <SceneGraph/dirLightNode.h>
#include <Engine/model.h>
#include <bass.h>
#include <Timer.h>

#include <util.h>

//Im planning to making this a abstract class of the pass items


//Should not refer directly to the packets, indirectly through pass system
#include <DemoMeister\ShaderFu\DeferredPackets\aoPacket.h>
#include <DemoMeister\ShaderFu\DeferredPackets\RayMarcher.h>

//yes I know I need a proper system for passes. 
//2017: its comming but it really shouldnt...fuck engine coding! WHY DIDNT I LISTEN TO THE OTHERS!?
//#include "ShaderFu/DeferredPackets/aoPacket.h"
//#include "ShaderFu/DeferredPackets/RayMarcher.h"




extern HSTREAM stream;


//Shoulld remove this also, visitation and rendrer should be seperate parts
//Visist would fit in demo meister
namespace NS_ENG
{ 


	struct RendrerItem
	{

		asset *gpuIn;
		NS_EFF::renderPacket *gpuEff;

		M3DMatrix44f sTransform;
		M3DMatrix44f sWVP;
		
	};

	

	struct PointLightItem
	{
		NS_SG::pointLightNode *sNode;
		PointLight sPL;
		M3DMatrix44f sWVP;
		M3DMatrix44f sW;


	};

	struct DirLightItem
	{
		NS_SG::dirLightNode *sNode;
		DirectionalLight sDL;
		M3DMatrix44f sWVP;
		M3DMatrix44f sW;
		
	};

class rendrer : public ICallbacks
{
public:
	Timer Ctan;
	double currentCtan;

	rendrer(NS_SG::composite *_scene, NS_SG::camera *_camera,
		NS_EFF::RayMarcher * _GeoRayMarch, 
		NS_EFF::aoPacket * _AoPass) : scene(_scene),
		kamera(_camera),  GeoRayMarch(_GeoRayMarch),
		AoPass(_AoPass)
	{

		unsigned int w = GetPixelWidth();
		unsigned int h = GetPixelHeight();


	
		m3dLoadIdentity44(view);
		kamera->getProjection(projection);
		//kamera->getAbsoluteTransform(view);
		kamera->getParent()->getLocalTransform(view);


		this->sphere_light = new NS_ENG::model();
		this->sphere_null = new NS_ENG::model();
		this->quad = new NS_ENG::model();

		this->sphere_light->Load(NS_ENG::ModelSimple::Sphere);
		this->sphere_null->Load(NS_ENG::ModelSimple::Sphere);
		this->quad->Load(NS_ENG::ModelSimple::Quad);
		std::cout << "Rendrer Instansiated!==================!" << std::endl;

	}

	void visit(NS_SG::node *Node, M3DMatrix44f world);



	void Run();
	virtual void RenderSceneCB();


	float CalcPointLightBSphere(const PointLight& Light);

private:
	NS_SG::composite *scene;
	NS_SG::camera *kamera;


	//why two for a simple assembly? TRADITION thats why!
	NS_ENG::model *sphere_light;
	NS_ENG::model *sphere_null;
	NS_ENG::model *quad;

	//need better system for this
	NS_EFF::aoPacket *AoPass;
	NS_EFF::RayMarcher *GeoRayMarch;


	std::list< struct RendrerItem> Visible;
	typedef std::list< struct RendrerItem>::iterator vIT;
	typedef std::list< struct RendrerItem>::const_iterator vITc;
	vIT beginVisible(){ return Visible.begin(); }
	vIT endVisible(){ return Visible.end(); }
	vITc beginVisible() const{ return Visible.begin(); }
	vITc endVisible()  const { return Visible.end(); }


	std::list< struct PointLightItem> VisiblePoint;
	typedef std::list< struct PointLightItem>::iterator vPIT;
	typedef std::list< struct PointLightItem>::const_iterator vPITc;
	vPIT beginVisiblePoint(){ return VisiblePoint.begin(); }
	vPIT endVisiblePoint(){ return VisiblePoint.end(); }
	vPITc beginVisiblePoint() const{ return VisiblePoint.begin(); }
	vPITc endVisiblePoint()  const { return VisiblePoint.end(); }


	std::list< struct DirLightItem> VisibleDir;
	typedef std::list< struct DirLightItem>::iterator vDIT;
	typedef std::list< struct DirLightItem>::const_iterator vDITc;
	vDIT beginVisibleDir(){ return VisibleDir.begin(); }
	vDIT endVisibleDir(){ return VisibleDir.end(); }
	vDITc beginVisibleDir() const{ return VisibleDir.begin(); }
	vDITc endVisibleDir()  const { return VisibleDir.end(); }


	//std::list< struct RendrerItem> Visible;
	//std::list< struct RendrerItem>::iterator vIT;

	//std::list< struct PointLightItem> VisiblePoint;
	//std::list< struct PointLightItem>::iterator vPIT;

	//std::list< struct DirLightItem> VisibleDir;
	//std::list< struct DirLightItem>::iterator vDIT;




public:
	M3DMatrix44f view,InvViewRT, projection;
	NS_VEC::VEC3 EyeWorldPos;
	GLfloat FOV;
	
};
}
#endif