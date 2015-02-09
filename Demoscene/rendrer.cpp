#include "rendrer.h"

#include "transform.h"
#include "assetNode.h"
#include "modelNode.h"
#include "node.h"


#include <stack>



using namespace sg::noder;


void rendrer::visit(nodePtr Node, M3DMatrix44f  world)
{
	if (4 == Node->getType())
	{
		modelNode mesh = reinterpret_cast<modelNode*>(Node);
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
	M3DMatrix44f world;
	m3dLoadIdentity44(world);
	visit(scene, world );
}