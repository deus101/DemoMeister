#include "rendrer.h"


#include "../SceneGraph/node.h"
#include "../SceneGraph/transform.h"
#include "../SceneGraph/assetNode.h"
#include "../SceneGraph/modelNode.h"


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
		mesh->draw();
	}

	for (node::child_iterator i = Node->beginChildren(); i != Node->endChildren(); ++i)
		visit(*i, world);
}


void rendrer::draw()
{
	//don't do this also USE EIGEN OF GLM OR WRITE YOUR OWN MATH3D IS SHIT!
	M3DMatrix44f world;
	m3dLoadIdentity44(world);
	visit(scene, world );
}