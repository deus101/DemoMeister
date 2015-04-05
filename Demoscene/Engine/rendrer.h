#ifndef RENDRER_HPP
#define RENDRER_HPP
//   model kaller p� rendrer eller loop henter shader, matrial og modell indexer
#include "../SceneGraph/composite.h"
#include "../SceneGraph/camera.h"
#include "../Math/math3d.h"
#include "../Rendrer/context.h"
#include "../SceneGraph/modelNode.h"
//rendrern can ta over for compositt klassen... eller kansje ikke hva har man namespaces til...
//men er konteinere I namespaces en god ide? 
namespace NS_ENG
{ 


	struct RendrerItem
	{
		//RendrerItem()
		//{
		//	
		//}

		//VEC3 m_vNor;
		//referanse til objekt referanse burde v�rt her
		//burde v�rt detrte men pr�ver mer direkt metode f�rst
		//NS_SG::assetNode *sNode;
		NS_SG::modelNode *sNode;
		M3DMatrix44f sTransform;
		M3DMatrix44f sWVP;
	};

class rendrer
{
public:

	rendrer(NS_SG::composite *_scene, NS_SG::camera *_camera, NS_REND::context *_context) : scene(_scene), kamera(_camera), mContext(_context)
	{

		
	}
	//using nodePtr might be a mistake
	void visit(NS_SG::node *Node, M3DMatrix44f world);
	void draw();

private:
	NS_SG::composite *scene;
	NS_SG::camera *kamera;
	NS_REND::context *mContext;
	
	std::list< struct RendrerItem> Visible;
	std::list< struct RendrerItem>::iterator vIT;


public:
	M3DMatrix44f view, projection;

};
}
#endif