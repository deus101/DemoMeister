#ifndef RENDRER_HPP
#define RENDRER_HPP
//   model kaller på rendrer eller loop henter shader, matrial og modell indexer
#include "../SceneGraph/composite.h"
#include "../SceneGraph/camera.h"
#include "../Math/math3d.h"
//rendrern can ta over for compositt klassen... eller kansje ikke hva har man namespaces til...
//men er konteinere I namespaces en god ide? 
namespace NS_ENG
{ 

class rendrer
{
public:

	rendrer(NS_SG::composite *_scene, NS_SG::camera *_camera) : scene(_scene), kamera(_camera)
	{

		
	}
	//using nodePtr might be a mistake
	void visit(node *Node, M3DMatrix44f world);
	void draw();

private:
	composite *scene;
	camera *kamera;
public:
	M3DMatrix44f view, projection;

};
}
#endif